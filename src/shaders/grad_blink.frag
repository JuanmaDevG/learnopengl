#version 330 core

uniform float u_time;

out vec4 color;

void main()
{
  color = vec4(0.5f + (sin(u_time) / 2), 0.5f + (cos(u_time) / 2), 0.5f + (cos(u_time * 2) / 3), 1.0f);
}
