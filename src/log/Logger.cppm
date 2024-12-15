module;

#include <fmt/core.h>

export module fwd.log:Logger;

import :Level;
import :Entry;


namespace fwd::log {

export
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

} // namespace fwd::log