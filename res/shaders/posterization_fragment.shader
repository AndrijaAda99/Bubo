#version 330 core

in vec2 v_TexCoords;

out vec4 FragColor;

uniform sampler2D u_ScreenTexture;

uniform float u_Gamma;
uniform float u_NumColors;

void main()
{
   vec3 c = texture(u_ScreenTexture, v_TexCoords).rgb;
   c = pow(c, vec3(u_Gamma, u_Gamma, u_Gamma));
   c = c * u_NumColors;
   c = floor(c);
   c = c / u_NumColors;
   c = pow(c, vec3(1.0 / u_Gamma));
   FragColor = vec4(c, 1.0);
}