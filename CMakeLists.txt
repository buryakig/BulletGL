cmake_minimum_required(VERSION 3.6)
set(CMAKE_SUPPRESS_REGENERATION true)

set(FOLDER_NAME BulletGL)
set(PROJECT_NAME BulletGL)

project(${PROJECT_NAME} CXX)

# Options
option(BUILD_WITH_EASY_PROFILER "Enable EasyProfiler usage" ON)
option(BUILD_WITH_OPTICK "Enable Optick usage" OFF)

include(CMake/CMakeMacros.txt)

# Dunno
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Setting up python for bootstrap
if(WIN32)
	set(PYTHON_EXECUTABLE "python")
else()
	set(PYTHON_EXECUTABLE "python3")
endif()

# Exetuting bootstrap
if((NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/submodules/.bootstrap.json") OR ("${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt" IS_NEWER_THAN "${CMAKE_CURRENT_SOURCE_DIR}/submodules/.bootstrap.json"))
	execute_process(
		COMMAND ${PYTHON_EXECUTABLE} "bootstrap.py"
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		RESULT_VARIABLE bootstrap_result
	)
	if (NOT (${bootstrap_result} EQUAL 0))
		message(FATAL_ERROR "Cannot run bootstrap.py")
	endif()
endif()

# Parameters to build GLFW with
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")
# Parameters to build EasyProfiler with
set(EASY_PROFILER_NO_GUI ON CACHE BOOL "")
set(EASY_PROFILER_NO_SAMPLES ON CACHE BOOL "")
# Parameters to build Assimp with
set(ASSIMP_NO_EXPORT ON CACHE BOOL "")
set(BUILD_SHARED_LIBS  OFF CACHE BOOL "")
set(ASSIMP_BUILD_DRACO OFF CACHE BOOL "")
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "")
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "")
set(ASSIMP_INSTALL_PDB OFF CACHE BOOL "")
set(BUILD_DOCS    OFF CACHE BOOL "")
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "")
set(ASSIMP_BUILD_OBJ_IMPORTER ON CACHE BOOL "")
set(ASSIMP_BUILD_GLTF_IMPORTER ON CACHE BOOL "")
# Parameters to build YAML with
set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "")
set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "")



# Excluding compiler warnings with project define 
#if(WIN32)
#	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
#endif()

# Adding submodules CmakeLists to this one
add_subdirectory(submodules/src/glfw)
add_subdirectory(submodules/src/easy_sources)
add_subdirectory(submodules/src/assimp)
add_subdirectory(submodules/src/yaml)
if(BUILD_WITH_OPTICK)
add_subdirectory(submodules/src/optick)
endif()

include_directories(.)
include_directories(submodules/src)
include_directories(submodules/src/imgui)
include_directories(submodules/src/glfw/include)
include_directories(submodules/src/glm)
include_directories(submodules/glad/include)
include_directories(submodules/src/stb)
include_directories(submodules/src/optick/src)
include_directories(submodules/src/assimp/include)
include_directories(submodules/src/yaml/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/submodules/src/assimp/include)

# Setting macros for glad linking
set(GLAD_SOURCES submodules/glad/src/glad.c submodules/glad/include/glad/glad.h)# submodules/glad/src/vulkan.c)
#if(WIN32)
#	set(GLAD_SOURCES ${GLAD_SOURCES} submodules/glad/src/wgl.c)
#endif()

add_library(glad ${GLAD_SOURCES})

if(BUILD_WITH_EASY_PROFILER)
	message("Enabled EasyProfiler")
	add_definitions(-DBUILD_WITH_EASY_PROFILER=1)
	include_directories(submodules/src/easy_profiler/include)
	set_property(TARGET easy_profiler PROPERTY FOLDER "ThirdPartyLibraries")
	set_property(TARGET profiler_converter PROPERTY FOLDER "ThirdPartyLibraries")
endif()
if(BUILD_WITH_OPTICK)
	message("Enabled Optick")
	add_definitions(-DBUILD_WITH_OPTICK=1)
	set_property(TARGET OptickCore PROPERTY FOLDER "ThirdPartyLibraries")
endif()
if(WIN32)
set_property(TARGET zlib          PROPERTY FOLDER "ThirdPartyLibraries")
set_property(TARGET zlibstatic    PROPERTY FOLDER "ThirdPartyLibraries")
set_property(TARGET UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTY FOLDER "ThirdPartyLibraries")
endif()
set_property(TARGET uninstall     PROPERTY FOLDER "ThirdPartyLibraries")
set_property(TARGET glfw          PROPERTY FOLDER "ThirdPartyLibraries")
set_property(TARGET assimp        PROPERTY FOLDER "ThirdPartyLibraries")
set_property(TARGET glad          PROPERTY FOLDER "ThirdPartyLibraries")
set_property(TARGET IrrXML        PROPERTY FOLDER "ThirdPartyLibraries")
set_property(TARGET yaml-cpp          PROPERTY FOLDER "ThirdPartyLibraries")







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

target_link_libraries(${PROJECT_NAME} glfw glad easy_profiler assimp yaml-cpp)
if(BUILD_WITH_OPTICK)
target_link_libraries(${PROJECT_NAME} OptickCore)
endif()

add_subdirectory(examples ${CMAKE_CURRENT_BINARY_DIR}/examples)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)