#version 330 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_UV;
layout (location = 2) in vec3 a_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

out vec3 v_Normal;
out vec3 v_FragPos;
out vec2 v_TexCoords;

void main()
{
   vec4 transformedPos = u_Model * vec4(a_Pos, 1.0f);

   gl_Position = u_ViewProjection * transformedPos;
   v_FragPos = vec3(transformedPos);
   v_Normal = mat3(transpose(inverse(u_Model))) * a_Normal;
   v_TexCoords = a_UV;
}