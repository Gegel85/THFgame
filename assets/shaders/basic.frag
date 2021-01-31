#version 460 core

in vec4 position;
in vec3 N;
in vec2 TexCoord;

out vec4 FragColors;

uniform vec3 Kd;
uniform vec3 Ks;
uniform vec3 Ka;
uniform vec3 Is[5];
uniform vec3 Id[5];
uniform vec4 lightPos[5];
uniform float shininess;
uniform sampler2D Tex1;

void main()
{
    vec4 texColor = texture( Tex1, TexCoord );
    vec3 specular = vec3(0);
    vec3 diffuse = vec3(0);
    vec3 ambient = Ka * texColor.xyz;

    for (int i = 0; i < 5; i++) {
        vec3 L = normalize(lightPos[i] - position).xyz;
        vec3 V = normalize(-position).xyz;
        vec3 H = normalize(L + V);
        float dotLn = dot(L, N);
        float d = dot(H, N);
        specular += Ks * Is[i] * max(pow(d, shininess), 0.0);
        diffuse += Kd * texColor.xyz * Id[i] * max(dotLn, 0.0);
    }

    FragColors = vec4(specular + ambient, texColor.w) + vec4(diffuse, 1.0);
}