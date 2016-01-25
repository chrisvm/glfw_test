cmake_minimum_required(VERSION 3.3)
project(glfw_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(program_SOURCES "src/main.cpp" "src/shader.cpp" "src/util.cpp")

# set brew include dirs and libs
include_directories("/usr/local/include")
include_directories("/usr/local/Cellar/glfw3/3.1.2/include")
include_directories("/usr/local/Cellar/glew/1.13.0/include")

link_directories("/usr/local/Cellar/glew/1.13.0/lib" "/usr/local/Cellar/glfw3/3.1.2/lib" "/usr/local/lib")

# find opengl framework
find_library(OPENGL OpenGL)
set(LIBS ${LIBS} ${OPENGL} glfw3 glew)

add_executable(main ${program_SOURCES})
target_link_libraries(main ${OPENGL} ${LIBS})