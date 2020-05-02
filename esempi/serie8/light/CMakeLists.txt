add_executable(light light.c)


target_link_libraries(light ${OPENGL_LIBRARY} ${GLUT_LIBRARY} )
