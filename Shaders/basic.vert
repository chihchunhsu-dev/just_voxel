#version 400

layout(location = 0) in vec4 in_pos;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec4 in_normal;

out vec4 io_color;
out vec3 io_light0_pos;
out vec3 io_light1_pos;
out vec3 io_frag_pos;
out vec3 io_normal;

uniform mat4 u_projection;
uniform mat4 u_modelview;
uniform mat4 u_modelview_light;
uniform vec4 u_light0_pos;
uniform vec4 u_light1_pos;

void main()
{
	io_color = in_color;
	io_light0_pos = vec3(u_modelview_light * u_light0_pos);
	io_light1_pos = vec3(u_modelview_light * u_light1_pos);
	io_frag_pos  = vec3(u_modelview * in_pos);

	io_normal = vec3(in_normal);
	//io_normal = vec3(mat3(u_modelview) * vec3(in_normal));

	gl_Position = u_projection * u_modelview * in_pos;
}