#pragma once

namespace Rasterizer
{

    enum class CullMode
    {
        None,
        Clockwise,
        CounterClockwise,
    };

    enum class DepthTestMode
    {
        Never,
        Always,
        Less,
        LessEqual,
        Greater,
        GreaterEqual,
        Equal,
        NotEqual,
    };

    struct DepthSettings
    {
        bool write = true;
        DepthTestMode mode = DepthTestMode::Always;
    };
}