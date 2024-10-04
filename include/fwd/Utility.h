#ifndef FORWARD_UTILITY_H
#define FORWARD_UTILITY_H

#include <type_traits>


namespace fwd {

class NonCopyable {
public:
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;

    NonCopyable(NonCopyable&&) noexcept = default;
    NonCopyable& operator=(NonCopyable&&) noexcept = default;

    ~NonCopyable() = default;

protected:
    NonCopyable() = default;
};


template<class Enum>
constexpr std::underlying_type_t<Enum> to_underlying(Enum e) noexcept
{
    return static_cast<std::underlying_type_t<Enum>>(e);
}

} // namespace fwd

#endif // FORWARD_UTILITY_H