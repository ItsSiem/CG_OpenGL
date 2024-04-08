cmake_minimum_required(VERSION 3.10)
project(CG_OpenGL)

set(CMAKE_CXX_STANDARD 17)

# Find OpenGL package
find_package(OpenGL REQUIRED)

# Find GLM
find_package(glm REQUIRED)

# Set include directories
include_directories(${OPENGL_INCLUDE_DIRS})

# Add executable
add_executable(CG_OpenGL src/main.cpp src/glsl.h src/glsl.cpp src/objloader.cpp src/objloader.h src/texture.cpp src/texture.h
        src/game_object.cpp
        src/game_object.h
        src/Material.h
        src/Light.h
        src/globals.h)

# Link GLEW and GLUT libraries
target_link_libraries(CG_OpenGL ${OPENGL_LIBRARIES} ${GLM_LIBRARIES} GLEW glut)

# Copy shaders to build directory
#file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
configure_file(vertex_shader.vert ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(fragment_shader.frag ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

file(COPY objects DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY textures DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


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
#compile_shader(vertex_shader vert)
#compile_shader(fragment_shader frag)

# Add shaders as dependencies for your executable
#add_dependencies(CG_OpenGL vertex_shader_target fragment_shader_target)
