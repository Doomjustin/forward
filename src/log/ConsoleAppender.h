#ifndef FORWARD_LOG_CONSOLE_APPENDER_H
#define FORWARD_LOG_CONSOLE_APPENDER_H

#include "Appender.h"


namespace fwd::log {

class ConsoleAppender final: public Appender {
public:
    ConsoleAppender() = default;

    ConsoleAppender(const ConsoleAppender& other) = delete;
    ConsoleAppender& operator=(const ConsoleAppender& other) = delete;

    ConsoleAppender(ConsoleAppender&& other) noexcept = default;
    ConsoleAppender& operator=(ConsoleAppender&& other) noexcept = default;

    ~ConsoleAppender() override = default;

    void append(const Entry& entry) override;
};

} // namespace fwd::log

#endif // FORWARD_LOG_CONSOLE_APPENDER_H
