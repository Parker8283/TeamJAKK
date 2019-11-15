cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project (swordthrow)

file (GLOB_RECURSE SOURCE_FILES
	${PROJECT_SOURCE_DIR}/src/*.c
	${PROJECT_SOURCE_DIR}/src/*.cpp)
file (GLOB_RECURSE HEADER_FILES
	${PROJECT_SOURCE_DIR}/include/*.h
	${PROJECT_SOURCE_DIR}/include/*.hpp)
file (GLOB_RECURSE OPENGL_FILES
	${PROJECT_SOURCE_DIR}/opengllib/Include/*.h
	${PROJECT_SOURCE_DIR}/opengllib/Include/*.hpp
	${PROJECT_SOURCE_DIR}/opengllib/Include/*.c
	${PROJECT_SOURCE_DIR}/opengllib/Include/*.cpp)
file (GLOB_RECURSE TEST_SOURCE
	${PROJECT_SOURCE_DIR}/test/*.cpp)

# Add .lib files
link_directories(${PROJECT_SOURCE_DIR}/opengllib/Lib)
# Configure assets header folder
configure_file(src/helpers/RootDir.h.in src/helpers/RootDir.h.in)

include_directories(${CMAKE_BINARY_DIR}/src)
#Define the executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# Add local project module path so cmake includes cutom cmake modules
list (APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules")
# Add local project path for find files
list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/opengllib")
list (APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

# OpenGL
find_package(OpenGL REQUIRED)
# GLM
find_package(GLM REQUIRED)
message (STATUS "GLM included at ${GLM_INCLUDE_DIR}")
# GLFW
find_package(GLFW3 REQUIRED)
message (STATUS "GLFW3 included at ${GLFW3_INCLUDE_DIR}")
# GLEW
set (CMAKE_LIBRARY_PATH "${PROJECT_SOURCE_DIR}/opengllib/Lib")
message (STATUS "CMAKE_LIBRARY_PATH included at ${CMAKE_LIBRARY_PATH}")
#find_package (GLEW REQUIRED)
set (GLEW_INCLUDE_PATH "opengllib/Include")
set (GLEW_LIBRARY "${PROJECT_SOURCE_DIR}/opengllib/Lib/glew32.lib")
message (STATUS "GLEW_LIBRARY included at ${GLEW_LIBRARY}")

# STB_IMAGE
add_library (STB_IMAGE "thirdparty/stb_image.cpp")
# GLAD
add_library (GLAD "thirdparty/glad.c")

set (FREETYPE "${PROJECT_SOURCE_DIR}/opengllib/Lib/freetype.lib")

# Put all libraries into a variable
set (LIBS glfw3 opengl32 STB_IMAGE GLAD ${GLEW_LIBRARY} ${FREETYPE})

# Define the Include DIRs
include_directories( 
	"${PROJECT_SOURCE_DIR}/src"
	"${PROJECT_SOURCE_DIR}/include"
	"${PROJECT_SOURCE_DIR}/opengllib/Include"
	"${PROJECT_SOURCE_DIR}/opengllib/Lib"
	${GLEW_INCLUDE_PATH}
)
# Define the link libraries
target_link_libraries (${PROJECT_NAME} ${LIBS} )

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


include(CTest)
enable_testing()

#add_library (stBase ${HEADER_FILES} ${SOURCE_FILES} ${LIBS} )

add_library (sword_test 
	"src/behaviors.cpp"
	"src/Collision.cpp"
	"src/Control.cpp"
	"src/Controller.cpp"
	"src/DungeonMap.cpp"
	"src/DungeonTile.cpp"
	"src/enemy.cpp"
	"src/enemy_manager.cpp"
	"src/entity.cpp"
	"src/FileLoader.cpp"
	"src/GameMath.cpp"
	"src/GameRunner.cpp"
	"src/Graphics.cpp"
	"src/MainMenu.cpp"
	"src/projectile.cpp"
	"src/Shader.cpp"
	"src/sword.cpp"
	"src/System.cpp"
	"src/TextBox.cpp"
	"src/Texture.cpp"
	"src/WindowManager.cpp"
)

# Catch (for testing)
add_library (Catch INTERFACE )
target_include_directories (Catch INTERFACE "include/catch.hpp")


add_executable (project_test ${TEST_SOURCE} ${HEADER_FILES})
target_link_libraries (project_test PUBLIC Catch sword_test ${LIBS})

add_test(NAME first_test COMMAND project_test)
