add_executable(smooth smooth.c)


target_link_libraries(smooth ${OPENGL_LIBRARY} ${GLUT_LIBRARY} )
