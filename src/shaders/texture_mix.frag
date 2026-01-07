#version 330 core

in vec2 texture_coords;

out vec4 color;

uniform sampler2D tx1_id;
uniform sampler2D tx2_id;

void main()
{
  color = mix(texture(tx1_id, texture_coords), texture(tx2_id, texture_coords), 0.2);
}
