add_executable(test_coding test_coding.cpp)
target_link_libraries(test_coding
    PRIVATE
        fwd::leveldb
        Catch2::Catch2WithMain
)


catch_discover_tests(test_coding)
