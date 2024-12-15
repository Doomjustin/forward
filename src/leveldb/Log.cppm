module;

#include <fmt/core.h>
#include <gsl/gsl>

#include <filesystem>
#include <fstream>
#include <memory>
#include <string_view>

export module fwd.leveldb.log;


namespace fwd::leveldb {

// ֻ��Ҫ֧��д����Ϣ���ɣ�����Ҫ���⹦�ܣ�Ч������
export
struct Logger {
    virtual ~Logger() = default;

    template<typename... Args>
    void write(fmt::format_string<Args...> fmt, Args... args)
    {
        write(fmt::format(std::move(fmt), std::forward<Args>(args)...));
    }

    virtual void write(const std::string_view message) = 0;
};


class FileLogger final: public Logger {
public:
    explicit FileLogger(const std::filesystem::path& path)
      : fs_{ path }
    {
        Ensures(fs_);
    }

    ~FileLogger() override = default;

    void write(const std::string_view message) override
    {
        fs_ << message << '\n';
    }

private:
    std::ofstream fs_;
};


export
std::unique_ptr<Logger> create(const std::filesystem::path& path)
{
    Ensures(std::filesystem::is_regular_file(path));
    return std::make_unique<FileLogger>(path);
}

} // namespace fwd::leveldb