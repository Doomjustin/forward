add_library(${PROJECT_NAME}_LEVELDB 
    OBJECT
        Coding.h 
        Record.cpp
        WriteBatch.cpp
        LevelDB.cpp
        FileLogger.cpp
        FileLogger.h
        Log.cpp
)

add_library(fwd::leveldb ALIAS ${PROJECT_NAME}_LEVELDB)
     
target_include_directories(${PROJECT_NAME}_LEVELDB
    PRIVATE
        ${FWD_INTERNAL_INCLUDE_DIR}
    INTERFACE
        ${FWD_INCLUDE_DIR}
        ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${PROJECT_NAME}_LEVELDB
    PUBLIC
        GSL
        fmt::fmt
)