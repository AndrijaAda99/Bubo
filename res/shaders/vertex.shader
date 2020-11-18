#version 330 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec3 a_Color;
layout (location = 2) in vec2 a_TexCoord;

out vec4 v_Color;
out vec2 v_TexCoord;

void main()
{
   gl_Position = vec4(a_Pos.x, a_Pos.y, a_Pos.z, 1.0f);
   v_Color = vec4(a_Color.r, a_Color.g, a_Color.b, 1.0f);
   v_TexCoord = a_TexCoord;

}