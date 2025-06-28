#pragma once

namespace Rasterizer
{
    struct Vector3f
    {
        float x, y, z;
    };

    struct Vector4f
    {
        float x, y, z, w;
    };

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

}