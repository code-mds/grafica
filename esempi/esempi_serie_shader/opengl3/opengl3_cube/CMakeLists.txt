project(opengl3_cube)
set(SOURCE_FILES opengl3_cube.cpp ../shaders_loader.cpp RgbImage.cpp Texture.cpp Vertex.cpp Box.cpp)

add_executable(${PROJECT_NAME}  ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS}  )

configure_file(shaders/shader.frag shaders/shader.frag COPYONLY)
configure_file(shaders/shader.vert shaders/shader.vert COPYONLY)

configure_file(images/wood_texture.bmp images/wood_texture.bmp COPYONLY)
configure_file(images/wall_texture.bmp images/wall_texture.bmp COPYONLY)
configure_file(images/roof_texture.bmp images/roof_texture.bmp COPYONLY)
