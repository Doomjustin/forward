SET(OPENGL_CORE_VERSION_MAJOR 3)
SET(OPENGL_CORE_VERSION_MAJOR 3)

configure_file(
    ${CMAKE_CURRENT_LIST_DIR}/BuildInfo.cppm.in
    ${CMAKE_CURRENT_LIST_DIR}/BuildInfo.cppm @ONLY
)

add_library(${PROJECT_NAME}_UTILITY STATIC)

add_library(fwd::utility ALIAS ${PROJECT_NAME}_UTILITY)

target_sources(${PROJECT_NAME}_UTILITY
    PUBLIC FILE_SET utility
    TYPE CXX_MODULES
    FILES
        export.cppm
        BuildInfo.cppm
        StringUtility.cppm
)