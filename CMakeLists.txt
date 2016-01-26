cmake_minimum_required(VERSION 3.3)
project(glfw_test CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(program_SOURCES "src/main.cpp" "src/shader.cpp" "src/util.cpp")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# set brew include dirs and libs
include_directories("/usr/local/include")
include_directories("/opt/local/include/SOIL")
include_directories("/usr/local/Cellar/glfw3/3.1.2/include")
include_directories("/usr/local/Cellar/glew/1.13.0/include")

link_directories("/usr/local/Cellar/glew/1.13.0/lib" "/usr/local/Cellar/glfw3/3.1.2/lib" "/usr/local/lib")
link_directories("/opt/local/lib")

# find opengl framework
find_library(OPENGL OpenGL)
set(LIBS ${LIBS} ${OPENGL} glfw3 glew soil)

add_executable(main ${program_SOURCES})
target_link_libraries(main ${OPENGL} ${LIBS})