#version 330 core

in vec4 Color;

out vec4 FragColor;

uniform vec4 u_Color;

void main()
{
   FragColor = Color + u_Color;
}