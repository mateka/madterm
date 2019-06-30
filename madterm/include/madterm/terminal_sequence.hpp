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
};

template<typename Derived>
class terminal_sequence : public i_terminal_sequence {
public:
    explicit terminal_sequence(::std::string seq = "\x1b[")
        : seq_{::std::move(seq)}
    {
    }

    template<typename CharT, typename Traits = std::char_traits<CharT>>
    ::std::basic_ostream<CharT, Traits> &
    operator()(::std::basic_ostream<CharT, Traits> &out) const
    {
        thread_local const ::std::basic_string<CharT> stream_seq{
            ::std::cbegin(seq_), ::std::cend(seq_)};
        out << stream_seq;
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

template<
    typename Manipulator,
    typename CharT,
    typename Traits = std::char_traits<CharT>>
::std::enable_if_t<
    ::std::is_base_of_v<i_terminal_sequence, Manipulator>,
    ::std::basic_ostream<CharT, Traits> &>
operator<<(::std::basic_ostream<CharT, Traits> &out, Manipulator manip)
{
    return manip(out);
}

class prefixed_terminal_sequence
    : public terminal_sequence<prefixed_terminal_sequence> {
public:
    prefixed_terminal_sequence(short int value, char code)
        : value_{value}, code_{code}
    {
    }

    template<typename CharT, typename Traits = std::char_traits<CharT>>
    ::std::basic_ostream<CharT, Traits> &
    print_sequence(::std::basic_ostream<CharT, Traits> &out) const
    {
        return out << code_ << value_;
    }

private:
    short int value_;
    char      code_;
};

class suffixed_terminal_sequence
    : public terminal_sequence<suffixed_terminal_sequence> {
public:
    suffixed_terminal_sequence(short int value, char code)
        : value_{value}, code_{code}
    {
    }

    template<typename CharT, typename Traits = std::char_traits<CharT>>
    ::std::basic_ostream<CharT, Traits> &
    print_sequence(::std::basic_ostream<CharT, Traits> &out) const
    {
        return out << value_ << code_;
    }

private:
    short int value_;
    char      code_;
};

class simple_terminal_sequence
    : public terminal_sequence<simple_terminal_sequence> {
public:
    simple_terminal_sequence(char prefix, short int value, char suffix)
        : value_{value}, prefix_{prefix}, suffix_{suffix}
    {
    }

    template<typename CharT, typename Traits = std::char_traits<CharT>>
    ::std::basic_ostream<CharT, Traits> &
    print_sequence(::std::basic_ostream<CharT, Traits> &out) const
    {
        return out << prefix_ << value_ << suffix_;
    }

private:
    short int value_;
    char      prefix_;
    char      suffix_;
};

}  // namespace madterm
