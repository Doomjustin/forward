#include "FileLogger.h"

#include "Coding.h"

#include <gsl/gsl>


namespace fwd::leveldb {

namespace details {

class Record {
private:
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

        Header(const std::uint32_t sz, Type t)
          : size{ sz }, type{ t }
        {}
    };

public:
    explicit Record(const std::string_view message)
      : content_{ message }
    {}

    void write(std::ostream& os) const
    {
        auto left = content_.size();

        bool is_begin = true;

        gsl::index offset = 0;
        while (is_begin || left > 0) {
            if (const auto left_over = BlockSize - offset; left_over < HeaderSize) {
                fill_rest_block(os, left_over);
                offset = 0;
            }

            const auto avail = BlockSize - HeaderSize - offset;
            const auto fragment_size = (left < avail) ? left : avail;

            const bool is_end = (left ==fragment_size);
            const auto type = get_type(is_begin, is_end);

            Header header{ gsl::narrow_cast<std::uint32_t>(fragment_size), type };

            write_header(os, header);
            write_content(os, offset, fragment_size);

            offset += static_cast<gsl::index>(fragment_size);
            left -= fragment_size;

            is_begin = false;
        }
    }

private:
    static constexpr int BlockSize = 0x8000;
    static constexpr char Fill = '\0';
    static constexpr int HeaderSize = 4 + 2 + 1;

    std::string content_;

    void write_content(std::ostream& os, const gsl::index offset, const std::size_t fragment) const
    {
        std::copy_n(std::next(content_.begin(), offset), fragment, 
                    std::ostream_iterator<char>(os));
    }

    static void write_header(std::ostream& os, const Header& header)
    {
        
    }

    static void fill_rest_block(std::ostream& os, const std::size_t size)
    {
        std::ranges::fill_n(std::ostream_iterator<char>(os), size, Fill);
    }

    static Type get_type(const bool begin, const bool end)
    {
        if (begin && end) return Type::Full;
        else if (begin) return Type::First;
        else if (end) return Type::Last;
        else return Type::Middle;
    }
};

} // namespace fwd::leveldb::details


void FileLogger::write(const std::string_view message)
{
    // TODO: 遵循原作，按block写入
    // xxxx|message|xxxx|message
    encode_fixed(fs_, message.size());
    fs_ << message;
}

} // namespace fwd::leveldb 