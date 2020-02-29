set(CMAKE_CXX_STANDARD 14)
set(CMAKE_PREFIX_PATH "C:/SUPSI/freeglut")
include_directories("C:/SUPSI/freeglut/include")
include_directories("C:/SUPSI/glew-2.1.0/include")

link_directories("C:/SUPSI/freeglut/lib/x64")
link_directories("C:/SUPSI/glew-2.1.0/lib/release/x64")

add_executable(rettangolo rettangolo.c)
target_link_libraries(rettangolo -lfreeGLUT -lglew32 -lopengl32 -lglu32)