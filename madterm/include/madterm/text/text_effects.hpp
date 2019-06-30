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

#include <madterm/terminal_sequence.hpp>

namespace madterm::text {

enum class colours : int {
    black          = 0,
    red            = 1,
    green          = 2,
    yellow         = 3,
    blue           = 4,
    magenta        = 5,
    cyan           = 6,
    white          = 7,
    default_colour = 9,
    bright_black   = 60,
    bright_red     = 61,
    bright_green   = 62,
    bright_yellow  = 63,
    bright_blue    = 64,
    bright_magenta = 65,
    bright_cyan    = 66,
    bright_white   = 67,
};

namespace detail {
    class text_effect : public suffixed_terminal_sequence {
    public:
        explicit text_effect(int effect)
            : suffixed_terminal_sequence{effect, 'm'}
        {
        }
    };

    class predefined_colour : public terminal_sequence<predefined_colour> {
    public:
        predefined_colour(colours c, int base_value)
            : colour_{c}, base_value_{base_value}
        {
        }

        template<typename CharT, typename Traits = std::char_traits<CharT>>
        ::std::basic_ostream<CharT, Traits> &
        print_sequence(::std::basic_ostream<CharT, Traits> &out) const
        {
            return out << base_value_ + static_cast<int>(colour_) << 'm';
        }

    private:
        colours colour_;
        int     base_value_;
    };

    class rgba_colour : public terminal_sequence<rgba_colour> {
    public:
        rgba_colour(
            unsigned char r, unsigned char g, unsigned char b, int base_value)
            : base_value_{base_value}, red_{r}, green_{g}, blue_{b}
        {
        }

        template<typename CharT, typename Traits = std::char_traits<CharT>>
        ::std::basic_ostream<CharT, Traits> &
        print_sequence(::std::basic_ostream<CharT, Traits> &out) const
        {
            return out << base_value_ << ";2;" << static_cast<int>(red_) << ';'
                       << static_cast<int>(green_) << ';'
                       << static_cast<int>(blue_) << 'm';
        }

    private:
        int           base_value_;
        unsigned char red_;
        unsigned char green_;
        unsigned char blue_;
    };
}  // namespace detail

inline detail::predefined_colour foreground_colour(colours c)
{
    return {c, 30};
}

inline detail::rgba_colour
foreground_colour(unsigned char r, unsigned char g, unsigned char b)
{
    return {r, g, b, 38};
}

inline detail::predefined_colour background_colour(colours c)
{
    return {c, 40};
}

inline detail::rgba_colour
background_colour(unsigned char r, unsigned char g, unsigned char b)
{
    return {r, g, b, 48};
}

template<typename CharT, typename Traits = std::char_traits<CharT>>
inline ::std::basic_ostream<CharT, Traits> &
clear_formatting(::std::basic_ostream<CharT, Traits> &out)
{
    return detail::text_effect{0}(out);
}

template<typename CharT, typename Traits = std::char_traits<CharT>>
inline ::std::basic_ostream<CharT, Traits> &
bold(::std::basic_ostream<CharT, Traits> &out)
{
    return detail::text_effect{1}(out);
}

class underline : public detail::text_effect {
public:
    explicit underline(bool turn_on) : detail::text_effect{turn_on ? 4 : 24} {}
};

}  // namespace madterm::text
