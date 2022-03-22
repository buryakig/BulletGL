
set(EXAMPLE_NAME Sandbox)

file(GLOB_RECURSE SRC_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.c??)
file(GLOB_RECURSE HEADER_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.h)

SETUP_GROUPS("${SRC_FILES}")
SETUP_GROUPS("${HEADER_FILES}")

add_executable(${EXAMPLE_NAME}  ${SRC_FILES} ${HEADER_FILES})

target_include_directories(${EXAMPLE_NAME} PRIVATE ../../include/)
target_include_directories(${EXAMPLE_NAME} PRIVATE ../../src/BulletGL/)
target_include_directories(${EXAMPLE_NAME} PRIVATE src/Sandbox/)

target_include_directories(${EXAMPLE_NAME} PRIVATE ../../submodules/glad/include/)
target_include_directories(${EXAMPLE_NAME} PRIVATE ../../submodules/glfw/include/)
target_include_directories(${EXAMPLE_NAME} PRIVATE ../../submodules/glm/)

if(MSVC)
	add_definitions(-D_CONSOLE)
	set_property(TARGET ${EXAMPLE_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY  "${CMAKE_SOURCE_DIR}")
endif()

target_link_libraries(${EXAMPLE_NAME} PRIVATE ${PROJECT_NAME})