#ifndef FORWARD_LOG_SIMPLE_LOGGER_H
#define FORWARD_LOG_SIMPLE_LOGGER_H

#include "Appender.h"
#include "Log.h"

#include <vector>


namespace fwd::log {

class SimpleLogger final: public Logger {
public:
    explicit SimpleLogger(const std::string_view name);

    SimpleLogger(const SimpleLogger& other) = delete;
    SimpleLogger& operator=(const SimpleLogger& other) = delete;

    SimpleLogger(SimpleLogger&& other) noexcept = default;
    SimpleLogger& operator=(SimpleLogger&& other) noexcept = default;

    ~SimpleLogger() override = default;

    void level(const Level value) noexcept override
    {
        level_ = value;
    }

    [[nodiscard]]
    constexpr Level level() const noexcept override
    {
        return level_;
    }

protected:
    void write(Entry entry) const override;

private:
    Level level_ = Level::Debug;
    std::string name_;
    std::vector<std::unique_ptr<Appender>> appenders_;
};

} // namespace fwd::log

#endif // FORWARD_LOG_SIMPLE_LOGGER_H
