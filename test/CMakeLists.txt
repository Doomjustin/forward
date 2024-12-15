list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

add_subdirectory(utility)
add_subdirectory(leveldb)