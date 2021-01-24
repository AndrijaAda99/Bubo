#version 330 core

in vec2 v_TexCoords;

out vec4 FragColor;

uniform sampler2D u_ScreenTexture;

uniform float u_Gamma;
uniform float u_Levels;

void main()
{
   FragColor = texture(u_ScreenTexture, v_TexCoords);

   FragColor.rgb = pow(FragColor.rgb, vec3(1.0f / u_Gamma));

   float greyscale = max(FragColor.r, max(FragColor.g, FragColor.b));

   float lower = floor(greyscale * u_Levels) / u_Levels;
   float lowerDiff = abs(greyscale - lower);

   float upper = ceil(greyscale * u_Levels) / u_Levels;
   float upperDiff = abs(upper - greyscale);

   float level = lowerDiff <= upperDiff ? lower : upper;
   float adjustment = level / greyscale;

   FragColor.rgb = FragColor.rgb * adjustment;

   FragColor.rgb = pow(FragColor.rgb, vec3(u_Gamma));
}
