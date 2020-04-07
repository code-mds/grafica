cmake_minimum_required(VERSION 3.9)
project(GL_Esempi)

set(CMAKE_CXX_STANDARD 11)

# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

# FIND GLUT
# NOTA: in realtà si tratta della libreria FreeGLUT
#########################################################
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)


# GLEW
#########################################################
find_package(GLEW)
include_directories(${GLEW_INCLUDE_DIR})
link_libraries(${GLEW_LIBRARIES})
include_directories("/usr/local/include")
link_libraries("/usr/local/lib/libGLEW.a")

# GLFW.
#########################################################
find_package(GLFW3 REQUIRED)
include_directories(${GLFW3_INCLUDE_DIR})

# Set necessary libs.
set(REQUIRED_LIBS
       ${GLUT_LIBRARY}
        ${GLEW_LIBRARIES}
        ${GLFW3_LIBRARIES}
        ${OPENGL_LIBRARY}
        )

add_subdirectory(serie3/backfaceculling)
add_subdirectory(serie3/colorbuffer)
add_subdirectory(serie3/edge)
add_subdirectory(serie3/icosaedro_suddiviso)
add_subdirectory(serie3/line_stripple)
add_subdirectory(serie3/polys)
add_subdirectory(serie3/primitive)
add_subdirectory(serie3/triangolo)
add_subdirectory(serie3/rettangolo)
add_subdirectory(serie3/triangolo_array)
add_subdirectory(serie3/triangle_strip)