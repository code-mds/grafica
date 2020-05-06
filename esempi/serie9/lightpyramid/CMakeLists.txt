add_executable(lightpyramid lightpyramid.c)


target_link_libraries(lightpyramid ${OPENGL_LIBRARY} ${GLUT_LIBRARY} )
