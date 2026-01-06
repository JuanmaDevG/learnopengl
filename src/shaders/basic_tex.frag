#version 330 core

in vec2 out_tex_coord;

out vec4 color;

uniform sampler2D tex_slot;

void main()
{
  color = texture(tex_slot, out_tex_coord);
}
