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

#include <madterm/enable_formatting.hpp>
#include <stdexcept>


#ifdef _WIN32
#    define DEFINE_CONSOLEV2_PROPERTIES
#    define WIN32_LEAN_AND_MEAN
#    define NOMINMAX
#    include <windows.h>


#endif

namespace madterm {

namespace {
#ifdef _WIN32
    void init_windows_console()
    {
        // Set output mode to handle virtual terminal sequences
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut == INVALID_HANDLE_VALUE) {
            throw ::std::runtime_error("Unable to obtain std output handle!");
        }

        DWORD dwMode = 0;
        if (!GetConsoleMode(hOut, &dwMode)) {
            throw ::std::runtime_error("Unable to obtain std output mode!");
        }

        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        if (!SetConsoleMode(hOut, dwMode)) {
            throw ::std::runtime_error("Unable to set std output mode!");
        }
    }
#endif

}  // namespace

namespace detail {

    void init_console()
    {
#ifdef _WIN32
        init_windows_console();
#endif
    }
}  // namespace detail

::std::ostream &enable_formatting(::std::ostream &out)
{
    detail::init_console();
    return out;
}

}  // namespace madterm
