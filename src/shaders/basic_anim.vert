#version 330 core

layout (location = 0) in vec3 pos;

uniform float u_time;

void main()
{
  gl_Position = vec4(pos.x + (sin(u_time * 2.5) / 2.0f), pos.yz, 1.0f);
}
