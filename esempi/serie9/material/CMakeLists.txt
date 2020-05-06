add_executable(material material.c)


target_link_libraries(material ${OPENGL_LIBRARY} ${GLUT_LIBRARY} )
