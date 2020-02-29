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

add_subdirectory(0-glut_test)

add_subdirectory(0-installare_opengl)

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

add_subdirectory(serie4/blender)
add_subdirectory(serie4/double)
add_subdirectory(serie4/double_timer)
add_subdirectory(serie4/glut_hello)
add_subdirectory(serie4/sb2db)
add_subdirectory(serie4/text)
add_subdirectory(serie4/wired_cube)

add_subdirectory(serie6/PIST_Lit)
add_subdirectory(serie6/cubo)
add_subdirectory(serie6/look_at)
add_subdirectory(serie6/planet)
add_subdirectory(serie6/pushpop)
add_subdirectory(serie6/robot)
add_subdirectory(serie6/rotateaboutvertex)
add_subdirectory(serie6/rotateaboutvertex2axes)
add_subdirectory(serie6/rotazione)
add_subdirectory(serie6/sunellipsemoon)

add_subdirectory(serie7/cubo7)

add_subdirectory(serie8/light)
add_subdirectory(serie8/light2)
add_subdirectory(serie8/movelight)
add_subdirectory(serie8/smooth)

add_subdirectory(serie9/icosaedro_flat_smooth)
add_subdirectory(serie9/lightpyramid)
add_subdirectory(serie9/material)
add_subdirectory(serie9/normali_random)

add_subdirectory(serie10/list)
add_subdirectory(serie10/lista)
add_subdirectory(serie10/stroke)
add_subdirectory(serie10/torus)
add_subdirectory(serie10/torus-slow)

add_subdirectory(serie11/bitmap)
add_subdirectory(serie11/drawf)
add_subdirectory(serie11/font)
add_subdirectory(serie11/image)
add_subdirectory(serie11/Salvataggio-file-bmp)

add_subdirectory(serie12/checker)
add_subdirectory(serie12/TextureBMP)



# ####### OPEGL 3 ################################
add_subdirectory(opengl3/opengl3_triangolo)
add_subdirectory(opengl3/opengl3_triangolo_lookat)
add_subdirectory(opengl3/opengl3_triangolo_trasformazioni)
