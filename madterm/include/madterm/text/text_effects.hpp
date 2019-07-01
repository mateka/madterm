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
        explicit text_effect(int effect);
    };

    class predefined_colour : public terminal_sequence<predefined_colour> {
    public:
        predefined_colour(colours c, int base_value);

        ::std::ostream &print_sequence(::std::ostream &out) const;

    private:
        colours colour_;
        int     base_value_;
    };

    class rgba_colour : public terminal_sequence<rgba_colour> {
    public:
        rgba_colour(
            unsigned char r, unsigned char g, unsigned char b, int base_value);

        ::std::ostream &print_sequence(::std::ostream &out) const;

    private:
        int           base_value_;
        unsigned char red_;
        unsigned char green_;
        unsigned char blue_;
    };
}  // namespace detail

detail::predefined_colour foreground_colour(colours c);

detail::rgba_colour
foreground_colour(unsigned char r, unsigned char g, unsigned char b);

detail::predefined_colour background_colour(colours c);

detail::rgba_colour
background_colour(unsigned char r, unsigned char g, unsigned char b);

::std::ostream &clear_formatting(::std::ostream &out);

::std::ostream &bold(::std::ostream &out);

class underline : public detail::text_effect {
public:
    explicit underline(bool turn_on);
};

}  // namespace madterm::text
