#pragma once

#include"Types.h"
#include"ColorBuffer.h"
#include"DrawCommand.h"

namespace Rasterizer
{
    using Types::Vector4f;
    using Types::Color4UB;

    void Clear(const ColorBuffer& colorBuffer, const Vector4f& color);

    void Draw(const ColorBuffer& colorBuffer, const DrawCommand& command);
}