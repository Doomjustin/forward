module;

#include <fmt/core.h>

#include <memory>
#include <string_view>

export module fwd.log;

export import :Entry;
export import :Level;
export import :Logger;

import :SimpleLogger;


namespace fwd::log {

// 一个默认实现的logger
export
std::unique_ptr<Logger> create(const std::string_view name) noexcept
{
    return std::make_unique<SimpleLogger>(name);
}


Logger& default_logger() noexcept
{
    static auto logger = create("forward");
    return *logger;
}

export
void level(const Level value) noexcept
{
    default_logger().level(value);
}

export
constexpr Level level() noexcept
{
    return default_logger().level();
}

export
template<typename... Args>
void fatal(fmt::format_string<Args...> fmt, Args... args)
{
    default_logger().fatal(std::move(fmt), std::forward<Args>(args)...);
}

export
template<typename... Args>
void error(fmt::format_string<Args...> fmt, Args... args)
{
    default_logger().error(std::move(fmt), std::forward<Args>(args)...);
}

export
template<typename... Args>
void warning(fmt::format_string<Args...> fmt, Args... args)
{
    default_logger().warning(std::move(fmt), std::forward<Args>(args)...);
}

export
template<typename... Args>
void debug(fmt::format_string<Args...> fmt, Args... args)
{
    default_logger().debug(std::move(fmt), std::forward<Args>(args)...);
}

export
template<typename... Args>
void info(fmt::format_string<Args...> fmt, Args... args)
{
    default_logger().info(std::move(fmt), std::forward<Args>(args)...);
}

export
template<typename... Args>
void trace(fmt::format_string<Args...> fmt, Args... args)
{
    default_logger().trace(std::move(fmt), std::forward<Args>(args)...);
}
} // namespace fwd::log