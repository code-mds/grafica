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
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})


# GLFW.
#########################################################
find_package(GLFW3 REQUIRED)
include_directories(${GLFW3_INCLUDE_DIR})

# Set necessary libs.
set(REQUIRED_LIBS
       ${GLUT_LIBRARY}
        ${GLFW3_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${OPENGL_LIBRARY}
        )



# ####### OPEGL 3 ################################
add_subdirectory(opengl3/opengl3_triangolo)
add_subdirectory(opengl3/opengl3_triangolo_lookat)
add_subdirectory(opengl3/opengl3_triangolo_trasformazioni)
