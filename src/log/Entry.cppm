module;

#include <cstdint>
#include <filesystem>
#include <string>
#include <thread>

export module fwd.log:Entry;

import :Level;


namespace fwd::log {

export
struct Entry {
    Level level;
    std::string message;
    std::string logger_name;
    std::uint64_t line = 0;
    std::uint64_t column = 0;
    std::uint64_t process_id = 0;
    std::thread::id thread_id = std::this_thread::get_id();

    Entry(const Level lvl, const std::string_view msg)
      : level{ lvl }, message{ msg }
    {}
};

} // namespace fwd::log