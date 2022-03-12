cmake_minimum_required(VERSION 3.20)
set(CMAKE_SUPPRESS_REGENERATION true)

#include(submodules/submodules.cmake)

project(BulletGL)

add_library(BulletGL 	STATIC
						src/BulletGL/Camera.cpp
						src/BulletGL/Camera.h
						src/BulletGL/Core.h
						src/BulletGL/Render.h
						src/BulletGL/Render.cpp
#						src/BulletGL/Programm.cpp
						src/BulletGL/Shader.cpp
						src/BulletGL/Shader.h
						src/BulletGL/Window.cpp
						src/BulletGL/Window.h)

target_include_directories(BulletGL PRIVATE include/)
target_include_directories(BulletGL PRIVATE src/BulletGL/)

find_package(OpenGL REQUIRED)
set(OPENGL_LIBRARY ${OPENGL_LIBRARIES})
target_link_libraries(BulletGL PRIVATE "${OPENGL_LIBRARY}")

add_subdirectory(submodules/glfw ${CMAKE_CURRENT_BINARY_DIR}/extern/glfw)
target_link_libraries(BulletGL PRIVATE glfw)

add_subdirectory(submodules/glm ${CMAKE_CURRENT_BINARY_DIR}/extern/glm)
target_link_libraries(BulletGL PRIVATE glm)

add_subdirectory(submodules/glad ${CMAKE_CURRENT_BINARY_DIR}/extern/glad)
target_link_libraries(BulletGL PRIVATE glad)

add_subdirectory(examples ${CMAKE_CURRENT_BINARY_DIR}/examples)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)