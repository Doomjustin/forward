module;

#include <algorithm>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

export module fwd.log:SimpleLogger;

import :Logger;
import :Appender;


namespace fwd::log {

class SimpleLogger final: public Logger {
public:
    explicit SimpleLogger(const std::string_view name)
    : name_{ name }
    {
        appenders_.push_back(std::make_unique<StdoutAppender>());
    }

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
    void write(Entry entry) const override
    {
        if (entry.level > level_) return;

        entry.logger_name = name_;
        std::ranges::for_each(appenders_, 
                        [&entry] (const auto& appender) { appender->append(entry); });
    }

private:
    Level level_ = Level::Debug;
    std::string name_;
    std::vector<std::unique_ptr<Appender>> appenders_;
};

} // namespace fwd::log
