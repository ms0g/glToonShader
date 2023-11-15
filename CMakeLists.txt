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
set(WINDOW_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/src/Window/include)
set(CAMERA_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/src/Camera/include)
set(CONFIGS_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/src/Configs/include)
set(ENGINE_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine/include)
set(GUI_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/src/Gui/include)
set(SHADER_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/src/Shader/include)
set(INPUT_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/src/Input/include)
set(MODEL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/src/Model/include)
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
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Window/src/Window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Window/include/Window/Window.h)
set(CAMERA
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Camera/src/Camera.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Camera/include/Camera/Camera.h)
set(ENGINE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine/src/Engine.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine/include/Engine/Engine.h)
set(GUI
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Gui/src/Gui.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Gui/include/Gui/Gui.h)
set(SHADER
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Shader/src/Shader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Shader/include/Shader/Shader.h)
set(INPUT
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Input/src/Input.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Input/include/Input/Input.h)
set(MODEL
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Model/src/Model.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Model/include/Model/Model.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Model/src/Mesh.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Model/include/Model/Mesh.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Model/src/Texture.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Model/include/Model/Texture.h)

file(GLOB_RECURSE IMGUI "libs/imgui/*")

set(COMPILATION_UNIT
        src/Main.cpp
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
        ${WINDOW_INCLUDE}
        ${CAMERA_INCLUDE}
        ${CONFIGS_INCLUDE}
        ${ENGINE_INCLUDE}
        ${GUI_INCLUDE}
        ${SHADER_INCLUDE}
        ${INPUT_INCLUDE}
        ${MODEL_INCLUDE}
        )

target_link_libraries(${PROJECT_NAME} OpenGL::GL ${SDL2_LIBRARIES} ${ASSIMP_LIBRARIES})