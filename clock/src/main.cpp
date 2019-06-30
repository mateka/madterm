#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <madterm/enable_formatting.hpp>
#include <madterm/text/text_effects.hpp>
#include <thread>

int main()
{
    std::cout << madterm::enable_formatting
              << madterm::text::foreground_colour(madterm::text::colours::green)
              << madterm::text::background_colour(75, 75, 75) << "Test"
              << madterm::text::clear_formatting << std::endl;
    while (true) {
        auto now  = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        auto tm   = *std::localtime(&time);
        std::cout << "\t\t\t\t\t\t\t" << std::put_time(&tm, "%c") << '\r'
                  << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds{1});
    }
    std::cout << std::endl;
}