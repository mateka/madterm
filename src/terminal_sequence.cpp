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
#include <madterm/terminal_sequence.hpp>


namespace madterm {
prefixed_terminal_sequence::prefixed_terminal_sequence(
    short int value, char code)
    : value_{value}, code_{code}
{
}

::std::ostream &
prefixed_terminal_sequence::print_sequence(::std::ostream &out) const
{
    return out << code_ << value_;
}

suffixed_terminal_sequence::suffixed_terminal_sequence(
    short int value, char code)
    : value_{value}, code_{code}
{
}

::std::ostream &
suffixed_terminal_sequence::print_sequence(::std::ostream &out) const
{
    return out << value_ << code_;
}

simple_terminal_sequence::simple_terminal_sequence(
    char prefix, short int value, char suffix)
    : value_{value}, prefix_{prefix}, suffix_{suffix}
{
}

::std::ostream &
simple_terminal_sequence::print_sequence(::std::ostream &out) const
{
    return out << prefix_ << value_ << suffix_;
}

}  // namespace madterm
