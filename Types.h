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

        inline Vector4f operator+(const Vector4f& v0, const Vector4f& v1)
        {
            return { v0.x + v1.x, v0.y + v1.y, v0.z + v1.z, v0.w + v1.w };
        }

        inline Vector4f operator*(const Vector4f& v, float t)
        {
            return { v.x * t, v.y * t, v.z * t, v.w * t };
        }

        inline Vector4f operator*(float t, const Vector4f& v)
        {
            return v * t;
        }

        // gives the determinate of matrix [ v0.xy v1.xy ] (in xy plane)
        inline float Det2D(const Vector4f& v0, const Vector4f& v1)
        {
            return v0.x * v1.y - v0.y * v1.x;
        }

        struct Matrix4x4f
        {
            float values[16];

            static Matrix4x4f Identity()
            {
                return Matrix4x4f
                {
                    1.f, 0.f, 0.f, 0.f,
                    0.f, 1.f, 0.f, 0.f,
                    0.f, 0.f, 1.f, 0.f,
                    0.f, 0.f, 0.f, 1.f,
                };
            }
        };

        inline Vector4f operator*(Matrix4x4f const& m, Vector4f const& v)
        {
            Vector4f result{ 0.f, 0.f, 0.f, 0.f };

            result.x = m.values[0] * v.x + m.values[1] * v.y + m.values[2] * v.z + m.values[3] * v.w;
            result.y = m.values[4] * v.x + m.values[5] * v.y + m.values[6] * v.z + m.values[7] * v.w;
            result.z = m.values[8] * v.x + m.values[9] * v.y + m.values[10] * v.z + m.values[11] * v.w;
            result.w = m.values[12] * v.x + m.values[13] * v.y + m.values[14] * v.z + m.values[15] * v.w;

            return result;
        }
    }
}