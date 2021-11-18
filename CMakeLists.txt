# Projects Settings
cmake_minimum_required (VERSION 3.1)
project (OpenGLEngine)

file(GLOB_RECURSE SOURCE_FILES 
	Engine/ThirdParty/*.c
	Engine/*.cpp
	Application/*.cpp
)
	
# Add header files
file(GLOB_RECURSE HEADER_FILES
	lib/spdlog/include
	lib/glfw/include
	lib/glew/include
	lib/imgui
	lib/glm/
)

configure_file(Engine/RootDir.h.in Engine/RootDir.h)

include_directories(HEADER_FILES)

set(CMAKE_BUILD_TYPE Debug)

# The main executable
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_MODE")
add_executable(main ${SOURCE_FILES} Application/Events.h Engine/Resources.cpp Engine/Render/Renderer.h)

set(LIBS glfw libglew_static glm spdlog::spdlog)

set_property(TARGET main PROPERTY CXX_STANDARD 20)
target_compile_options(main PRIVATE -Wall)

add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)

add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)

add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
add_subdirectory(lib/spdlog EXCLUDE_FROM_ALL)

target_link_libraries(main PRIVATE ${LIBS})