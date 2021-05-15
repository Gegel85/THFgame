#version 460 core

uniform vec3 Kd;
uniform vec3 Ks;
uniform vec3 Ka;
uniform vec3 Is[5];
uniform vec3 Id[5];
uniform vec4 lightPos[5];
uniform float shininess;
uniform sampler2D Tex1;

in vec4 position;
in vec3 N;
in vec2 TexCoord;

out vec4 FragColors;

void main()
{
    vec4 texColor = texture( Tex1, TexCoord );

    FragColors = texColor;
}