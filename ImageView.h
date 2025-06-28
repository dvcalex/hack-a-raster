#pragma once

#include"Globals.h"
#include"Color.h"

#include <cstdint>

namespace Rasterizer
{
    // just a wrapper for our pointer Color4UB* pixels.
    template <typename Pixel>
    struct ImageView
    {
        Pixel* pixels = nullptr;

        explicit operator bool() const
        {
            return pixels != nullptr;
        }

        Pixel& At(std::uint32_t x, std::uint32_t y) const
        {
            return pixels[x + y * WINDOW_WIDTH];
        }
    };

}

