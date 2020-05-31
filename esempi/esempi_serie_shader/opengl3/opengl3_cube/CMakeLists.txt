add_executable(opengl3_cube opengl3_cube.cpp ../shaders_loader.cpp RgbImage.cpp Texture.cpp )
target_link_libraries(opengl3_cube ${REQUIRED_LIBS}  )

configure_file(shaders/shader.frag shaders/shader.frag COPYONLY)
configure_file(shaders/shader.vert shaders/shader.vert COPYONLY)
configure_file(images/wood_texture.bmp images/wood_texture.bmp COPYONLY)
