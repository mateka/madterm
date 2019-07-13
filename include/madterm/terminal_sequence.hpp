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

#include <iosfwd>
#include <string>
#include <type_traits>

namespace madterm {

class i_terminal_sequence {
public:
    virtual ::std::ostream &operator()(::std::ostream &out) const = 0;
};

template<typename Derived>
class terminal_sequence : public i_terminal_sequence {
public:
    explicit terminal_sequence(::std::string seq = "\x1b[")
        : seq_{::std::move(seq)}
    {
    }

    ::std::ostream &operator()(::std::ostream &out) const override
    {
        out << seq_;
        return derived().print_sequence(out);
    }

private:
    Derived &      derived() { return static_cast<Derived &>(*this); }
    Derived const &derived() const
    {
        return static_cast<Derived const &>(*this);
    }

    ::std::string seq_;
};

template<typename Manipulator>
inline ::std::enable_if_t<
    ::std::is_base_of_v<i_terminal_sequence, Manipulator>,
    ::std::ostream &>
operator<<(::std::ostream &out, Manipulator manip)
{
    return manip(out);
}

class prefixed_terminal_sequence
    : public terminal_sequence<prefixed_terminal_sequence> {
public:
    prefixed_terminal_sequence(unsigned short value, char code);

    ::std::ostream &print_sequence(::std::ostream &out) const;

private:
    unsigned short value_;
    char           code_;
};

class suffixed_terminal_sequence
    : public terminal_sequence<suffixed_terminal_sequence> {
public:
    suffixed_terminal_sequence(unsigned short value, char code);

    ::std::ostream &print_sequence(::std::ostream &out) const;

private:
    unsigned short value_;
    char           code_;
};

class simple_terminal_sequence
    : public terminal_sequence<simple_terminal_sequence> {
public:
    simple_terminal_sequence(char prefix, unsigned short value, char suffix);

    ::std::ostream &print_sequence(::std::ostream &out) const;

private:
    unsigned short value_;
    char           prefix_;
    char           suffix_;
};

class string_sequence : public terminal_sequence<string_sequence> {
public:
    explicit string_sequence(::std::string code, ::std::string seq = "\x1b[");

    ::std::ostream &print_sequence(::std::ostream &out) const;

private:
    ::std::string code_;
};

::std::ostream &soft_reset(::std::ostream &out);

}  // namespace madterm
