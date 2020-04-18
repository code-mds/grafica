cmake_minimum_required(VERSION 3.9)
project(GL_Esempi)

set(CMAKE_CXX_STANDARD 11)

if(APPLE)
    message(INFO ": PLATFORM APPLE")

    include_directories("/usr/local/include")
    find_package(OpenGL REQUIRED)
    include_directories(${OpenGL_INCLUDE_DIRS})
    link_directories(${OpenGL_LIBRARY_DIRS})
    add_definitions(${OpenGL_DEFINITIONS})
    if(NOT OPENGL_FOUND)
        message(ERROR " OPENGL not found!")
    endif(NOT OPENGL_FOUND)

    find_package(GLUT REQUIRED)
    include_directories(${GLUT_INCLUDE_DIRS})
    link_directories(${GLUT_LIBRARY_DIRS})
    add_definitions(${GLUT_DEFINITIONS})
    if(NOT GLUT_FOUND)
        message(ERROR " GLUT not found!")
    endif(NOT GLUT_FOUND)
else()
    message(INFO ": PLATFORM WINDOWS")

    set(CMAKE_PREFIX_PATH "C:/SUPSI/freeglut")
    include_directories("C:/SUPSI/freeglut/include")
    include_directories("C:/SUPSI/glew-2.1.0/include")

    link_directories("C:/SUPSI/freeglut/lib/x64")
    link_directories("C:/SUPSI/glew-2.1.0/lib/release/x64")

    set(OPENGL_LIBRARY -lopengl32)
    set(GLUT_LIBRARY -lfreeGLUT -lglu32)
    set(GLEW_LIBRARIES -lglew32)
endif()

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