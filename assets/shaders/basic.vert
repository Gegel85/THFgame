#version 460 core

layout(location = 0) in vec3 positions;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 VertexTexCoord;

uniform mat4 mvp;
uniform mat4 mv;
uniform mat3 normalMatrix;

out vec4 position;
out vec3 N;
out vec2 TexCoord;

void main(void)
{
    position = mv * vec4(positions, 1.0);
    N = normalize(normalMatrix * normals);
    gl_Position = mvp * vec4(positions, 1.0);
    TexCoord = VertexTexCoord;
}