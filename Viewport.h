#pragma once

#include"Types.h"

#include <cstdint>

namespace Rasterizer
{
    using Types::Vector4f;

    struct Viewport
    {
        std::int32_t xmin, ymin, xmax, ymax;
    };

    inline Vector4f Apply(const Viewport& viewport, Vector4f v)
    {
        v.x = viewport.xmin + (viewport.xmax - viewport.xmin) * (0.5f + 0.5f * v.x);
        v.y = viewport.ymin + (viewport.ymax - viewport.ymin) * (0.5f - 0.5f * v.y);
        return v;
    }

}