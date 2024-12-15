add_executable(test_trim test_trim.cpp)
target_link_libraries(test_trim PRIVATE 
    fwd::utility
    Catch2::Catch2WithMain
)

add_executable(test_case_transform test_case_transform.cpp)
target_link_libraries(test_case_transform PRIVATE 
    fwd::utility
    Catch2::Catch2WithMain
)

catch_discover_tests(test_trim)
catch_discover_tests(test_case_transform)
