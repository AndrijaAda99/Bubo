#version 330 core

#define NUM_OF_POINT_LIGHTS (2)

struct Material {
   sampler2D diffuse;
   sampler2D specular;
   sampler2D normal;
   float shininess;
};

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

in vec3 v_Normal;
in vec3 v_FragPos;
in vec2 v_TexCoords;

in vec3 v_TangentLight;
in vec3 v_TangentView;
in vec3 v_TangentFrag;

out vec4 FragColor;

uniform Material u_Material;
uniform DirectionalLight u_DirectionalLight;
uniform PointLight u_PointLight[NUM_OF_POINT_LIGHTS];

uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir);
vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir);

void main()
{
    vec3 normal = texture(u_Material.normal, v_TexCoords).rgb;
    normal = normalize(normal * 2.0f - 1.0f);

    vec3 viewDir = normalize(v_TangentView - v_TangentFrag);

    vec3 result = vec3(0.0f, 0.0f, 0.0f);
    result += CalcDirLight(u_DirectionalLight, normal, viewDir);
    for (int i = 0; i < NUM_OF_POINT_LIGHTS; i++) {
        result += CalcPointLight(u_PointLight[i], normal, viewDir);
    }

    FragColor = vec4(result, 1.0f);
    //FragColor = texture(u_Material.normal, v_TexCoords);
}

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir) {
   // Ambient
   vec3 ambient = light.ambient * vec3(texture(u_Material.diffuse, v_TexCoords));

   // Diffuse
   vec3 lightDir = normalize(-light.direction);
   float diff = max(dot(normal, lightDir), 0.0);
   vec3 diffuse = light.diffuse * diff * vec3(texture(u_Material.diffuse, v_TexCoords));

   // Specular
   vec3 reflectDir = reflect(-lightDir, normal);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
   vec3 specular = light.specular * spec * vec3(texture(u_Material.specular, v_TexCoords));

   return (ambient + diffuse + specular);
}


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir) {
    // Point Light attenuation
    float distance = length(v_TangentLight - v_TangentFrag);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                              light.quadratic * distance * distance);

    // Ambient
    vec3 ambient  = light.ambient  * vec3(texture(u_Material.diffuse, v_TexCoords));

    // Diffuse
    vec3 lightDir = normalize(v_TangentLight - v_TangentFrag);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(u_Material.diffuse, v_TexCoords));

    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(u_Material.specular, v_TexCoords));

    return (ambient + diffuse + specular);
}