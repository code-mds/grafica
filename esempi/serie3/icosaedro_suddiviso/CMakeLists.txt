cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH "C:/SUPSI/freeglut")
include_directories("C:/SUPSI/freeglut/include")
include_directories("C:/SUPSI/glew-2.1.0/include")

link_directories("C:/SUPSI/freeglut/lib/x64")
link_directories("C:/SUPSI/glew-2.1.0/lib/release/x64")
set(REQUIRED_LIBS -lfreeGLUT -lglew32 -lopengl32 -lglu32)

project(icosaedro_suddiviso)
add_executable(icosaedro_suddiviso icosaedro_suddiviso.c)
target_link_libraries(icosaedro_suddiviso ${REQUIRED_LIBS} )
