#ifndef FORWARD_LEVELDB_H
#define FORWARD_LEVELDB_H

#include <fmt/core.h>
#include <gsl/gsl>

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <iterator>
#include <mutex>
#include <string>
#include <string_view>
#include <vector>
#include <condition_variable>


namespace fwd::leveldb {

class Record {
    friend bool operator==(const Record& lhs, const Record& rhs) noexcept;
    friend std::ostream& operator<<(std::ostream& os, const Record& record);

public:
    explicit Record(const std::string_view key);

    Record(const std::string_view key, const std::string_view value);

    [[nodiscard]]
    std::string_view key() const noexcept { return key_; }

    [[nodiscard]]
    std::string_view value() const noexcept { return value_; }

    void encode(std::ostream& os) const noexcept;

    static Record decode(std::istream& is) noexcept;

private:
    enum class Type: std::uint8_t {
        Value = 0x01,
        Deletion = 0x02
    };

    std::string key_;
    std::string value_;
    Type type_ = value_.empty() ? Type::Deletion : Type::Value;

    Record() = default;

    [[nodiscard]]
    constexpr bool is_not_removed() const noexcept
    {
        return type_ != Type::Deletion;
    }
};


class WriteBatch {
    friend WriteBatch operator+(WriteBatch lhs, const WriteBatch& rhs);
    friend bool operator==(const WriteBatch& lhs, const WriteBatch& rhs);
    friend std::ostream& operator<<(std::ostream& os, const WriteBatch& batch);

public:
    using Size = std::size_t;
    using SequenceNumber = std::uint64_t;

    void put(const std::string_view key, const std::string_view value) noexcept
    {
        records_.emplace_back(key, value);
    }

    void remove(const std::string_view key) noexcept
    {
        records_.emplace_back(key);
    }

    [[nodiscard]]
    constexpr Size size() const noexcept { return records_.size(); }

    [[nodiscard]]
    constexpr SequenceNumber sequence_number() const noexcept
    {
        return sequence_number_;
    }

    void sequence_number(const SequenceNumber value) noexcept
    {
        sequence_number_ = value;
    }


    WriteBatch& operator+=(const WriteBatch& other)
    {
        std::ranges::copy(other.records_, std::back_inserter(records_));
        return *this;
    }
  
    void encode(std::ostream& os) const noexcept;

    static WriteBatch decode(std::istream& is) noexcept;

private:
    SequenceNumber sequence_number_ = 0;
    std::vector<Record> records_;
};


struct Task {
    WriteBatch batch;
    bool done = false;

    explicit Task(WriteBatch batch)
      : batch(std::move(batch))
    {}

    Task() = default;
};
 

// 只需要支持写入message即可，不需要额外功能，效率优先
struct Logger {
    virtual ~Logger() = default;

    template<typename... Args>
    void write(fmt::format_string<Args...> fmt, Args... args)
    {
        write(fmt::format(std::move(fmt), std::forward<Args>(args)...));
    }

    virtual void write(const std::string_view message) = 0;
};


struct LogParser {
    virtual ~LogParser() = default;

    [[nodiscard]]
    virtual std::string next() const noexcept = 0;

    [[nodiscard]]
    virtual std::string seek(std::size_t index) const noexcept = 0;
};


std::unique_ptr<Logger> create(const std::filesystem::path& path);
std::unique_ptr<LogParser> parse(const std::filesystem::path& path);


class LevelDB {
public:
    explicit LevelDB(std::filesystem::path dir);

    [[nodiscard]]
    std::optional<std::string> get(const std::string_view key) const;

    void put(const std::string_view key, const std::string_view value)
    {
        WriteBatch batch{};
        batch.put(key, value);
        write(batch);
    }

    void remove(const std::string_view key)
    {
        WriteBatch batch{};
        batch.remove(key);
        write(batch);
    }

    void write(const WriteBatch& batch);

    [[nodiscard]]
    std::string name() const noexcept
    {
        return dir_.stem().string();
    }

private:
    static constexpr auto LogFileName = "Log";
    static constexpr auto ManifestFileName = "MANIFEST-{:0>6}";

    std::filesystem::path dir_;
    std::mutex m_;
    std::condition_variable cv_;
    std::vector<Task> tasks_;
    std::unique_ptr<Logger> logger_ = create(dir_ / LogFileName);

    using Iterator = std::vector<Task>::iterator;

    Iterator push(const WriteBatch& batch) noexcept
    {
        std::lock_guard<std::mutex> locker{ m_ };
        tasks_.emplace_back(batch);
        return std::prev(tasks_.end(), 1);
    }

};

} // namespace fwd::leveldb

#endif // FORWARD_LEVELDB_H