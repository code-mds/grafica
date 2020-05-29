cmake_minimum_required(VERSION 3.9)
project(GL_Esempi)

set(CMAKE_CXX_STANDARD 11)

if(APPLE)
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

else()
    message(INFO ": PLATFORM WINDOWS")

    set(CMAKE_PREFIX_PATH "C:/SUPSI/opengl/freeglut")

    include_directories("C:/SUPSI/opengl/freeglut/include")
    link_directories("C:/SUPSI/opengl/freeglut/lib/x64")

    include_directories("C:/SUPSI/opengl/glew-2.1.0/include")
    link_directories("C:/SUPSI/opengl/glew-2.1.0/lib/release/x64")

    include_directories("C:/SUPSI/opengl/glfw-3.3.2.bin.WIN64/include")
    link_directories("C:/SUPSI/opengl/glfw-3.3.2.bin.WIN64/lib-mingw-w64")

    include_directories("C:/SUPSI/opengl/glm-0.9.9.8/glm")

    set(OPENGL_LIBRARY -lopengl32)
    set(GLUT_LIBRARY -lfreeGLUT -lglu32)
    set(GLEW_LIBRARIES -lglew32)
    set(GLFW3_LIBRARIES -lglfw3)
endif()

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
