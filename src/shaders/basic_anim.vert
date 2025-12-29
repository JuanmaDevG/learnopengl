#version 330 core

layout (location = 0) vec3 pos;

uniform float u_time;

void main()
{
  gl_Position = vec4(pos, 1.0f); //TODO: animate
}
