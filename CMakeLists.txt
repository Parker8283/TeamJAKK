cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project (swordthrow)

file (GLOB_RECURSE SOURCE_FILES
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)
file (GLOB_RECURSE HEADER_FILES
	${CMAKE_SOURCE_DIR}/include/*.h
	${CMAKE_SOURCE_DIR}/include/*.hpp)
file (GLOB_RECURSE OPENGL_FILES
	${CMAKE_SOURCE_DIR}/opengllib/Include/*.h
	${CMAKE_SOURCE_DIR}/opengllib/Include/*.hpp
	${CMAKE_SOURCE_DIR}/opengllib/Include/*.c
	${CMAKE_SOURCE_DIR}/opengllib/Include/*.cpp)

# Add .lib files
link_directories(${CMAKE_SOURCE_DIR}/opengllib/Lib)
# Configure assets header folder
configure_file(src/helpers/RootDir.h.in src/helpers/RootDir.h.in)

include_directories(${CMAKE_BINARY_DIR}/src)
#Define the executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

#Need a CMAKE_DIR with some code in it to find external libraries
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
# OpenGL
find_package(OpenGL REQUIRED)
# GLM
find_package(GLM REQUIRED)
message (STATUS "GLM included at ${GLM_INCLUDE_DIR}")
# GLFW
find_package(GLFW3 REQUIRED)
message (STATUS "GLFW3 included at ${GLFW3_INCLUDE_DIR}")
# GLEW
#find_package(GLEW REQUIRED)
#message (STATUS "GLEW included at ${GLEW_INCLUDE_DIR}")
#find_package(GLEW REQUIRED)
#if (GLEW_FOUND)
#    include_directories(${GLEW_INCLUDE_DIRS})
#    link_libraries(${GLEW_LIBRARIES})
#endif()
set (GLEW_INCLUDE_PATH "opengllib/Include")
set (GLEW_LIBRARY "" CACHE FILEPATH "glew32s.lib or glew32.lib")

# STB_IMAGE
add_library (STB_IMAGE "thirdparty/stb_image.cpp")
# GLAD
add_library (GLAD "thirdparty/glad.c")

# Put all libraries into a variable
set (LIBS glfw3 opengl32 STB_IMAGE GLAD ${GLEW_LIBRARY})

# Define the Include DIRs
include_directories( 
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/include"
	"${CMAKE_SOURCE_DIR}/opengllib/Include"
	"${CMAKE_SOURCE_DIR}/opengllib/Lib"
	${GLEW_INCLUDE_PATH}
)
# Define the link libraries
target_link_libraries (${PROJECT_NAME} ${LIBS})

# Create virtual folders to make it look nicer in VS
if(MSVC_IDE)
	# Macro to preserve source files hierarchy in the IDE
	macro(GroupSources curdir)
		file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir} ${PROJECT_SOURCE_DIR}/${curdir}/*)

		foreach(child ${children})
			if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
				GroupSources(${curdir}/${child})
			else()
				string(REPLACE "/" "\\" groupname ${curdir})
				string(REPLACE "src" "Sources" groupname ${groupname})
				source_group(${groupname} FILES ${PROJECT_SOURCE_DIR}/${curdir}/${child})
			endif()
		endforeach()
	endmacro()

	# Run macro
	GroupSources(src)
endif()

# Copy dlls
if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${PROJECT_SOURCE_DIR}/dlls"
		$<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()