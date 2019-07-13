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

#include <madterm/types.hpp>
#include <sstream>

// clang-format: off
#include <gtest/gtest.h>
// clang-format: on

template<typename T>
class types_tester : public ::testing::Test {
};

namespace {
using test_types = ::testing::Types<
    ::madterm::red,
    ::madterm::blue,
    ::madterm::green,
    ::madterm::x_coord,
    ::madterm::y_coord>;
}

TYPED_TEST_CASE(types_tester, test_types);

TYPED_TEST(types_tester, casting_operator)
{
    auto val = TypeParam{3};
    EXPECT_EQ(static_cast<int>(val), 3);
}

TYPED_TEST(types_tester, equality_operator)
{
    auto a = TypeParam{5};
    auto b = TypeParam{5};
    EXPECT_TRUE(a == b);
}

TYPED_TEST(types_tester, inequality_operator)
{
    auto a = TypeParam{5};
    auto b = TypeParam{6};
    EXPECT_TRUE(a != b);
}

TYPED_TEST(types_tester, less_operator)
{
    auto a = TypeParam{5};
    auto b = TypeParam{6};
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TYPED_TEST(types_tester, less_equal_operator)
{
    auto a = TypeParam{5};
    auto b = TypeParam{6};
    EXPECT_TRUE(a <= b);
    EXPECT_FALSE(b <= a);
}

TYPED_TEST(types_tester, greater_operator)
{
    auto a = TypeParam{7};
    auto b = TypeParam{6};
    EXPECT_TRUE(a > b);
    EXPECT_FALSE(b > a);
}

TYPED_TEST(types_tester, greater_equal_operator)
{
    auto a = TypeParam{7};
    auto b = TypeParam{6};
    EXPECT_TRUE(a >= b);
    EXPECT_FALSE(b >= a);
}

TYPED_TEST(types_tester, pre_increment)
{
    auto val = TypeParam{2};
    ++val;
    EXPECT_EQ(val, TypeParam{3});
}

TYPED_TEST(types_tester, post_increment)
{
    auto val    = TypeParam{7};
    auto before = val++;
    EXPECT_EQ(before, TypeParam{7});
    EXPECT_EQ(val, TypeParam{8});
}

TYPED_TEST(types_tester, pre_decrement)
{
    auto val = TypeParam{2};
    --val;
    EXPECT_EQ(val, TypeParam{1});
}

TYPED_TEST(types_tester, post_decrement)
{
    auto val    = TypeParam{7};
    auto before = val--;
    EXPECT_EQ(before, TypeParam{7});
    EXPECT_EQ(val, TypeParam{6});
}

TYPED_TEST(types_tester, increase_operator)
{
    auto val = TypeParam{5};
    val += TypeParam{3};
    EXPECT_EQ(val, TypeParam{8});
}

TYPED_TEST(types_tester, decrease_operator)
{
    auto val = TypeParam{5};
    val -= TypeParam{3};
    EXPECT_EQ(val, TypeParam{2});
}

TYPED_TEST(types_tester, plus_operator)
{
    auto a = TypeParam{5};
    auto b = TypeParam{3};
    EXPECT_EQ(a + b, TypeParam{8});
}

TYPED_TEST(types_tester, minus_operator)
{
    auto a = TypeParam{5};
    auto b = TypeParam{3};
    EXPECT_EQ(a - b, TypeParam{2});
}

TYPED_TEST(types_tester, stream_inserter)
{
    auto               a = TypeParam{5};
    std::ostringstream str;
    str << a;
    EXPECT_EQ(str.str(), "5");
}
