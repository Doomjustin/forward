module;

#include <algorithm>
#include <fmt/core.h>

#include <cstdint>
#include <istream>
#include <iterator>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

export module fwd.leveldb:WriteBatch;

import fwd.leveldb.coding;


namespace fwd::leveldb {

std::string read_string(std::istream& is)
{
    const auto size = decode_varint<std::size_t>(is);
    std::string result(size, ' ');
    is.read(result.data(), static_cast<std::streamsize>(size));

    return result;
}


class Record {
    friend constexpr bool operator==(const Record& lhs, const Record& rhs) noexcept;
    friend std::ostream& operator<<(std::ostream& os, const Record& record);

public:
    explicit Record(const std::string_view key)
      : key_{ key }
    {}

    Record(const std::string_view key, const std::string_view value)
      : key_{ key },
        value_{ value }
    {}

    [[nodiscard]]
    std::string_view key() const noexcept { return key_; }

    [[nodiscard]]
    std::string_view value() const noexcept { return value_; }

    void encode(std::ostream& os) const noexcept
    {
        encode_fixed(os, std::to_underlying(type_));

        encode_varint(os, key_.size());
        os << key_;

        if (is_not_removed()) {
            encode_varint(os, value_.size());
            os << value_;
        }
    }

    static Record decode(std::istream& is) noexcept
    {
        Record record{};
        record.type_ = static_cast<Type>(decode_fixed<std::underlying_type_t<Type>>(is));
        record.key_ = read_string(is);

        if (record.type_ == Type::Value)
            record.value_ = read_string(is);

        return record;
    }

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


export
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

    void encode(std::ostream& os) const noexcept
    {
        encode_fixed(os, sequence_number_);
        encode_varint(os, records_.size());

        std::ranges::for_each(records_, [&os] (const auto& record) { record.encode(os); });
    }

    WriteBatch& operator+=(const WriteBatch& other)
    {
        std::ranges::copy(other.records_, std::back_inserter(records_));
        return *this;
    }

    static WriteBatch decode(std::istream& is) noexcept
    {
        WriteBatch batch{};
        batch.sequence_number_ = decode_fixed<SequenceNumber>(is);
        auto record_size = decode_varint<Size>(is);

        while (record_size-- > 0)
            batch.records_.push_back(Record::decode(is));

        return batch;
    }

private:
    SequenceNumber sequence_number_ = 0;
    std::vector<Record> records_;
};


constexpr bool operator==(const Record& lhs, const Record& rhs) noexcept
{
    return lhs.type_ == rhs.type_ &&
           lhs.key_ == rhs.key_ &&
           lhs.value_ == rhs.value_;
}

std::ostream& operator<<(std::ostream& os, const Record& record)
{
    switch (record.type_) {
    case Record::Type::Value:
        os << fmt::format("[value]{}: {}", record.key_, record.value_);
        break;
    case Record::Type::Deletion:
        os << fmt::format("[deleted]{}", record.key_);
        break;
    }

    return os;
}


WriteBatch operator+(WriteBatch lhs, const WriteBatch& rhs)
{
    return lhs += rhs;
}

bool operator==(const WriteBatch& lhs, const WriteBatch& rhs)
{
    if (lhs.sequence_number_ != rhs.sequence_number_) return false;

    if (lhs.records_.size() != rhs.records_.size()) return false;

    return std::ranges::equal(lhs.records_, rhs.records_);
}

std::ostream& operator<<(std::ostream& os, const WriteBatch& batch)
{
    os << batch.sequence_number_ << '\n';
    std::ranges::copy(batch.records_, std::ostream_iterator<Record>(os, "\n"));
    return os;
}

} // namespace fwd::leveldb
