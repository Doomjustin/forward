#ifndef FORWARD_LOG_H
#define FORWARD_LOG_H

#include <fmt/core.h>

#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <thread>


namespace fwd::log {

enum class Level {
    Off,
    Fatal,
    Error,
    Warning,
    Debug,
    Info,
    Trace
};


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


class Logger {
public:
    Logger() = default;

    Logger(const Logger& other) = delete;
    Logger& operator=(const Logger& other) = delete;

    Logger(Logger&& other) noexcept = default;
    Logger& operator=(Logger&& other) noexcept = default;

    virtual ~Logger() = default;

    virtual void level(Level value) noexcept = 0;

    [[nodiscard]]
    virtual constexpr Level level() const noexcept = 0;

    template<typename... Args>
    void fatal(fmt::format_string<Args...> fmt, Args... args) const
    {
        write(Entry{ Level::Fatal, fmt::format(std::move(fmt), std::forward<Args>(args)...) });
    }

    template<typename... Args>
    void error(fmt::format_string<Args...> fmt, Args... args) const
    {
        write(Entry{ Level::Error, fmt::format(std::move(fmt), std::forward<Args>(args)...) });
    }

    template<typename... Args>
    void warning(fmt::format_string<Args...> fmt, Args... args) const
    {
        write(Entry{ Level::Warning, fmt::format(std::move(fmt), std::forward<Args>(args)...) });
    }

    template<typename... Args>
    void debug(fmt::format_string<Args...> fmt, Args... args) const
    {
        write(Entry{ Level::Debug, fmt::format(std::move(fmt), std::forward<Args>(args)...) });
    }

    template<typename... Args>
    void info(fmt::format_string<Args...> fmt, Args... args) const
    {
        write(Entry{ Level::Info, fmt::format(std::move(fmt), std::forward<Args>(args)...) });
    }

    template<typename... Args>
    void trace(fmt::format_string<Args...> fmt, Args... args) const
    {
        write(Entry{ Level::Trace, fmt::format(std::move(fmt), std::forward<Args>(args)...) });
    }

protected:
    virtual void write(Entry entry) const = 0;
}; 


// 一个默认实现的logger
std::unique_ptr<Logger> create(const std::string_view name) noexcept;

Logger& default_logger() noexcept;

static void level(const Level value) noexcept
{
    default_logger().level(value);
}

[[nodiscard]]
Level level() noexcept;

template<typename... Args>
void fatal(fmt::format_string<Args...> fmt, Args... args)
{
    default_logger().fatal(std::move(fmt), std::forward<Args>(args)...);
}

template<typename... Args>
void error(fmt::format_string<Args...> fmt, Args... args)
{
    default_logger().error(std::move(fmt), std::forward<Args>(args)...);
}

template<typename... Args>
void warning(fmt::format_string<Args...> fmt, Args... args)
{
    default_logger().warning(std::move(fmt), std::forward<Args>(args)...);
}

template<typename... Args>
void debug(fmt::format_string<Args...> fmt, Args... args)
{
    default_logger().debug(std::move(fmt), std::forward<Args>(args)...);
}

template<typename... Args>
void info(fmt::format_string<Args...> fmt, Args... args)
{
    default_logger().info(std::move(fmt), std::forward<Args>(args)...);
}

template<typename... Args>
void trace(fmt::format_string<Args...> fmt, Args... args)
{
    default_logger().trace(std::move(fmt), std::forward<Args>(args)...);
}

} // namespace fwd::log

#endif // FORWARD_LOG_H
