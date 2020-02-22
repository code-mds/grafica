cmake_minimum_required(VERSION 3.15)
project(glut_test)
set(CMAKE_CXX_STANDARD 14)

add_executable(glut_test glut_test.cpp)
target_link_libraries(glut_test -lfreeGLUT -lglew32 -lopengl32 -lglu32)