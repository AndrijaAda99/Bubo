#version 330 core

in vec4 v_Color;
in vec2 v_TexCoord;

out vec4 FragColor;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
   FragColor = texture(u_Texture, v_TexCoord) * u_Color;
}