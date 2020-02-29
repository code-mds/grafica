cmake_minimum_required(VERSION 3.15)
project(s3_bandiera)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_PREFIX_PATH "C:/SUPSI/freeglut")
find_package(GLUT REQUIRED)

include_directories("C:/SUPSI/freeglut/include")
include_directories("C:/SUPSI/glew-2.1.0/include")

link_directories("C:/SUPSI/freeglut/lib/x64")
link_directories("C:/SUPSI/glew-2.1.0/lib/release/x64")

add_executable(s3_bandiera2 main.cpp)
target_link_libraries(s3_bandiera2 -lfreeGLUT -lglew32 -lopengl32 -lglu32)