add_executable(bitmap bitmap.c)


target_link_libraries(bitmap ${OPENGL_LIBRARY} ${GLUT_LIBRARY} )
