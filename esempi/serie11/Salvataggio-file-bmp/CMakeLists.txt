
add_executable(Salvataggio-file-bmp planet.cpp RgbImage.cpp)

target_link_libraries(Salvataggio-file-bmp ${OPENGL_LIBRARY} ${GLUT_LIBRARY} )

