#version 330 core

in vec3 v_Normal;
in vec3 v_FragPos;

out vec4 FragColor;

uniform vec3 u_lightPos;
uniform vec3 u_lightColor;
uniform vec3 u_objectColor;
uniform vec3 u_viewPos;

uniform sampler2D u_Texture;

void main()
{
   float ambientStrength = 0.5;
   vec3 ambient = ambientStrength * u_lightColor;

   vec3 norm = normalize(v_Normal);
   vec3 lightDir = normalize(u_lightPos - v_FragPos);

   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = diff * u_lightColor;

   float specularStrength = 0.5f;
   vec3 viewDir = normalize(u_viewPos - v_FragPos);
   vec3 reflectDir = reflect(-lightDir, norm);

   float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
   vec3 specular = specularStrength * spec * u_lightColor;

   vec3 result = (ambient + diffuse + specular) * u_objectColor;
   FragColor = vec4(result, 1.0f);
}