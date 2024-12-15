module;

#include <fmt/core.h>

export module fwd.log:Appender;

import :Entry;


namespace fwd::log {

export
struct Appender {
    Appender() = default;

    Appender(const Appender& other) = delete;
    Appender& operator=(const Appender& other) = delete;

    Appender(Appender&& other) noexcept = default;
    Appender& operator=(Appender&& other) noexcept = default;

    virtual ~Appender() = default;

    virtual void append(const Entry& entry) = 0;
};


export
class StdoutAppender final: public Appender {
public:
    StdoutAppender() = default;

    StdoutAppender(const StdoutAppender& other) = delete;
    StdoutAppender& operator=(const StdoutAppender& other) = delete;

    StdoutAppender(StdoutAppender&& other) noexcept = default;
    StdoutAppender& operator=(StdoutAppender&& other) noexcept = default;

    ~StdoutAppender() override = default;

    void append(const Entry& entry) override
    {
        // TODO: 格式支持自定义，由Formatter来转换
        fmt::println("{}", entry.message);
    }
};

} // namespace fwd::log 