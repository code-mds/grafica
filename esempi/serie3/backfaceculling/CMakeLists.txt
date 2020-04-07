cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH "C:/SUPSI/freeglut")
include_directories("C:/SUPSI/freeglut/include")
include_directories("C:/SUPSI/glew-2.1.0/include")

link_directories("C:/SUPSI/freeglut/lib/x64")
link_directories("C:/SUPSI/glew-2.1.0/lib/release/x64")
set(REQUIRED_LIBS -lfreeGLUT -lglew32 -lopengl32 -lglu32)

project(backfaceculling)

set(
        CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_HOME_DIRECTORY}/serie3/backfaceculling
)

add_executable(backfaceculling main.cpp imageloader.cpp imageloader.h)

target_link_libraries(backfaceculling ${REQUIRED_LIBS} )
