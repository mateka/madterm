#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <madterm/cursor/mode.hpp>
#include <madterm/cursor/move.hpp>
#include <madterm/enable_formatting.hpp>
#include <madterm/text/text_effects.hpp>
#include <madterm/window/window.hpp>
#include <thread>


int main()
{
    std::cout << madterm::enable_formatting
              << madterm::text::foreground_colour(madterm::text::colours::green)
              << madterm::text::background_colour(75, 75, 75) << "Test"
              << madterm::text::clear_formatting
              << madterm::cursor::blink(false) << madterm::cursor::show(false)
              << madterm::window::title("clock") << madterm::window::wide(false)
              << " " << std::endl;
    while (true) {
        auto now  = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        auto tm   = *std::localtime(&time);
        std::cout << madterm::cursor::move_to(69, 12) << "xxxxxxxxxxxxxxxxxxx"
                  << madterm::cursor::move_to(70, 12)
                  << std::put_time(&tm, "%c")
                  << madterm::cursor::move_to(70, 10) << "Time:" << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds{1});
    }
    std::cout << std::endl;
}