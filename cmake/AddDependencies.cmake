include(FetchContent)

FetchContent_Declare(
    GSL
    GIT_REPOSITORY https://github.com/microsoft/GSL.git
    GIT_TAG        v4.1.0
    FIND_PACKAGE_ARGS
)


FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG        11.0.2
    FIND_PACKAGE_ARGS
)

option(FMT_TEST "fmt build test" OFF)


FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        v1.15.0
    FIND_PACKAGE_ARGS
)

option(SPDLOG_FMT_EXTERNAL "spdlog use external fmt" ON)
option(SPDLOG_BUILD_EXAMPLES "spdlog build example" OFF)
option(SPDLOG_BUILD_SHARED "spdlog build as shared lib" OFF)


FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.7.1
    FIND_PACKAGE_ARGS
)

option(BUILD_TESTING "Catch2 build test" OFF)
option(CATCH_INSTALL_DOCS "Catch2 install doc" OFF)
option(CATCH_INSTALL_EXTRAS "Catch2's extras folder" ON)


FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG        v2.13.6
)


FetchContent_MakeAvailable(
    GSL 
    fmt 
    spdlog
    Catch2
    pybind11
)
