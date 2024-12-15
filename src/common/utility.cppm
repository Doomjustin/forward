module;

#include <algorithm>
#include <ranges>
#include <string>

export module fwd.utility;


namespace fwd {

export
[[nodiscard]]
constexpr bool is_space(char p) noexcept
{
    auto not_equal = [p] (auto q) { return p != q; };
    return !!(" \t\n\v\r\f" | std::views::drop_while(not_equal));
};

export
[[nodiscard("trims the output")]]
constexpr std::string trim_left(const std::string_view in) noexcept
{
    auto view = in | std::views::drop_while(is_space);
    return {view.begin(), view.end()};
}

export
[[nodiscard("trims the output")]]
constexpr std::string trim_right(const std::string_view in)
{
    auto view = in
              | std::views::reverse
              | std::views::drop_while(is_space)
              | std::views::reverse
              ;

    return { view.begin(), view.end() };
}

export
[[nodiscard("trims the output")]]
constexpr std::string trim(const std::string_view in)
{
    auto view = in
              | std::views::drop_while(is_space)
              | std::views::reverse
              | std::views::drop_while(is_space)
              | std::views::reverse
              ;

    return {view.begin(), view.end()};
}

} // namespace fwd
