#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <algorithm>
#include <cctype>
#include <ranges>
#include <string>

import fwd.utility;

static constexpr std::string trim_left_std(const std::string_view in)
{
    auto view = in | std::views::drop_while([] (char c) { return std::isspace(c); });

    return { view.begin(), view.end() };
}


TEST_CASE("test trim")
{
    const std::string base_str = "      123test f a s  ";

    SECTION("trim left")
    {
        REQUIRE_THAT(fwd::trim_left(base_str), Catch::Matchers::Equals("123test f a s  "));
    }

    SECTION("trim right")
    {
        REQUIRE_THAT(fwd::trim_right(base_str), Catch::Matchers::Equals("      123test f a s"));
    }

    SECTION("trim")
    {
        REQUIRE_THAT(fwd::trim(base_str), Catch::Matchers::Equals("123test f a s"));
    }
    
    BENCHMARK("std::isspace")
    {
        return trim_left_std(lower_case);
    };

    BENCHMARK("constexpr is space")
    {
        return fwd::trim_left(lower_case);
    };
}