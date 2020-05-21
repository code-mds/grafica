# Set biuld dir
#########################################################
set(
        CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_HOME_DIRECTORY/serie12}
)

MESSAGE (STATUS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(TextureBMP TextureBMP.cpp RgbImage.cpp )


target_link_libraries(TextureBMP ${OPENGL_LIBRARY} ${GLUT_LIBRARY} )

