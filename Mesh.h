#pragma once

#include "Types.h"

namespace Rasterizer
{
    using Types::Vector4f;
    using Types::Vector3f;
    using Types::Color4UB;

    struct Mesh
    {
        Vector3f const* vertexBuffer = nullptr;
        std::uint32_t vertexCount = 0;
        Vector4f color = { 1.f, 1.f, 1.f, 1.f };
    };
}