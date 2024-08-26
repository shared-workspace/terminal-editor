cmake_minimum_required(VERSION 3.5.0)
# Set the C++ compiler to clang++
set(CMAKE_CXX_COMPILER clang++)
project(terminal-editor VERSION 0.1.0 LANGUAGES C CXX)


add_executable(terminal-editor main.cpp)

# include(CTest)
# enable_testing()

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
