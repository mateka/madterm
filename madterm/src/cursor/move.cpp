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
#include <madterm/cursor/move.hpp>


namespace madterm::cursor {

suffixed_terminal_sequence up(short int rows)
{
    return suffixed_terminal_sequence{rows, 'A'};
}

suffixed_terminal_sequence down(short int rows)
{
    return suffixed_terminal_sequence{rows, 'B'};
}

suffixed_terminal_sequence left(short int columns)
{
    return suffixed_terminal_sequence{columns, 'D'};
}

suffixed_terminal_sequence right(short int columns)
{
    return suffixed_terminal_sequence{columns, 'C'};
}

suffixed_terminal_sequence column(short int col)
{
    return suffixed_terminal_sequence{col, 'G'};
}

suffixed_terminal_sequence row(short int r)
{
    return suffixed_terminal_sequence{r, 'd'};
}

move_to::move_to(short int x, short int y) : x_{x}, y_{y} {}

::std::ostream &move_to::print_sequence(::std::ostream &out) const
{
    return out << y_ << ';' << x_ << 'H';
}

}  // namespace madterm::cursor
