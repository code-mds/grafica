#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 outColor;
out vec2 TexCoord;

// Uniform variables
uniform mat4 modelview_matrix;
uniform mat4 projection_matrix;

void main()
{
    // Applica la trasformazione modelview
    vec4 pos = modelview_matrix * vec4(aPos, 1.0f);

    // Applica la matrice di proiezione
    gl_Position = projection_matrix * pos;

    // Passa semplicemente il colore al fragment shader
    outColor = aColor;
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}

