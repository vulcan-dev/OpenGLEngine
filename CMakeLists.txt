# Projects Settings
cmake_minimum_required (VERSION 3.1)
project (OpenGLEngine)

file(GLOB_RECURSE SOURCE_FILES 
	Engine/Source/*.cpp
	Engine/Source/Core/*.cpp
	Engine/Source/Core/Utilities/*.cpp)
	
# Add header files
file(GLOB_RECURSE HEADER_FILES
	lib/spdlog/include
	lib/glfw/include
	lib/glew/include
	lib/glm/

	Engine/Source/*.h
	Engine/Source/Core/*.h
	Engine/Source/Core/Utilities/*.h)

configure_file(Engine/Source/RootDir.h.in Engine/Source/RootDir.h)

include_directories(HEADER_FILES)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DEBUG_MODE")

# The main executable
add_executable(main
  ${SOURCE_FILES}
)

set(LIBS glfw libglew_static glm spdlog::spdlog)

set_property(TARGET main PROPERTY CXX_STANDARD 20)
target_compile_options(main PRIVATE -Wall)

add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)

add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)

add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
add_subdirectory(lib/spdlog EXCLUDE_FROM_ALL)

target_link_libraries(main PRIVATE ${LIBS})