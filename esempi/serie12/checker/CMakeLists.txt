add_executable(checker checker.c)


target_link_libraries(checker ${OPENGL_LIBRARY} ${GLUT_LIBRARY} )
