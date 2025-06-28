#pragma once

#include"Globals.h"
#include"Types.h"

#include <cstdint>

namespace Rasterizer
{
    using Types::Color4UB;

    // just a wrapper for our pointer Color4UB* pixels.
    struct ColorBuffer
    {
        Color4UB* pixels = nullptr;

        Color4UB& ColorAt(std::uint32_t x, std::uint32_t y) const
        {
            return pixels[x + y * WINDOW_WIDTH];
        }
    };

}

