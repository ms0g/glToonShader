cmake_minimum_required(VERSION 3.23.0)
project(glToonShader VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)

find_package(SDL2 REQUIRED)
if (SDL2_FOUND)
    include_directories(${SDL2_INCLUDE_DIR})
endif()

find_package(ASSIMP REQUIRED)
if(ASSIMP_FOUND)
    include_directories(${ASSIMP_INCLUDE_DIR})
endif()

set(FILESYSTEM_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/libs/filesystem/include)
set(GLM_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/libs/glm/include)
set(GLAD_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/include)
set(STB_IMAGE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/libs/image/include)
set(KHR_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/libs/KHR/include)
set(GLAD
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/src/glad.c
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/include/glad/glad.h)
set(STB_IMAGE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/image/src/stb_image.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/image/include/image/stb_image.h)
set(FILESYSTEM
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/filesystem/src/filesystem.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/filesystem/include/filesystem/filesystem.h)
set(WINDOW
        ${CMAKE_CURRENT_SOURCE_DIR}/src/window/window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/window/window.h)
set(CAMERA
        ${CMAKE_CURRENT_SOURCE_DIR}/src/camera/camera.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/camera/camera.h)
set(ENGINE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/engine.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/engine.h)
set(GUI
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/gui.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/gui.h)
set(SHADER
        ${CMAKE_CURRENT_SOURCE_DIR}/src/shader/shader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/shader/shader.h)
set(INPUT
        ${CMAKE_CURRENT_SOURCE_DIR}/src/input/input.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/input/input.h)
set(MODEL
        ${CMAKE_CURRENT_SOURCE_DIR}/src/model/model.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/model/model.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/model/mesh.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/model/mesh.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/model/texture.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/model/texture.h)

file(GLOB_RECURSE IMGUI "libs/imgui/*")

set(COMPILATION_UNIT
        src/main.cpp
        ${GLAD}
        ${STB_IMAGE}
        ${FILESYSTEM}
        ${IMGUI}
        ${WINDOW}
        ${CAMERA}
        ${ENGINE}
        ${GUI}
        ${SHADER}
        ${INPUT}
        ${MODEL}
        )

add_executable(${PROJECT_NAME} ${COMPILATION_UNIT})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${GLAD_INCLUDE_DIRS}
        ${FILESYSTEM_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
        ${STB_IMAGE_INCLUDE_DIRS}
        ${KHR_INCLUDE_DIRS}
        )

target_link_libraries(${PROJECT_NAME} OpenGL::GL ${SDL2_LIBRARIES} ${ASSIMP_LIBRARIES})