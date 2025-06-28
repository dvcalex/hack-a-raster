#pragma once

#include "Types.h"
#include "VertexAttribute.h"

namespace Rasterizer
{
    using Types::Vector4f;
    using Types::Vector3f;
    using Types::Color4UB;

    struct Mesh
    {
        Attribute<Vector3f> vertices = {};
        Attribute<Vector4f> colors = {};
        std::uint32_t vertexCount = 0;
    };
}