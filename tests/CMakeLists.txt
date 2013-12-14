include(ExternalProject)

ExternalProject_Add(
    CppUTest
    GIT_REPOSITORY "https://github.com/cpputest/cpputest.git"
    GIT_TAG "v3.5"
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/../cpputest
    INSTALL_DIR ${CMAKE_BINARY_DIR}/install
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/install
)

include_directories(${CMAKE_BINARY_DIR}/install/include)

add_library(imp_cpputest STATIC IMPORTED)
set_property(TARGET imp_cpputest PROPERTY
             IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/install/lib/libCppUTest.a)

add_executable(fat_test test_main.cc)
target_link_libraries(fat_test imp_cpputest)

