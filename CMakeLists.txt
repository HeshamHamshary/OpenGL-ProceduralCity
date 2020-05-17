cmake_minimum_required(VERSION 3.0.0)
project(sample VERSION 0.1.0)

set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)

add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/glm)
add_subdirectory(thirdparty/assimp)
add_subdirectory(thirdparty/glew/build/cmake)

include_directories(
    thirdparty/glfw/include 
    thirdparty/glm 
    thirdparty/glew/include 
    thirdparty/assimp/include 
    ${OPENGL_INCLUDE_DIRS})

file(GLOB_RECURSE SAMPLEFW_SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/samplefw/*.c
    ${CMAKE_SOURCE_DIR}/samplefw/*.cpp)

file(GLOB_RECURSE SAMPLEFW_HEADER_FILES 
	${CMAKE_SOURCE_DIR}/samplefw/*.h
    ${CMAKE_SOURCE_DIR}/samplefw/*.hpp)

file(GLOB_RECURSE WOLF_SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/wolf/*.c
    ${CMAKE_SOURCE_DIR}/wolf/*.cpp)

file(GLOB_RECURSE WOLF_HEADER_FILES 
	${CMAKE_SOURCE_DIR}/wolf/*.h
    ${CMAKE_SOURCE_DIR}/wolf/*.hpp)

file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)
	
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/src/*.h
    ${CMAKE_SOURCE_DIR}/src/*.hpp)

add_executable(sample 
    ${SAMPLEFW_SOURCE_FILES}
    ${SAMPLEFW_HEADER_FILES}
    ${WOLF_SOURCE_FILES}
    ${WOLF_HEADER_FILES}
    ${SOURCE_FILES}
    ${HEADER_FILES}
    )

target_link_libraries(sample assimp glfw glew ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
