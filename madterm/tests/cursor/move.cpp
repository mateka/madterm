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

#include <madterm/cursor/move.hpp>


// clang-format: off
#include <gtest/gtest.h>

// clang-format: on

TEST(moveTests, up)
{
    std::ostringstream stream;
    stream << madterm::cursor::up(2);
    EXPECT_EQ("\x1b[2A", stream.str());
}

TEST(moveTests, down)
{
    std::ostringstream stream;
    stream << madterm::cursor::down(5);
    EXPECT_EQ("\x1b[5B", stream.str());
}

TEST(moveTests, left)
{
    std::ostringstream stream;
    stream << madterm::cursor::left(7);
    EXPECT_EQ("\x1b[7D", stream.str());
}

TEST(moveTests, right)
{
    std::ostringstream stream;
    stream << madterm::cursor::right(3);
    EXPECT_EQ("\x1b[3C", stream.str());
}

TEST(moveTests, column)
{
    std::ostringstream stream;
    stream << madterm::cursor::column(13);
    EXPECT_EQ("\x1b[13G", stream.str());
}

TEST(moveTests, row)
{
    std::ostringstream stream;
    stream << madterm::cursor::row(77);
    EXPECT_EQ("\x1b[77d", stream.str());
}

TEST(moveTests, move_to)
{
    std::ostringstream stream;
    stream << madterm::cursor::move_to(8, 4);
    EXPECT_EQ("\x1b[4;8H", stream.str());
}
