#type vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 0) in vec4 a_color;
layout(location = 1) in vec2 a_tex_coord;

uniform mat4 u_view_projection;

out vec2 v_tex_coord;
out vec4 v_color;

void main()
{
    v_color = a_color;
    v_tex_coord = a_tex_coord;
    gl_Position = u_view_projection * vec4(a_position, 1.0);
}



#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_color;
in vec2 v_tex_coord;

uniform vec4 u_color;
uniform float u_tiling_factor;
// texture slot
uniform sampler2D u_texture;

void main()
{
    // color = texture(u_texture, v_tex_coord * u_tiling_factor) * u_color;
    color = v_color;
}
