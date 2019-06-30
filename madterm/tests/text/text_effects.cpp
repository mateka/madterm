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

#include <madterm/text/text_effects.hpp>
#include <sstream>


// clang-format: off
#include <gtest/gtest.h>

// clang-format: on

TEST(colourTests, predefined_foreground_colour)
{
    std::ostringstream stream;
    stream << madterm::text::foreground_colour(madterm::text::colours::red);
    EXPECT_EQ("\x1b[31m", stream.str());
}

TEST(colourTests, custom_foreground_colour)
{
    std::ostringstream stream;
    stream << madterm::text::foreground_colour(125, 17, 55);
    EXPECT_EQ("\x1b[38;2;125;17;55m", stream.str());
}

TEST(colourTests, predefined_background_colour)
{
    std::ostringstream stream;
    stream << madterm::text::background_colour(madterm::text::colours::green);
    EXPECT_EQ("\x1b[42m", stream.str());
}

TEST(colourTests, custom_background_colour)
{
    std::ostringstream stream;
    stream << madterm::text::background_colour(1, 2, 3);
    EXPECT_EQ("\x1b[48;2;1;2;3m", stream.str());
}

TEST(colourTests, bold)
{
    std::ostringstream stream;
    stream << madterm::text::bold;
    EXPECT_EQ("\x1b[1m", stream.str());
}

TEST(colourTests, underline)
{
    std::ostringstream stream;
    stream << madterm::text::underline(true);
    EXPECT_EQ("\x1b[4m", stream.str());
}

TEST(colourTests, no_underline)
{
    std::ostringstream stream;
    stream << madterm::text::underline(false);
    EXPECT_EQ("\x1b[24m", stream.str());
}

TEST(colourTests, clear)
{
    std::ostringstream stream;
    stream << madterm::text::clear_formatting;
    EXPECT_EQ("\x1b[0m", stream.str());
}
