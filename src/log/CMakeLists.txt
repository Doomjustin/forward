add_library(${PROJECT_NAME}_LOG STATIC)

add_library(fwd::log ALIAS ${PROJECT_NAME}_LOG)

target_sources(${PROJECT_NAME}_LOG
    PUBLIC FILE_SET log 
    TYPE CXX_MODULES
    FILES
        export.cppm
        Logger.cppm
        LogLevel.cppm
)