#pragma once

#include<cstdint>

namespace Rasterizer
{
    namespace Types
    {
        // RGBA color with 4 unsigned bytes
        struct Color4UB
        {
            std::uint8_t r, g, b, a;
        };

        struct Vector3f
        {
            float x, y, z;
        };

        struct Vector4f
        {
            float x, y, z, w;
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

        // Vector3f -> Vector4f with w = 0
        inline Vector4f AsVector4f(const Vector3f& v)
        {
            return { v.x, v.y, v.z, 0.f };
        }

        // converts Vector3f into homogenous coordinate point with w = 1.
        inline Vector4f AsPoint(const Vector3f& v)
        {
            return { v.x, v.y, v.z, 1.f };
        }

        inline Vector4f operator-(const Vector4f& v0, const Vector4f& v1)
        {
            return { v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w };
        }

        // gives the determinate of matrix [ v0.xy v1.xy ] (in xy plane)
        inline float Det2D(const Vector4f& v0, const Vector4f& v1)
        {
            return v0.x * v1.y - v0.y * v1.x;
        }
    }
}