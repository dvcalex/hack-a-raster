#pragma once

#include"Vector.h"
#include"Color.h"
#include"ColorBuffer.h"
#include"DrawCommand.h"
#include"Viewport.h"

namespace Rasterizer
{
    void Clear(const ColorBuffer& colorBuffer, const Vector4f& color);

    void Draw(const ColorBuffer& colorBuffer,
        const Viewport& viewport,
        const DrawCommand& command);
}