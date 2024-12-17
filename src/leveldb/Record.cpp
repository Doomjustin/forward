#include "LevelDB.h"

#include "Coding.h"


namespace fwd::leveldb {

bool operator==(const Record& lhs, const Record& rhs) noexcept
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


Record::Record(const std::string_view key)
  : key_{ key }
{}

Record::Record(const std::string_view key, const std::string_view value)
  : key_{ key },
    value_{ value }
{}

void Record::encode(std::ostream& os) const noexcept
{
    encode_fixed(os, std::to_underlying(type_));

    encode_varint(os, key_.size());
    os << key_;

    if (is_not_removed()) {
        encode_varint(os, value_.size());
        os << value_;
    }
}

std::string read_string(std::istream& is)
{
    const auto size = decode_varint<std::size_t>(is);
    std::string result(size, ' ');
    is.read(result.data(), static_cast<std::streamsize>(size));

    return result;
}

Record Record::decode(std::istream& is) noexcept
{
    Record record{};
    record.type_ = static_cast<Type>(decode_fixed<std::underlying_type_t<Type>>(is));
    record.key_ = read_string(is);

    if (record.type_ == Type::Value)
        record.value_ = read_string(is);

    return record;
}

} // namespace fwd::leveldb