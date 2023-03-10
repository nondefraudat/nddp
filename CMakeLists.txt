cmake_minimum_required (VERSION 3.13)

project ("nddp")
add_subdirectory("3rd-party/zip")

add_executable(${PROJECT_NAME} "src/main.cpp" "src/nddp.cpp" "src/nddp.hpp" "src/packagemaster.cpp" "src/package.cpp")
target_include_directories(${PROJECT_NAME} PRIVATE "3rd-party/zip/src")
target_link_libraries(${PROJECT_NAME} PRIVATE zipshell)
set_property(TARGET nddp PROPERTY CXX_STANDARD 20)
