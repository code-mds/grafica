#version 330 core

in vec3 outColor;
in vec2 TexCoord;

out vec4 FragColor;
// texture sampler
uniform sampler2D texture1;

void main()
{
    //FragColor = vec4(outColor, 1.0f);
    FragColor = texture(texture1, TexCoord);
}

