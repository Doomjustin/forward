add_library(${PROJECT_NAME}_LEVELDB STATIC)

add_library(fwd::leveldb ALIAS ${PROJECT_NAME}_LEVELDB)

target_sources(${PROJECT_NAME}_LEVELDB
    PUBLIC FILE_SET CXX_MODULES
    FILES
        export.cppm
        LevelDB.cppm
        WriteBatch.cppm
        Coding.cppm
        Log.cppm
)

target_link_libraries(${PROJECT_NAME}_LEVELDB
    PRIVATE
        GSL
        fmt::fmt
)