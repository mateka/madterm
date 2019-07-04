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

#include <madterm/text/modification.hpp>


// clang-format: off
#include <gtest/gtest.h>

// clang-format: on

TEST(modificationTests, insert_spaces)
{
    std::ostringstream stream;
    stream << madterm::text::insert_spaces(2);
    EXPECT_EQ("\x1b[2@", stream.str());
}

TEST(modificationTests, delete_characters)
{
    std::ostringstream stream;
    stream << madterm::text::delete_characters(21);
    EXPECT_EQ("\x1b[21P", stream.str());
}

TEST(modificationTests, erase_characters)
{
    std::ostringstream stream;
    stream << madterm::text::erase_characters(4);
    EXPECT_EQ("\x1b[4X", stream.str());
}

TEST(modificationTests, insert_lines)
{
    std::ostringstream stream;
    stream << madterm::text::insert_lines(7);
    EXPECT_EQ("\x1b[7L", stream.str());
}

TEST(modificationTests, delete_lines)
{
    std::ostringstream stream;
    stream << madterm::text::delete_lines(3);
    EXPECT_EQ("\x1b[3M", stream.str());
}
