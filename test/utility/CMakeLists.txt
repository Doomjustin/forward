function(add_utility_test target source)
    add_executable(${target} ${source})

    target_link_libraries(${target}
        PRIVATE
            fwd::fwd
            Catch2::Catch2WithMain
    )

    catch_discover_tests(${target})
endfunction()


add_utility_test(test_trim test_trim.cpp)
add_utility_test(test_case_transform test_case_transform.cpp)
