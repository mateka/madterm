#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <madterm/cursor/mode.hpp>
#include <madterm/cursor/move.hpp>
#include <madterm/enable_formatting.hpp>
#include <madterm/screen_buffer/screen_buffer.hpp>
#include <madterm/text/effects.hpp>
#include <madterm/text/modification.hpp>
#include <madterm/window/window.hpp>
#include <thread>


int main()
{
    using namespace madterm::literals;

    std::cout << madterm::enable_formatting << madterm::screen_buffer::alternate
              << madterm::text::foreground_colour(madterm::text::colours::green)
              << madterm::text::background_colour(75_r, 75_g, 75_b) << "Test"
              << madterm::text::clear_formatting
              << madterm::cursor::blink(false) << madterm::cursor::show(false)
              << madterm::window::title("clock") << " " << std::endl;
    while (true) {
        auto now  = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        auto tm   = *std::localtime(&time);
        std::cout << madterm::cursor::move_to(69_x, 12_y)
                  << "xxxxxxxxxxxxxxxxxxx"
                  << madterm::cursor::move_to(70_x, 12_y)
                  << madterm::text::insert_spaces(30)
                  << std::put_time(&tm, "%c")
                  << madterm::cursor::move_to(70_x, 10_y)
                  << "Time:" << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds{1});
    }
    std::cout << madterm::screen_buffer::main << std::endl;
}