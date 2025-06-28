#pragma once

#include"Globals.h"
#include"ImageView.h"
#include <cstdint>
#include <memory>

namespace Rasterizer
{
    template <typename Pixel>
    struct Image
    {
        std::unique_ptr<Pixel[]> pixels;

        explicit operator bool() const
        {
            return pixels != nullptr;
        }

        static Image Allocate()
        {
            return Image
            {
                std::make_unique<Pixel[]>(WINDOW_WIDTH * WINDOW_HEIGHT)
            };
        }

        ImageView<Pixel> View()
        {
            return ImageView<Pixel>
            {
                pixels.get()
            };
        }
    };

}