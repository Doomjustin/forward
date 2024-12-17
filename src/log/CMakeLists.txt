add_library(${PROJECT_NAME}_LOG
    OBJECT
        SimpleLogger.cpp
        SimpleLogger.h
        Log.cpp
        Appender.h
        ConsoleAppender.h
        ConsoleAppender.cpp
)

add_library(fwd::log ALIAS ${PROJECT_NAME}_LOG)

target_include_directories(${PROJECT_NAME}_LOG
    PRIVATE  
        ${FWD_INTERNAL_INCLUDE_DIR}
    PUBLIC
        ${FWD_INCLUDE_DIR}
        ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${PROJECT_NAME}_LOG
    PUBLIC
        GSL
        fmt::fmt
)