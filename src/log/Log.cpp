#include "Log.h"

#include "SimpleLogger.h"

#include <memory>
#include <string_view>


namespace fwd::log {

// 一个默认实现的logger
std::unique_ptr<Logger> create(const std::string_view name) noexcept
{
    return std::make_unique<SimpleLogger>(name);
}

Logger& default_logger() noexcept
{
    static auto logger = create("forward");
    return *logger;
}

} // fwd::log