#ifndef FORWARD_LEVELDB_FILE_LOGGER_H
#define FORWARD_LEVELDB_FILE_LOGGER_H

#include "LevelDB.h"

#include <fstream>


namespace fwd::leveldb {

class FileLogger final: public Logger {
public:
    explicit FileLogger(const std::filesystem::path& path)
      : fs_{ path }
    {
        Ensures(fs_);
    }

    FileLogger(const FileLogger& other) = delete;
    FileLogger& operator=(const FileLogger& other) = delete;

    FileLogger(FileLogger&& other) noexcept = default;
    FileLogger& operator=(FileLogger&& other) noexcept = default;

    ~FileLogger() override = default;


    void write(const std::string_view message) override;

private:
    std::ofstream fs_;
};

} // namespace fwd::leveldb

#endif // FORWARD_LEVELDB_FILE_LOGGER_H