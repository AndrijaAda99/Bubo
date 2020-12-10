#version 330 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_UV;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

out vec2 v_UV;

void main()
{
   gl_Position = u_ViewProjection * u_Model * vec4(a_Pos.x, a_Pos.y, a_Pos.z, 1.0f);
   v_UV = a_UV;
}