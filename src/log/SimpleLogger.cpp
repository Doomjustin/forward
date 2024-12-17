#include "SimpleLogger.h"

#include "ConsoleAppender.h"


namespace fwd::log {

SimpleLogger::SimpleLogger(const std::string_view name)
 : name_{ name }
{
    appenders_.push_back(std::make_unique<ConsoleAppender>());
}

void SimpleLogger::write(Entry entry) const
{
    if (entry.level > level_) return;

    entry.logger_name = name_;
    std::ranges::for_each(appenders_, 
                    [&entry] (const auto& appender) { appender->append(entry); });
}

} // namespace fwd::log