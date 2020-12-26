#version 330 core

in vec3 v_UVs;

out vec4 FragColor;

uniform samplerCube u_Skybox;

void main()
{
    FragColor = texture(u_Skybox, v_UVs);
}