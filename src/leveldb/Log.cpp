#include "LevelDB.h"

#include "FileLogger.h"

#include <filesystem>
#include <memory>


namespace fwd::leveldb {

std::unique_ptr<Logger> create(const std::filesystem::path& path)
{
    using namespace std::filesystem;
    Ensures(!exists(path) || is_regular_file(path));

    return std::make_unique<FileLogger>(path);
}

std::unique_ptr<LogParser> parse(const std::filesystem::path& path)
{
    using namespace std::filesystem;
    Ensures(is_regular_file(path));

    return nullptr;
}

} // namespace fwd::leveldb