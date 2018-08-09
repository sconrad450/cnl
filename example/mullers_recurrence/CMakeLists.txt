project(MullersRecurrence)

cmake_minimum_required(VERSION 3.0)

add_executable(MullersRecurrence main.cpp)
target_compile_options(MullersRecurrence PRIVATE "-std=c++17" "-fsanitize=undefined")
target_link_libraries(MullersRecurrence "-fsanitize=undefined")
target_compile_definitions(MullersRecurrence PRIVATE "CNL_USE_INT128")

find_package(Cnl REQUIRED)
include(${Cnl_DIR}/CnlConfig.cmake)

target_link_libraries(MullersRecurrence Cnl::Cnl)
get_target_property(Cnl_INCLUDE_DIR Cnl::Cnl INTERFACE_INCLUDE_DIRECTORIES)

target_include_directories(MullersRecurrence PRIVATE ${Cnl_INCLUDE_DIR})
