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


namespace madterm::window {

class title : public terminal_sequence<title> {
public:
    title(::std::string window_title)
        : terminal_sequence<title>{"\x1b]0;"}, title_{window_title}
    {
    }

    template<typename CharT, typename Traits = std::char_traits<CharT>>
    ::std::basic_ostream<CharT, Traits> &
    print_sequence(::std::basic_ostream<CharT, Traits> &out) const
    {
        thread_local const ::std::basic_string<CharT> stream_seq{
            ::std::cbegin(title_), ::std::cend(title_)};
        return out << stream_seq << "\x07";
    }

private:
    ::std::string title_;
};

inline simple_terminal_sequence wide(bool value)
{
    return simple_terminal_sequence{'?', 3, value ? 'h' : 'l'};
}

}  // namespace madterm::window
