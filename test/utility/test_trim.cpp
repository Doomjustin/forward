#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <fwd/Utility.h>

#include <cctype>
#include <ranges>
#include <string>


/*
static constexpr std::string trim_left_std(const std::string_view in)
{
    auto view = in | std::views::drop_while([] (const char c) { return std::isspace(c); });

    return { view.begin(), view.end() };
}
*/

TEST_CASE("test trim")
{
    const std::string base_str = "      123test f a s  ";
    const std::string lower_case = "0123456789 \t\n\v\r\f ;:<>.,?|\\'`~\"!@#$%^&*(){}[]/_+-= abcdefghijklmnopqrstuvwxyz";
    const std::string upper_case = "0123456789 \t\n\v\r\f ;:<>.,?|\\'`~\"!@#$%^&*(){}[]/_+-= ABCDEFGHIJKLMNOPQRSTUVWXYZ";


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
    
    /*
     BENCHMARK("std::isspace")
    {
        return trim_left_std(lower_case);
    };
    */

    BENCHMARK("constexpr is space")
    {
        return fwd::trim_left(lower_case);
    };
}