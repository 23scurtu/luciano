cmake_minimum_required(VERSION 2.8.9)
project(Test)
set(EXEC "output")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)

#Disable GLFW tests, examples, and documentation
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

#Bring the headers, such as Student.h into the project
include_directories(include)
 
#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")
 
add_executable(${EXEC} ${SOURCES})

find_package(OpenGL REQUIRED)

#Build GLFW as shown at http://www.glfw.org/docs/latest/build_guide.html
add_subdirectory(glfw-3.2.1)
include_directories(glfw-3.2.1/include)
target_link_libraries(${EXEC} glfw)
target_include_directories(${EXEC} PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(${EXEC} ${OPENGL_gl_LIBRARY})
