#version 330 core

uniform vec3 L = vec3(0, 1, 0);
uniform vec3 ambient = vec3(0.5, 0.5, 0.5);

in vec3 N;
in vec3 interpolateColor;

out vec3 color;

void main()
{
    color =  ambient * interpolateColor + max(dot(L, N), 0.0) * interpolateColor;
}
