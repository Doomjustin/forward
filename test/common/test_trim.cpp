#include <catch2/catch_test_macros.hpp>
#include "catch2/matchers/catch_matchers_string.hpp"

import fwd.utility;


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
}