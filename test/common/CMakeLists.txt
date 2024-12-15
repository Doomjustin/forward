add_executable(test_trim test_trim.cpp)
target_link_libraries(test_trim PRIVATE 
    fwd::common
    Catch2::Catch2WithMain
)


catch_discover_tests(test_trim)
