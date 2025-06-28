#include"Globals.h"  
#include"Renderer.h"  

#include <algorithm>  
#include <cstring> // For std::memset  

namespace Rasterizer  
{  
    // Sets each element in 'colorBuffer' to 'color' as a Color4UB.  
    void Clear(const ColorBuffer& colorBuffer, const Vector4f& color)  
    {  
        std::fill_n(colorBuffer.pixels, WINDOW_WIDTH * WINDOW_HEIGHT, ToColor4UB(color));
    }  

    void Draw(const ColorBuffer& colorBuffer, const DrawCommand& command)
    {
        // For each vertex in buffer
        for (std::uint32_t vIdx = 0;
            vIdx + 2 < command.mesh.vertexCount;
            vIdx += 3)
        {
            // Vertices are group adjacently in threes to make up a triangle.
            // Get all three points in the triangle as homogenous coordinates.
            auto v0 = Types::AsPoint(command.mesh.vertexBuffer[vIdx + 0]);
            auto v1 = Types::AsPoint(command.mesh.vertexBuffer[vIdx + 1]);
            auto v2 = Types::AsPoint(command.mesh.vertexBuffer[vIdx + 2]);

            // For each screen coordinate (0,0) <> (WINDOW_WIDTH, WINDOW_HEIGHT)
            for (std::int32_t y = 0; y < WINDOW_HEIGHT; ++y)
            {
                for (std::int32_t x = 0; x < WINDOW_WIDTH; ++x)
                {
                    // Sample point for this pixel (+ 0.5f because we sample the middle)
                    Vector4f p{ x + 0.5f, y + 0.5f, 0.f, 0.f };

                    /* 
                    * Get if p is left or right of a given side of the triangle.
                    * 
                    * Triangle v0, v1, v2 oriented counterclockwise, so we check if p
                    * is left of v0v1, v1v2, and v2v0.
                    * 
                    * Det2D(A, B) is positive when the rotation from A to B is 
                    * counterclockwise. So in our case we check for this.
                    */
                    float det01p = Types::Det2D(v1 - v0, p - v0);
                    float det12p = Types::Det2D(v2 - v1, p - v1);
                    float det20p = Types::Det2D(v0 - v2, p - v2);

                    // If sample point p is to the left of each side, color that pixel.
                    if (det01p >= 0.f && det12p >= 0.f && det20p >= 0.f)
                        colorBuffer.ColorAt(x, y) = ToColor4UB(command.mesh.color);
                }
            }
        }
    }
}