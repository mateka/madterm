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

#include <madterm/window/window.hpp>
#include <sstream>

// clang-format: off
#include <gtest/gtest.h>


// clang-format: on

TEST(windowTests, title_char)
{
    std::ostringstream stream;
    stream << madterm::window::title("Title");
    EXPECT_EQ("\x1b]0;Title\x07", stream.str());
}

TEST(windowTests, title_wchar)
{
    std::wostringstream stream;
    stream << madterm::window::title("Title");
    EXPECT_EQ(L"\x1b]0;Title\x07", stream.str());
}

TEST(windowTests, wide)
{
    std::ostringstream stream;
    stream << madterm::window::wide(true);
    EXPECT_EQ("\x1b[?3h", stream.str());
}

TEST(windowTests, narrow)
{
    std::ostringstream stream;
    stream << madterm::window::wide(false);
    EXPECT_EQ("\x1b[?3l", stream.str());
}
