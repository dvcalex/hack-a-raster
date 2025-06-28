#pragma once

#include"Vector.h"

#include<cmath>

namespace Rasterizer
{
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
        static Matrix4x4f Scale(Vector3f const& s)
        {
            return Matrix4x4f
            {
                s.x, 0.f, 0.f, 0.f,
                0.f, s.y, 0.f, 0.f,
                0.f, 0.f, s.z, 0.f,
                0.f, 0.f, 0.f, 1.f,
            };
        }
        static Matrix4x4f Scale(float s)
        {
            return Scale(Vector3f{ s, s, s });
        }
        static Matrix4x4f Translate(Vector3f const& s)
        {
            return Matrix4x4f
            {
                1.f, 0.f, 0.f, s.x,
                0.f, 1.f, 0.f, s.y,
                0.f, 0.f, 1.f, s.z,
                0.f, 0.f, 0.f, 1.f,
            };
        }
        static Matrix4x4f RotateXY(float angle)
        {
            float cos = std::cos(angle);
            float sin = std::sin(angle);

            return Matrix4x4f
            {
                cos, -sin, 0.f, 0.f,
                sin,  cos, 0.f, 0.f,
                0.f,  0.f, 1.f, 0.f,
                0.f,  0.f, 0.f, 1.f,
            };
        }
        static Matrix4x4f RotateYZ(float angle)
        {
            float cos = std::cos(angle);
            float sin = std::sin(angle);

            return Matrix4x4f
            {
                1.f, 0.f,  0.f, 0.f,
                0.f, cos, -sin, 0.f,
                0.f, sin,  cos, 0.f,
                0.f, 0.f,  0.f, 1.f,
            };
        }
        static Matrix4x4f RotateZX(float angle)
        {
            float cos = std::cos(angle);
            float sin = std::sin(angle);

            return Matrix4x4f
            {
                 cos, 0.f, sin, 0.f,
                 0.f, 1.f, 0.f, 0.f,
                -sin, 0.f, cos, 0.f,
                 0.f, 0.f, 0.f, 1.f,
            };
        }
        static Matrix4x4f Perspective(float near, float far, float fovY, float aspect_ratio)
        {
            float top = near * std::tan(fovY / 2.f);
            float right = top * aspect_ratio;

            return Matrix4x4f
            {
                near / right, 0.f, 0.f, 0.f,
                0.f, near / top, 0.f, 0.f,
                0.f, 0.f, -(far + near) / (far - near), -2.f * far * near / (far - near),
                0.f, 0.f, -1.f, 0.f,
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

    inline Matrix4x4f operator * (Matrix4x4f const& m1, Matrix4x4f const& m2)
    {
        Matrix4x4f result
        {
            0.f, 0.f, 0.f, 0.f,
            0.f, 0.f, 0.f, 0.f,
            0.f, 0.f, 0.f, 0.f,
            0.f, 0.f, 0.f, 0.f,
        };

        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                for (int k = 0; k < 4; ++k)
                    result.values[4 * i + j] += m1.values[4 * i + k] * m2.values[4 * k + j];

        return result;
    }
}