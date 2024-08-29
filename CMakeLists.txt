cmake_minimum_required(VERSION 3.5.0)
# Set the C++ compiler to 
set(CMAKE_CXX_COMPILER g++)
project(terminal-editor VERSION 0.1.0 LANGUAGES C CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(terminal-editor src/main.cpp)

# include(CTest)
# enable_testing()

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
