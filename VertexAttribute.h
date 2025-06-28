#pragma once

#include <cstdint>

namespace Rasterizer
{

    // Defines a vertex attribute
    template <typename T>
    struct Attribute
    {
        void* pointer = nullptr;

        // distance in bytes between two values of this attribute corresponding to two consecutive vertices.
        std::uint32_t stride = sizeof(T);

        // Get attribute by vertex index
        T const& operator[] (std::uint32_t i) const
        {
            return *(T const*)((char const*)(pointer)+stride * i);
        }
    };

}