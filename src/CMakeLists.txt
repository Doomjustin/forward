set(FWD_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(FWD_INTERNAL_INCLUDE_DIR ${FWD_INCLUDE_DIR}/fwd)

SET(OPENGL_CORE_VERSION_MAJOR 3)
SET(OPENGL_CORE_VERSION_MAJOR 3)

configure_file(
    ${CMAKE_CURRENT_LIST_DIR}/BuildInfo.h.in
    ${FWD_INTERNAL_INCLUDE_DIR}/BuildInfo.h @ONLY
)

add_subdirectory(log)
add_subdirectory(leveldb)

add_library(${PROJECT_NAME}
    ${FWD_INTERNAL_INCLUDE_DIR}/BuildInfo.h
    ${FWD_INTERNAL_INCLUDE_DIR}/Utility.h
    ${FWD_INTERNAL_INCLUDE_DIR}/Log.h
    ${FWD_INTERNAL_INCLUDE_DIR}/LevelDB.h
    $<TARGET_OBJECTS:${PROJECT_NAME}_LOG>
    $<TARGET_OBJECTS:${PROJECT_NAME}_LEVELDB>
)

add_library(fwd::fwd ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${FWD_INCLUDE_DIR}
    PRIVATE
        ${FWD_INTERNAL_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
        GSL
        fmt::fmt
)