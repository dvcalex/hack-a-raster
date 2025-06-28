#pragma once

#include"ImageView.h"
#include"Color.h"

namespace Rasterizer
{
    struct Framebuffer
    {
        ImageView<Color4UB> color;
        ImageView<std::uint32_t> depth;
    };

}