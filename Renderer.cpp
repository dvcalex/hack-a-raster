#include"Globals.h"  
#include"Renderer.h"  

#include <algorithm>  
#include <cmath>

namespace Rasterizer  
{  
	namespace
	{

		struct Vertex
		{
			Vector4f pos;
			Vector4f color;
		};

		Vertex clipIntersectEdge(Vertex const& v0, Vertex const& v1, float value0, float value1)
		{
			// f(t) = at+b
			// f(0) = v0 = b
			// f(1) = v1 = a+v0 => a = v1 - v0
			// f(t) = v0 + (v1 - v0) * t
			// f(t) = 0 => t = -v0 / (v1 - v0) = v0 / (v0 - v1)

			float t = value0 / (value0 - value1);

			Vertex v;
			v.pos = (1.f - t) * v0.pos + t * v1.pos;
			v.color = (1.f - t) * v0.color + t * v1.color;

			return v;
		}

		Vertex* clipTriangle(Vertex* triangle, Vector4f equation, Vertex* result)
		{
			float values[3] =
			{
				Dot(triangle[0].pos, equation),
				Dot(triangle[1].pos, equation),
				Dot(triangle[2].pos, equation),
			};

			std::uint8_t mask = (values[0] < 0.f ? 1 : 0) | (values[1] < 0.f ? 2 : 0) | (values[2] < 0.f ? 4 : 0);

			switch (mask)
			{
			case 0b000:
				// All vertices are inside allowed half-space
				// No clipping required, copy the triangle to output
				*result++ = triangle[0];
				*result++ = triangle[1];
				*result++ = triangle[2];
				break;
			case 0b001:
				// Vertex 0 is outside allowed half-space
				// Replace it with points on edges 01 and 02
				// And re-triangulate
			{
				auto v01 = clipIntersectEdge(triangle[0], triangle[1], values[0], values[1]);
				auto v02 = clipIntersectEdge(triangle[0], triangle[2], values[0], values[2]);
				*result++ = v01;
				*result++ = triangle[1];
				*result++ = triangle[2];
				*result++ = v01;
				*result++ = triangle[2];
				*result++ = v02;
			}
			break;
			case 0b010:
				// Vertex 1 is outside allowed half-space
				// Replace it with points on edges 10 and 12
				// And re-triangulate
			{
				auto v10 = clipIntersectEdge(triangle[1], triangle[0], values[1], values[0]);
				auto v12 = clipIntersectEdge(triangle[1], triangle[2], values[1], values[2]);
				*result++ = triangle[0];
				*result++ = v10;
				*result++ = triangle[2];
				*result++ = triangle[2];
				*result++ = v10;
				*result++ = v12;
			}
			break;
			case 0b011:
				// Vertices 0 and 1 are outside allowed half-space
				// Replace them with points on edges 02 and 12
				*result++ = clipIntersectEdge(triangle[0], triangle[2], values[0], values[2]);
				*result++ = clipIntersectEdge(triangle[1], triangle[2], values[1], values[2]);
				*result++ = triangle[2];
				break;
			case 0b100:
				// Vertex 2 is outside allowed half-space
				// Replace it with points on edges 20 and 21
				// And re-triangulate
			{
				auto v20 = clipIntersectEdge(triangle[2], triangle[0], values[2], values[0]);
				auto v21 = clipIntersectEdge(triangle[2], triangle[1], values[2], values[1]);
				*result++ = triangle[0];
				*result++ = triangle[1];
				*result++ = v20;
				*result++ = v20;
				*result++ = triangle[1];
				*result++ = v21;
			}
			break;
			case 0b101:
				// Vertices 0 and 2 are outside allowed half-space
				// Replace them with points on edges 01 and 21
				*result++ = clipIntersectEdge(triangle[0], triangle[1], values[0], values[1]);
				*result++ = triangle[1];
				*result++ = clipIntersectEdge(triangle[2], triangle[1], values[2], values[1]);
				break;
			case 0b110:
				// Vertices 1 and 2 are outside allowed half-space
				// Replace them with points on edges 10 and 20
				*result++ = triangle[0];
				*result++ = clipIntersectEdge(triangle[1], triangle[0], values[1], values[0]);
				*result++ = clipIntersectEdge(triangle[2], triangle[0], values[2], values[0]);
				break;
				break;
			case 0b111:
				// All vertices are outside allowed half-space
				// Clip the whole triangle, result is empty
				break;
			}

			return result;
		}

		Vertex* clipTriangle(Vertex* begin, Vertex* end)
		{
			static Vector4f const equations[2] =
			{
				{0.f, 0.f,  1.f, 1.f}, // Z > -W  =>   Z + W > 0
				{0.f, 0.f, -1.f, 1.f}, // Z <  W  => - Z + W > 0
			};

			Vertex result[12];

			for (auto equation : equations)
			{
				auto result_end = result;

				for (Vertex* triangle = begin; triangle != end; triangle += 3)
					result_end = clipTriangle(triangle, equation, result_end);

				end = std::copy(result, result_end, begin);
			}

			return end;
		}

	}


    // Sets each element in 'colorBuffer' to 'color' as a Color4UB.  
    void Clear(const ColorBuffer& colorBuffer, const Vector4f& color)  
    {  
        std::fill_n(colorBuffer.pixels, WINDOW_WIDTH * WINDOW_HEIGHT, ToColor4UB(color));
    }  

    void Draw(const ColorBuffer& colorBuffer, 
        const Viewport& viewport, 
        const DrawCommand& command)
    {
        // For each triangle (set of 3 vertices/indices) in Vertex buffer
        for (std::uint32_t vertIdx = 0; (vertIdx + 2) < command.mesh.count; vertIdx += 3)
        {
            // initialize indices to the raw vertices
            std::uint32_t i0 = vertIdx + 0;
            std::uint32_t i1 = vertIdx + 1;
            std::uint32_t i2 = vertIdx + 2;

            // check for indices != nullptr
            if (command.mesh.indices)
            {
                // assign i0, i1, i2 to proper indices (we are now using indexed rendering)
                i0 = command.mesh.indices[i0];
                i1 = command.mesh.indices[i1];
                i2 = command.mesh.indices[i2];
            }

            // Fill just 3 vertices, but leave place for the clipping result
            Vertex clippedVertices[12];

            clippedVertices[0].pos = command.transform * AsPoint(command.mesh.vertices[i0]);
            clippedVertices[1].pos = command.transform * AsPoint(command.mesh.vertices[i1]);
            clippedVertices[2].pos = command.transform * AsPoint(command.mesh.vertices[i2]);

            clippedVertices[0].color = command.mesh.colors[i0];
            clippedVertices[1].color = command.mesh.colors[i1];
            clippedVertices[2].color = command.mesh.colors[i2];

            // This is where actual clipping takes place
            auto clippedVertices_end = clipTriangle(clippedVertices, clippedVertices + 3);

            for (auto triangle_begin = clippedVertices; triangle_begin != clippedVertices_end; triangle_begin += 3)
            {
                auto v0 = triangle_begin[0];
                auto v1 = triangle_begin[1];
                auto v2 = triangle_begin[2];

                v0.pos = PerspectiveDivide(v0.pos);
                v1.pos = PerspectiveDivide(v1.pos);
                v2.pos = PerspectiveDivide(v2.pos);

                v0.pos = Apply(viewport, v0.pos);
                v1.pos = Apply(viewport, v1.pos);
                v2.pos = Apply(viewport, v2.pos);

                // Get determinate of [ v0v1 v0v2 ]
                float det012 = Det2D(v1.pos - v0.pos, v2.pos - v0.pos);

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
                xmin = std::max<float>(xmin, std::min({ std::floor(v0.pos.x), std::floor(v1.pos.x), std::floor(v2.pos.x) }));
                xmax = std::min<float>(xmax, std::max({ std::floor(v0.pos.x), std::floor(v1.pos.x), std::floor(v2.pos.x) }));
                ymin = std::max<float>(ymin, std::min({ std::floor(v0.pos.y), std::floor(v1.pos.y), std::floor(v2.pos.y) }));
                ymax = std::min<float>(ymax, std::max({ std::floor(v0.pos.y), std::floor(v1.pos.y), std::floor(v2.pos.y) }));

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
                        float det01p = Det2D(v1.pos - v0.pos, p - v0.pos);
                        float det12p = Det2D(v2.pos - v1.pos, p - v1.pos);
                        float det20p = Det2D(v0.pos - v2.pos, p - v2.pos);

                        // If sample point p is to the left of each side, color that pixel.                        
                        if (det01p >= 0.f && det12p >= 0.f && det20p >= 0.f)
                        {
                            // Calculate barycentric coordinates
                            float l0 = det12p / det012;
                            float l1 = det20p / det012;
                            float l2 = det01p / det012;

                            colorBuffer.ColorAt(x, y) = ToColor4UB(l0 * v0.color + l1 * v1.color + l2 * v2.color);
                        }

                    }
                }
            }

            
        }
    }
}