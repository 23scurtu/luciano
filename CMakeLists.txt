cmake_minimum_required(VERSION 2.8.9)
project(luciano)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXEC "output")
set(THIRD_PARTY_DIR "third-party")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)

#Disable GLFW tests, examples, and documentation
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

#Set assimp variables
set(BUILD_ASSIMP_TOOLS  OFF)
set(BUILD_ASSIMP_SAMPLES  OFF)
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_BUILD_STATIC_LIB ON)

#Bring the headers, such as Student.h into the project
include_directories(
	src 
	${THIRD_PARTY_DIR}/assimp/include/ 
	${THIRD_PARTY_DIR}/glm
)

#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${EXEC} ${SOURCES})

find_package(OpenGL REQUIRED)

#Build GLFW as shown at http://www.glfw.org/docs/latest/build_guide.html
add_subdirectory(${THIRD_PARTY_DIR}/glfw)
include_directories(${THIRD_PARTY_DIR}/glfw/include)
target_link_libraries(${EXEC} glfw)
target_include_directories(${EXEC} PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(${EXEC} ${OPENGL_gl_LIBRARY})

#Build GLEW
find_package(GLEW REQUIRED)
add_subdirectory(${THIRD_PARTY_DIR}/glew/build/cmake ${THIRD_PARTY_DIR}/glew/build/cmake)
include_directories(${THIRD_PARTY_DIR}/glew/include)
target_link_libraries(${EXEC} glew)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

#Link assimp
add_subdirectory(${THIRD_PARTY_DIR}/assimp ${THIRD_PARTY_DIR}/assimp)
target_link_libraries(${EXEC} assimp)

#Compile and link SOIL
add_subdirectory(${THIRD_PARTY_DIR}/Simple-OpenGL-Image-Library)
target_link_libraries(${EXEC} SOIL)
include_directories(${THIRD_PARTY_DIR}/Simple-OpenGL-Image-Library/src)

#Set EntityX variables
add_definitions(-DENTITYX_RUN_BENCHMARKS=1)
set(ENTITYX_RUN_BENCHMARKS 0)
set(ENTITYX_MAX_COMPONENTS 64)
set(ENTITYX_BUILD_SHARED 1)
set(ENTITYX_BUILD_TESTING 0)
set(ENTITYX_DT_TYPE "double")

#Compile and link entityx
add_subdirectory(${THIRD_PARTY_DIR}/entityx)
target_link_libraries(${EXEC} entityx)
include_directories(${THIRD_PARTY_DIR}/entityx)


