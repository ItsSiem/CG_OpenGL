cmake_minimum_required(VERSION 3.28)
project(CG_OpenGL)

set(CMAKE_CXX_STANDARD 17)

# Find OpenGL package
find_package(OpenGL REQUIRED)

# Set include directories
include_directories(${OPENGL_INCLUDE_DIRS})

# Add executable
add_executable(CG_OpenGL main.cpp)

# Link GLEW and GLUT libraries
target_link_libraries(CG_OpenGL ${OPENGL_LIBRARIES} GLEW glut)

