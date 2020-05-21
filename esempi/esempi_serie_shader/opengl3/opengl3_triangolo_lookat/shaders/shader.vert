#version 330 core
in vec3 position;


// Uniform variables
uniform mat4 modelview_matrix;
uniform mat4 projection_matrix;

void main()
{
    // Applica la trasformazione modelview
    vec4 pos = modelview_matrix * vec4(position, 1.0f);

    // Applica la matrice di proiezione
    gl_Position = projection_matrix * pos;

}

