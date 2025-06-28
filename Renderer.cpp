#include"Globals.h"  
#include"Renderer.h"  

#include <algorithm>  
#include <cmath>

namespace Rasterizer  
{  
    // Sets each element in 'colorBuffer' to 'color' as a Color4UB.  
    void Clear(const ColorBuffer& colorBuffer, const Vector4f& color)  
    {  
        std::fill_n(colorBuffer.pixels, WINDOW_WIDTH * WINDOW_HEIGHT, ToColor4UB(color));
    }  

    void Draw(const ColorBuffer& colorBuffer, 
        const Viewport& viewport, 
        const DrawCommand& command)
    {
        // For each triangle (set of 3 vertices) in vertex buffer
        for (std::uint32_t vIdx = 0;
            vIdx + 2 < command.mesh.vertexCount;
            vIdx += 3)
        {
            // Vertices are group adjacently in threes to make up a triangle.
            // Get all three points in the triangle as homogenous coordinates.
            auto v0 = command.transform * AsPoint(command.mesh.vertices[vIdx + 0]);
            auto v1 = command.transform * AsPoint(command.mesh.vertices[vIdx + 1]);
            auto v2 = command.transform * AsPoint(command.mesh.vertices[vIdx + 2]);

            v0 = Apply(viewport, v0);
            v1 = Apply(viewport, v1);
            v2 = Apply(viewport, v2);

            // Color vertex attributes
            auto c0 = command.mesh.colors[vIdx + 0];
            auto c1 = command.mesh.colors[vIdx + 1];
            auto c2 = command.mesh.colors[vIdx + 2];

            // Get determinate of [ v0v1 v0v2 ]
            float det012 = Det2D(v1 - v0, v2 - v0);

            // Is it counterclockwise on screen?
            bool const isCounterClockwise = det012 < 0.f;

            switch (command.cullMode)
            {
            case CullMode::None:
                break;
            case CullMode::Clockwise:
                if (!isCounterClockwise)
                    continue; // move to the next triangle
                break;
            case CullMode::CounterClockwise:
                if (isCounterClockwise)
                    continue; // move to the next triangle
                break;
            }

            // This fixes messed up orientations
            if (isCounterClockwise)
            {
                std::swap(v1, v2);
                det012 = -det012;
            }

            // Get the bounding box of the triangle (so we don't operate on redundant pixel coordinates)
            std::int32_t xmin = std::max<std::int32_t>(viewport.xmin, 0);
            std::int32_t xmax = std::min<std::int32_t>(viewport.xmax, WINDOW_WIDTH) - 1;
            std::int32_t ymin = std::max<std::int32_t>(viewport.ymin, 0);
            std::int32_t ymax = std::min<std::int32_t>(viewport.ymax, WINDOW_HEIGHT) - 1;

            // Restrict bounding box to be inside of our canvas space
            xmin = std::max<float>(xmin, std::min({ std::floor(v0.x), std::floor(v1.x), std::floor(v2.x) }));
            xmax = std::min<float>(xmax, std::max({ std::floor(v0.x), std::floor(v1.x), std::floor(v2.x) }));
            ymin = std::max<float>(ymin, std::min({ std::floor(v0.y), std::floor(v1.y), std::floor(v2.y) }));
            ymax = std::min<float>(ymax, std::max({ std::floor(v0.y), std::floor(v1.y), std::floor(v2.y) }));

            // For each pixel coordinate in our bounding box
            for (std::int32_t y = ymin; y <= ymax; ++y)
            {
                for (std::int32_t x = xmin; x <= xmax; ++x)
                {
                    // Sample point for this pixel (+ 0.5f because we sample the middle)
                    Vector4f p{ x + 0.5f, y + 0.5f, 0.f, 0.f };

                    /* 
                    * Get if p is left or right of a given side of the triangle.
                    * 
                    * Triangle v0, v1, v2 oriented clockwise (counterclockwise in regular 
                    * maths because Y is flipped in our case), so we check if p
                    * is left of v0v1, v1v2, and v2v0.
                    * 
                    * Det2D(A, B) is positive when the rotation from A to B is 
                    * clockwise. So in our case we check for this.
                    */
                    float det01p = Det2D(v1 - v0, p - v0);
                    float det12p = Det2D(v2 - v1, p - v1);
                    float det20p = Det2D(v0 - v2, p - v2);

                    // If sample point p is to the left of each side, color that pixel.                        
                    if (det01p >= 0.f && det12p >= 0.f && det20p >= 0.f)
                    {
                        // Calculate barycentric coordinates
                        float l0 = det12p / det012;
                        float l1 = det20p / det012;
                        float l2 = det01p / det012;

                        colorBuffer.ColorAt(x, y) = Types::ToColor4UB(l0 * c0 + l1 * c1 + l2 * c2);
                    }

                }
            }
        }
    }
}