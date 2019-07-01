/*
 * Copyright 2019 mateka
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files(the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 * - The above copyright notice and this permission notice shall be included
 *   in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
 * THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#pragma once

#include <iostream>


namespace madterm {
namespace detail {
    template<typename T, typename Tag>
    class tagged_type {
    public:
        explicit constexpr tagged_type(T value) : value_{value} {}
        constexpr tagged_type(tagged_type const &) = default;
        constexpr tagged_type(tagged_type &&)      = default;
        constexpr tagged_type &operator=(tagged_type const &) = default;
        constexpr tagged_type &operator=(tagged_type &&) = default;

        explicit constexpr operator T() const { return value_; }
        template<typename U>
        explicit constexpr operator U() const
        {
            return static_cast<U>(value_);
        }

    private:
        T value_;
    };

    template<typename T, typename Tag>
    bool operator==(tagged_type<T, Tag> const &a, tagged_type<T, Tag> const &b)
    {
        return static_cast<T>(a) == static_cast<T>(b);
    }

    template<typename T, typename Tag>
    bool operator!=(tagged_type<T, Tag> const &a, tagged_type<T, Tag> const &b)
    {
        return !(a == b);
    }

    template<typename T, typename Tag>
    ::std::ostream &
    operator<<(::std::ostream &out, tagged_type<T, Tag> const &tt)
    {
        return out << static_cast<T>(tt);
    }

    struct red_tag {
    };
    struct green_tag {
    };
    struct blue_tag {
    };

    struct x_coord_tag {
    };
    struct y_coord_tag {
    };
}  // namespace detail
using red   = detail::tagged_type<unsigned char, detail::red_tag>;
using green = detail::tagged_type<unsigned char, detail::green_tag>;
using blue  = detail::tagged_type<unsigned char, detail::blue_tag>;

using x_coord = detail::tagged_type<short, detail::x_coord_tag>;
using y_coord = detail::tagged_type<short, detail::y_coord_tag>;

namespace literals {
    inline constexpr red operator"" _r(unsigned long long v)
    {
        return red{static_cast<unsigned char>(v)};
    }

    inline constexpr green operator"" _g(unsigned long long v)
    {
        return green{static_cast<unsigned char>(v)};
    }

    inline constexpr blue operator"" _b(unsigned long long v)
    {
        return blue{static_cast<unsigned char>(v)};
    }

    inline constexpr x_coord operator"" _x(unsigned long long v)
    {
        return x_coord{static_cast<short>(v)};
    }

    inline constexpr y_coord operator"" _y(unsigned long long v)
    {
        return y_coord{static_cast<short>(v)};
    }
}  // namespace literals

using namespace literals;

}  // namespace madterm
