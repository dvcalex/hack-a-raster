#pragma once

#include"Vector.h"
#include<cstdint>

namespace Rasterizer
{
    // RGBA color with 4 unsigned bytes
    struct Color4UB
    {
        std::uint8_t r, g, b, a;
    };

    struct Color4ULong
    {
        std::uint16_t r, g, b, a;
    };

    template<typename T>
    T max(T a, T b)
    {
        return (a > b) ? a : b;
    }

    template<typename T>
    T min(T a, T b)
    {
        return (a > b) ? b : a;
    }

    inline Color4UB ToColor4UB(const Vector4f& c)
    {
        Color4UB result;

        result.r = (uint8_t)max(0.f, min(255.f, c.x * 255.f));
        result.g = (uint8_t)max(0.f, min(255.f, c.y * 255.f));
        result.b = (uint8_t)max(0.f, min(255.f, c.z * 255.f));
        result.a = (uint8_t)max(0.f, min(255.f, c.w * 255.f));

        return result;
    }

    // Caution: May lose precision
    inline Color4UB ToColor4UB(const Color4ULong& c)
    {
        return
        {
            static_cast<std::uint8_t>(c.r),
            static_cast<std::uint8_t>(c.g),
            static_cast<std::uint8_t>(c.b),
            static_cast<std::uint8_t>(c.a)
        };
    }

    inline Color4ULong ToColor4ULong(const Color4UB& c)
    {
        return
        {
            static_cast<std::uint16_t>(c.r),
            static_cast<std::uint16_t>(c.g),
            static_cast<std::uint16_t>(c.b),
            static_cast<std::uint16_t>(c.a)
        };
    }

    inline Color4ULong operator+(const Color4ULong& c0, const Color4ULong& c1)  
    {  
        return 
        {  
            static_cast<std::uint16_t>(c0.r + c1.r),  
            static_cast<std::uint16_t>(c0.g + c1.g),  
            static_cast<std::uint16_t>(c0.b + c1.b),  
            static_cast<std::uint16_t>(c0.a + c1.a)  
        };  
    }

    inline Color4ULong operator/(const Color4ULong& c0, int t)
    {
        return
        {
            static_cast<std::uint16_t>(c0.r / t),
            static_cast<std::uint16_t>(c0.g / t),
            static_cast<std::uint16_t>(c0.b / t),
            static_cast<std::uint16_t>(c0.a / t)
        };
    }

}