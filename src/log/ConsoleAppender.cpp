#include "ConsoleAppender.h"


namespace fwd::log {

void ConsoleAppender::append(const Entry& entry)
{
    // TODO: 格式支持自定义，由Formatter来转换
    fmt::println("{}", entry.message);
}

} // namespace fwd::log
