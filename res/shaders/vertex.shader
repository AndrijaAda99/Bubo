#version 330 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_UV;
layout (location = 2) in vec3 a_Normal;
layout (location = 3) in vec3 a_Tangent;
layout (location = 4) in vec3 a_Bitangent;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;

out vec3 v_Normal;
out vec3 v_FragPos;
out vec2 v_TexCoords;

out vec3 v_TangentLight;
out vec3 v_TangentView;
out vec3 v_TangentFrag;

void main()
{
    vec4 transformedPos = u_Model * vec4(a_Pos, 1.0f);
    v_FragPos = vec3(transformedPos);
    gl_Position = u_ViewProjection * transformedPos;

    mat3 normalMatrix = mat3(transpose(inverse(u_Model)));
    vec3 T = normalize(normalMatrix * a_Tangent);
    vec3 N = normalize(normalMatrix * a_Normal);
    vec3 B = normalize(normalMatrix * a_Bitangent);

    mat3 TBN = transpose(mat3(T, B, N));
    v_TangentLight = TBN * u_LightPos;
    v_TangentView = TBN * u_ViewPos;
    v_TangentFrag = TBN * v_FragPos;

    v_Normal = mat3(transpose(inverse(u_Model))) * a_Normal;
    v_TexCoords = a_UV;

}