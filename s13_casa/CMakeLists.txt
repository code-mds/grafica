project(s13_casa)
set(SOURCE_FILES Texture.cpp RgbImage.cpp solid.cpp shaders_loader.cpp vertex.cpp camera.cpp house.cpp main.cpp)

configure_file(images/flag_texture.bmp images/flag_texture.bmp COPYONLY)
configure_file(images/wall_texture.bmp images/wall_texture.bmp COPYONLY)
configure_file(images/wood_texture.bmp images/wood_texture.bmp COPYONLY)
configure_file(images/roof_texture.bmp images/roof_texture.bmp COPYONLY)
configure_file(images/marble_texture.bmp images/marble_texture.bmp COPYONLY)

configure_file(shaders/shader.frag shaders/shader.frag COPYONLY)
configure_file(shaders/shader.vert shaders/shader.vert COPYONLY)

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)

if(APPLE)
    message(INFO ": PLATFORM APPLE")
    include_directories("/usr/local/include")

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
            ${GLFW3_LIBRARIES}
            ${GLEW_LIBRARIES}
            ${OPENGL_LIBRARY}
            )

#endif(APPLE)
#if(UNIX)
#    message(INFO ": PLATFORM LINUX")
#
#    set(OPENGL_LIBRARY -lGL)
#    set(GLUT_LIBRARY -lglut -lGLU)
else()
    message(INFO ": PLATFORM WINDOWS")

    set(CMAKE_PREFIX_PATH "C:/SUPSI/freeglut/opengl")
    include_directories("C:/SUPSI/opengl/freeglut/include")
    include_directories("C:/SUPSI/opengl/glew-2.1.0/include")
    include_directories("C:/SUPSI/opengl/glm-0.9.9.8/glm")

    link_directories("C:/SUPSI/opengl/freeglut/lib/x64")
    link_directories("C:/SUPSI/opengl/glew-2.1.0/lib/release/x64")

    set(OPENGL_LIBRARY -lopengl32)
    set(GLUT_LIBRARY -lfreeGLUT -lglu32)
    set(GLEW_LIBRARIES -lglew32)

endif()
set(REQUIRED_LIBS ${GLUT_LIBRARY} ${GLEW_LIBRARIES} ${OPENGL_LIBRARY})
add_executable(${PROJECT_NAME}  ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS})
