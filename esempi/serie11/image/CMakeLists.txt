add_executable(image image.c)


target_link_libraries(image ${OPENGL_LIBRARY} ${GLUT_LIBRARY} )
