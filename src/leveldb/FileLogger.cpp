#include "FileLogger.h"

#include "Coding.h"

#include <gsl/gsl>


namespace fwd::leveldb {

static constexpr int BlockSize = 0x8000;
static constexpr char Fill = '\0';
static constexpr int HeaderSize = 4 + 2 + 1;

enum class Type: std::uint8_t {
    Full,
    First,
    Middle,
    Last
};

struct Header {
    std::uint64_t checksum = 0;
    std::uint32_t size;
    Type type = Type::Full;

    Header(const std::uint32_t sz, const Type t)
      : size{ sz }, type{ t }
    {}
};

void write_header(std::ostream& os, const Header& header)
{
    
}

void fill_rest_block(std::ostream& os, const std::size_t size)
{
    std::ranges::fill_n(std::ostream_iterator<char>(os), static_cast<gsl::index>(size), Fill);
}

constexpr Type check_type(const bool begin, const bool end)
{
    if (begin && end) return Type::Full;
    else if (begin) return Type::First;
    else if (end) return Type::Last;
    else return Type::Middle;
}

void FileLogger::write(const std::string_view message)
{
    auto left = message.size();

    bool is_begin = true;

    gsl::index offset = 0;
    while (is_begin || left > 0) {
        if (const auto left_over = BlockSize - offset; left_over < HeaderSize) {
            fill_rest_block(fs_, left_over);
            offset = 0;
        }

        const auto avail = BlockSize - HeaderSize - offset;
        const auto fragment_size = (left < avail) ? left : avail;

        const bool is_end = (left ==fragment_size);
        const auto type = check_type(is_begin, is_end);

        Header header{ gsl::narrow_cast<std::uint32_t>(fragment_size), type };

        write_header(fs_, header);
        // write_content(os, offset, fragment_size);

        offset += static_cast<gsl::index>(fragment_size);
        left -= fragment_size;

        is_begin = false;
    }
}

} // namespace fwd::leveldb 