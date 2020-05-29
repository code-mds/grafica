add_executable(opengl3_triangolo_trasformazioni opengl3_triangolo_trasformazioni.cpp ../shaders_loader.cpp)
target_link_libraries(opengl3_triangolo_trasformazioni ${REQUIRED_LIBS}  )

configure_file(shaders/shader.frag shaders/shader.frag COPYONLY)
configure_file(shaders/shader.vert shaders/shader.vert COPYONLY)
