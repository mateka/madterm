/*
 * Copyright 2019 mateka
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
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

#include <madterm/terminal_sequence.hpp>
#include <sstream>

// clang-format: off
#include <gtest/gtest.h>


// clang-format: on

class dummy : public madterm::terminal_sequence<dummy> {
public:
    ::std::ostream &print_sequence(::std::ostream &out) const
    {
        return out << "dummy";
    }
};

class dummy2 : public madterm::terminal_sequence<dummy2> {
public:
    dummy2() : madterm::terminal_sequence<dummy2>{"dummy2"} {}
    ::std::ostream &print_sequence(::std::ostream &out) const
    {
        return out << "dummy";
    }
};

TEST(terminal_sequenceTests, correct_escape_sequence)
{
    std::ostringstream stream;
    stream << dummy();
    EXPECT_EQ("\x1b[dummy", stream.str());
}

TEST(terminal_sequenceTests, two_manipulators)
{
    std::ostringstream stream;
    stream << dummy() << dummy2();
    EXPECT_EQ("\x1b[dummydummy2dummy", stream.str());
}
