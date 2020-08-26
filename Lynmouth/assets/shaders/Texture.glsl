#type vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_tex_coord;
layout(location = 3) in float a_tex_index;
layout(location = 4) in float a_tiling_factor;

uniform mat4 u_view_projection;

out vec4 v_color;
out vec2 v_tex_coord;
out float v_tex_index;
out float v_tiling_factor;

void main()
{
    v_color = a_color;
    v_tex_coord = a_tex_coord;
    v_tex_index = a_tex_index;
    v_tiling_factor = a_tiling_factor;
    gl_Position = u_view_projection * vec4(a_position, 1.0);
}



#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_color;
in vec2 v_tex_coord;
in float v_tex_index;
in float v_tiling_factor;

// texture slots
uniform sampler2D u_textures[32];

void main()
{
    // ToDo: tiling factor
    vec4 tex_color = v_color;
	switch(int(v_tex_index))
	{
		case 0:  tex_color *= texture(u_textures[0],  v_tex_coord * v_tiling_factor); break;
		case 1:  tex_color *= texture(u_textures[1],  v_tex_coord * v_tiling_factor); break;
		case 2:  tex_color *= texture(u_textures[2],  v_tex_coord * v_tiling_factor); break;
		case 3:  tex_color *= texture(u_textures[3],  v_tex_coord * v_tiling_factor); break;
		case 4:  tex_color *= texture(u_textures[4],  v_tex_coord * v_tiling_factor); break;
		case 5:  tex_color *= texture(u_textures[5],  v_tex_coord * v_tiling_factor); break;
		case 6:  tex_color *= texture(u_textures[6],  v_tex_coord * v_tiling_factor); break;
		case 7:  tex_color *= texture(u_textures[7],  v_tex_coord * v_tiling_factor); break;
		case 8:  tex_color *= texture(u_textures[8],  v_tex_coord * v_tiling_factor); break;
		case 9:  tex_color *= texture(u_textures[9],  v_tex_coord * v_tiling_factor); break;
		case 10: tex_color *= texture(u_textures[10], v_tex_coord * v_tiling_factor); break;
		case 11: tex_color *= texture(u_textures[11], v_tex_coord * v_tiling_factor); break;
		case 12: tex_color *= texture(u_textures[12], v_tex_coord * v_tiling_factor); break;
		case 13: tex_color *= texture(u_textures[13], v_tex_coord * v_tiling_factor); break;
		case 14: tex_color *= texture(u_textures[14], v_tex_coord * v_tiling_factor); break;
		case 15: tex_color *= texture(u_textures[15], v_tex_coord * v_tiling_factor); break;
		case 16: tex_color *= texture(u_textures[16], v_tex_coord * v_tiling_factor); break;
		case 17: tex_color *= texture(u_textures[17], v_tex_coord * v_tiling_factor); break;
		case 18: tex_color *= texture(u_textures[18], v_tex_coord * v_tiling_factor); break;
		case 19: tex_color *= texture(u_textures[19], v_tex_coord * v_tiling_factor); break;
		case 20: tex_color *= texture(u_textures[20], v_tex_coord * v_tiling_factor); break;
		case 21: tex_color *= texture(u_textures[21], v_tex_coord * v_tiling_factor); break;
		case 22: tex_color *= texture(u_textures[22], v_tex_coord * v_tiling_factor); break;
		case 23: tex_color *= texture(u_textures[23], v_tex_coord * v_tiling_factor); break;
		case 24: tex_color *= texture(u_textures[24], v_tex_coord * v_tiling_factor); break;
		case 25: tex_color *= texture(u_textures[25], v_tex_coord * v_tiling_factor); break;
		case 26: tex_color *= texture(u_textures[26], v_tex_coord * v_tiling_factor); break;
		case 27: tex_color *= texture(u_textures[27], v_tex_coord * v_tiling_factor); break;
		case 28: tex_color *= texture(u_textures[28], v_tex_coord * v_tiling_factor); break;
		case 29: tex_color *= texture(u_textures[29], v_tex_coord * v_tiling_factor); break;
		case 30: tex_color *= texture(u_textures[30], v_tex_coord * v_tiling_factor); break;
		case 31: tex_color *= texture(u_textures[31], v_tex_coord * v_tiling_factor); break;
	}
	color = tex_color;
}
