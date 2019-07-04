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

#include <iostream>
#include <madterm/text/effects.hpp>

namespace madterm::text {

namespace detail {
    text_effect::text_effect(int effect)
        : suffixed_terminal_sequence{effect, 'm'}
    {
    }

    predefined_colour::predefined_colour(colours c, int base_value)
        : colour_{c}, base_value_{base_value}
    {
    }

    ::std::ostream &predefined_colour::print_sequence(::std::ostream &out) const
    {
        return out << base_value_ + static_cast<int>(colour_) << 'm';
    }

    rgba_colour::rgba_colour(red r, green g, blue b, int base_value)
        : base_value_{base_value}, red_{r}, green_{g}, blue_{b}
    {
    }

    ::std::ostream &rgba_colour::print_sequence(::std::ostream &out) const
    {
        return out << base_value_ << ";2;" << static_cast<int>(red_) << ';'
                   << static_cast<int>(green_) << ';' << static_cast<int>(blue_)
                   << 'm';
    }

}  // namespace detail

detail::predefined_colour foreground_colour(colours c)
{
    return {c, 30};
}

detail::rgba_colour foreground_colour(red r, green g, blue b)
{
    return {r, g, b, 38};
}

detail::predefined_colour background_colour(colours c)
{
    return {c, 40};
}

detail::rgba_colour background_colour(red r, green g, blue b)
{
    return {r, g, b, 48};
}

::std::ostream &clear_formatting(::std::ostream &out)
{
    return detail::text_effect{0}(out);
}

::std::ostream &bold(::std::ostream &out)
{
    return detail::text_effect{1}(out);
}

underline::underline(bool turn_on) : detail::text_effect{turn_on ? 4 : 24} {}

}  // namespace madterm::text
