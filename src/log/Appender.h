#ifndef FORWARD_LOG_APPENDER_H
#define FORWARD_LOG_APPENDER_H

#include "Log.h"


namespace fwd::log {

struct Appender {
    Appender() = default;

    Appender(const Appender& other) = delete;
    Appender& operator=(const Appender& other) = delete;

    Appender(Appender&& other) noexcept = default;
    Appender& operator=(Appender&& other) noexcept = default;

    virtual ~Appender() = default;

    virtual void append(const Entry& entry) = 0;
};

} // namespace fwd::log

#endif // FORWARD_LOG_APPENDER_H
