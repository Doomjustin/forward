module;

#include <string_view>

export module fwd.log:Logger;

import :LogLevel;


namespace fwd {

export
struct Logger {
    virtual ~Logger() = default;

    virtual void write(std::string_view message) const = 0;

    virtual void level(LogLevel value) noexcept = 0;

    [[nodiscard]]
    virtual constexpr LogLevel level() const noexcept = 0;
}; 

} // namespace fwd