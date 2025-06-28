#pragma once

#include "Vector.h"
#include "Color.h"
#include "VertexAttribute.h"

namespace Rasterizer
{
    struct Mesh
    {
        Attribute<Vector3f> vertices = {};
        Attribute<Vector4f> colors = {};
        std::uint32_t const* indices = nullptr;
        // Number of indices in our index array. If indices is null, count is the number of vertices.
        std::uint32_t count = 0; 
    };
}