function(add_leveldb_test target source)
    add_executable(${target} ${source})

    target_link_libraries(${target}
        PRIVATE
            fwd::leveldb
            Catch2::Catch2WithMain
    )

    catch_discover_tests(${target})
endfunction()


add_leveldb_test(test_coding test_coding.cpp)
add_leveldb_test(test_write_batch test_write_batch.cpp)
