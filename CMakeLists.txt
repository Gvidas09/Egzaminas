cmake_minimum_required(VERSION 3.10)
project(TextAnalize)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/analyzer.cpp
    src/urls.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

add_executable(Testai
    tests/tests.cpp
    src/analyzer.cpp
    src/urls.cpp
)
target_include_directories(Testai PRIVATE include)
