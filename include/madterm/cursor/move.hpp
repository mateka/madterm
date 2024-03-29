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
#include <madterm/types.hpp>


namespace madterm::cursor {

suffixed_terminal_sequence up(unsigned short rows);

suffixed_terminal_sequence down(unsigned short rows);

suffixed_terminal_sequence left(unsigned short columns);

suffixed_terminal_sequence right(unsigned short columns);

suffixed_terminal_sequence column(unsigned short col);

suffixed_terminal_sequence row(unsigned short r);

class move_to : public terminal_sequence<move_to> {
public:
    move_to(x_coord x, y_coord y);

    ::std::ostream &print_sequence(::std::ostream &out) const;

private:
    x_coord x_;
    y_coord y_;
};

}  // namespace madterm::cursor
