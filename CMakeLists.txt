cmake_minimum_required(VERSION 3.20)
set(CMAKE_SUPPRESS_REGENERATION true)

#include(submodules/submodules.cmake)

set(FOLDER_NAME BulletGL)
set(PROJECT_NAME BulletGL)
project(${PROJECT_NAME} CXX)

include(CMake/CMakeMacros.txt)

file(GLOB_RECURSE SRC_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.c??)
file(GLOB_RECURSE HEADER_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.h)
file(GLOB_RECURSE SHADER_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} res/Shaders/*)

include_directories(src/BulletGL/)
include_directories(res/Shaders/)

add_library(${PROJECT_NAME} STATIC ${SRC_FILES} ${HEADER_FILES} ${SHADER_FILES})

SETUP_GROUPS("${SRC_FILES}")
SETUP_GROUPS("${HEADER_FILES}")
SETUP_GROUPS("${SHADER_FILES}")

#set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME_DEBUG ${PROJECT_NAME}_Debug)
#set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME_RELEASE ${PROJECT_NAME}_Release)
#set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME_RELWITHDEBINFO ${PROJECT_NAME}_ReleaseDebInfo)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDART 20)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

if(MSVC)
	add_definitions(-D_CONSOLE)
	set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY  "${CMAKE_SOURCE_DIR}")
endif()






find_package(OpenGL REQUIRED)
set(OPENGL_LIBRARY ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE "${OPENGL_LIBRARY}")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(submodules/glfw ${CMAKE_CURRENT_BINARY_DIR}/extern/glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

add_subdirectory(submodules/glm ${CMAKE_CURRENT_BINARY_DIR}/extern/glm)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)

add_subdirectory(submodules/glad ${CMAKE_CURRENT_BINARY_DIR}/extern/glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

add_subdirectory(examples ${CMAKE_CURRENT_BINARY_DIR}/examples)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)