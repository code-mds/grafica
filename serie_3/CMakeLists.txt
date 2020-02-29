cmake_minimum_required(VERSION 3.15)
project(serie_3)
set(CMAKE_CXX_STANDARD 14)

include_directories("C:/SUPSI/freeglut/include")
include_directories("C:/SUPSI/glew-2.1.0/include")

link_directories("C:/SUPSI/freeglut/lib/x64")
link_directories("C:/SUPSI/glew-2.1.0/lib/release/x64")

add_executable(serie_3 main.cpp)
target_link_libraries(serie_3 -lfreeGLUT -lglew32 -lopengl32 -lglu32)