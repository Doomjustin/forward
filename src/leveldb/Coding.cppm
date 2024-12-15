module;

#include <concepts>
#include <cstdint>
#include <istream>
#include <ostream>

export module fwd.leveldb.coding;


namespace fwd::leveldb {

constexpr int VarintByteSize = 7;

constexpr int NotLastByte = 1 << VarintByteSize; // 0b10000000

template<std::unsigned_integral T>
constexpr bool is_not_last_byte(T value)
{
    return value >= NotLastByte;
}

template<std::unsigned_integral T>
constexpr std::uint8_t get_varint_byte(T value)
{
    return value | NotLastByte;
}

export
template<std::unsigned_integral T>
void encode_fixed(std::ostream& os, T value)
{
    os.write(reinterpret_cast<char*>(&value), sizeof(T));
}

export
template<std::unsigned_integral T>
T decode_fixed(std::istream& is)
{
    T result{};
    is.read(reinterpret_cast<char*>(&result), sizeof(T));

    return result;
}

export
template<std::unsigned_integral T>
void encode_varint(std::ostream& os, T value)
{
    std::uint8_t byte{};

    while (is_not_last_byte(value)) {
        byte = get_varint_byte(value);
        os.write(reinterpret_cast<char*>(&byte), 1);
        value >>= VarintByteSize;
    }

    os.write(reinterpret_cast<char*>(&value), 1);
}

export
template<std::unsigned_integral T>
T decode_varint(std::istream& is)
{
    T result{};
    T byte{};
    is.read(reinterpret_cast<char*>(&byte), 1);

    int shift = 0;
    while (is_not_last_byte(byte)) {
        constexpr int VARINT_BYTE_SIZE = 7;
        constexpr int VARINT_BYTE_MAX = 0b01111111;

        result |= ((byte & VARINT_BYTE_MAX) << shift);
        is.read(reinterpret_cast<char*>(&byte), 1);
        shift += VARINT_BYTE_SIZE;
    }

    result |= (byte << shift);
    return result;
}

} // namespace fwd::leveldb
