#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <madterm/cursor/mode.hpp>
#include <madterm/cursor/move.hpp>
#include <madterm/enable_formatting.hpp>
#include <madterm/screen_buffer/screen_buffer.hpp>
#include <madterm/text/charset.hpp>
#include <madterm/text/effects.hpp>
#include <madterm/text/modification.hpp>
#include <madterm/window/window.hpp>
#include <thread>
#include <type_traits>

namespace {
class hline : public madterm::i_terminal_sequence {
public:
    hline(::madterm::x_coord x, ::madterm::y_coord y, ::madterm::x_coord len)
        : x_{x}, y_{y}, len_{len}
    {
    }

    ::std::ostream &operator()(::std::ostream &out) const override
    {
        out << madterm::cursor::move_to(x_, y_);
        for (int i = 0; i < len_; ++i)
            out << madterm::text::shapes::hline;
        return out;
    }

private:
    ::madterm::x_coord x_;
    ::madterm::y_coord y_;
    int                len_;
};

class vline : public madterm::i_terminal_sequence {
public:
    vline(::madterm::x_coord x, ::madterm::y_coord y, ::madterm::y_coord len)
        : x_{x}, y_{y}, len_{len}
    {
    }

    ::std::ostream &operator()(::std::ostream &out) const override
    {
        ::madterm::y_coord y = y_;
        for (int i = 0; i < len_; ++i)
            out << madterm::cursor::move_to(x_, y++)
                << madterm::text::shapes::vline;
        return out;
    }

private:
    ::madterm::x_coord x_;
    ::madterm::y_coord y_;
    int                len_;
};

class frame : public madterm::i_terminal_sequence {
public:
    frame(
        ::madterm::x_coord x,
        ::madterm::y_coord y,
        ::madterm::x_coord width,
        ::madterm::y_coord height)
        : x_{x}, y_{y}, width_{width}, height_{height}
    {
    }

    ::std::ostream &operator()(::std::ostream &out) const override
    {
        return out << hline(x_, y_, width_) << hline(x_, y_ + height_, width_)
                   << vline(x_, y_, height_) << vline(x_ + width_, y_, height_)
                   << madterm::cursor::move_to(x_, y_)
                   << madterm::text::shapes::top_left_corner
                   << madterm::cursor::move_to(x_ + width_, y_)
                   << madterm::text::shapes::top_right_corner
                   << madterm::cursor::move_to(x_, y_ + height_)
                   << madterm::text::shapes::bottom_left_corner
                   << madterm::cursor::move_to(x_ + width_, y_ + height_)
                   << madterm::text::shapes::bottom_right_corner;
    }

private:
    ::madterm::x_coord x_;
    ::madterm::y_coord y_;
    ::madterm::x_coord width_;
    ::madterm::y_coord height_;
};

}  // namespace

int main()
{
    using namespace madterm::literals;

    std::cout << madterm::enable_formatting << madterm::screen_buffer::alternate
              << madterm::text::foreground_colour(madterm::text::colours::green)
              << madterm::text::background_colour(75_r, 75_g, 75_b)
              << madterm::cursor::blink(false) << madterm::cursor::show(false)
              << madterm::window::title("clock") << std::endl;
    while (true) {
        auto now  = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        auto tm   = *std::localtime(&time);
        std::cout << madterm::cursor::move_to(69_x, 10_y)
                  << madterm::text::erase_characters(22)
                  << madterm::cursor::move_to(69_x, 11_y)
                  << madterm::text::erase_characters(22)
                  << madterm::cursor::move_to(69_x, 12_y)
                  << madterm::text::erase_characters(22) << madterm::text::lines
                  << frame(68_x, 9_y, 22_x, 4_y) << madterm::text::ascii
                  << madterm::cursor::move_to(70_x, 12_y)
                  << std::put_time(&tm, "%Y-%m-%d %H-%M-%S")
                  << madterm::cursor::move_to(76_x, 10_y)
                  << "Time:" << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds{1});
    }
    std::cout << madterm::text::clear_formatting << madterm::screen_buffer::main
              << madterm::soft_reset << std::endl;
}
