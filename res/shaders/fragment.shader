#version 330 core

struct Material {
   sampler2D diffuse;
   sampler2D specular;
   float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 v_Normal;
in vec3 v_FragPos;
in vec2 v_TexCoords;

out vec4 FragColor;

uniform Material u_Material;
uniform Light u_Light;

uniform vec3 u_lightPos;
uniform vec3 u_lightColor;
uniform vec3 u_viewPos;

void main()
{
   // Ambient
   vec3 ambient = u_Light.ambient * vec3(texture(u_Material.diffuse, v_TexCoords));

   // Diffuse
   vec3 norm = normalize(v_Normal);
   vec3 lightDir = normalize(u_Light.position - v_FragPos);
   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = u_Light.diffuse * diff * vec3(texture(u_Material.diffuse, v_TexCoords));

   // Specular
   vec3 viewDir = normalize(u_viewPos - v_FragPos);
   vec3 reflectDir = reflect(-lightDir, norm);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
   vec3 specular = u_Light.specular * spec * vec3(texture(u_Material.specular, v_TexCoords));

   vec3 result = (ambient + diffuse + specular);
   FragColor = vec4(result, 1.0f);
}