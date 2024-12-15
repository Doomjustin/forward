SET(OPENGL_CORE_VERSION_MAJOR 3)
SET(OPENGL_CORE_VERSION_MAJOR 3)

configure_file(
    ${CMAKE_CURRENT_LIST_DIR}/build_info.cppm.in
    ${CMAKE_CURRENT_LIST_DIR}/build_info.cppm @ONLY
)

add_library(${PROJECT_NAME}_COMMON OBJECT)

add_library(fwd::common ALIAS ${PROJECT_NAME}_COMMON)

target_sources(${PROJECT_NAME}_COMMON
    PUBLIC FILE_SET CXX_MODULES
    FILES
        build_info.cppm
        utility.cppm
)