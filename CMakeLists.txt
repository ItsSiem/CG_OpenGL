cmake_minimum_required(VERSION 3.28)
project(CG_OpenGL)

set(CMAKE_CXX_STANDARD 17)

# Find OpenGL package
find_package(OpenGL REQUIRED)

# Find GLM
find_package(glm REQUIRED)

# Set include directories
include_directories(${OPENGL_INCLUDE_DIRS})

# Add executable
add_executable(CG_OpenGL main.cpp glsl.h glsl.cpp)

# Link GLEW and GLUT libraries
target_link_libraries(CG_OpenGL ${OPENGL_LIBRARIES} ${GLM_LIBRARIES} GLEW glut)

# Copy shaders to build directory
file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Function to compile GLSL shaders
function(compile_shader SHADER_NAME SHADER_TYPE)
    add_custom_command(
            OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/shaders/${SHADER_NAME}.spv
            COMMAND glslangValidator -V ${CMAKE_CURRENT_SOURCE_DIR}/shaders/${SHADER_NAME}.${SHADER_TYPE} -o ${CMAKE_CURRENT_BINARY_DIR}/shaders/${SHADER_NAME}.spv
            DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/shaders/${SHADER_NAME}.${SHADER_TYPE}
            COMMENT "Compiling ${SHADER_NAME} ${SHADER_TYPE} shader"
    )
    add_custom_target(${SHADER_NAME}_target DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/shaders/${SHADER_NAME}.spv)
endfunction()

# Compile your shaders (replace "vert" and "frag" with your actual shader file extensions)
compile_shader(vertex_shader vert)
compile_shader(fragment_shader frag)

# Add shaders as dependencies for your executable
add_dependencies(CG_OpenGL vertex_shader_target fragment_shader_target)
