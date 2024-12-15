#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

import fwd.utility;


TEST_CASE("test case transform")
{
    const std::string lower_case = "0123456789 \t\n\v\r\f ;:<>.,?|\\'`~\"!@#$%^&*(){}[]/_+-= abcdefghijklmnopqrstuvwxyz";
    const std::string upper_case = "0123456789 \t\n\v\r\f ;:<>.,?|\\'`~\"!@#$%^&*(){}[]/_+-= ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    SECTION("to_upper only alpha transformed")
    {
        REQUIRE_THAT(fwd::to_upper(lower_case), Catch::Matchers::Equals(upper_case));
        REQUIRE_THAT(fwd::to_upper(upper_case), Catch::Matchers::Equals(upper_case));
    }

    SECTION("to_lower  only alpha transformed")
    {
        REQUIRE_THAT(fwd::to_lower(upper_case), Catch::Matchers::Equals(lower_case));
        REQUIRE_THAT(fwd::to_lower(lower_case), Catch::Matchers::Equals(lower_case));
    }

}