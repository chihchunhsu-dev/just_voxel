#version 400

in vec4 io_color;
in vec3 io_light0_pos;
in vec3 io_light1_pos;
in vec3 io_frag_pos;
in vec3 io_normal;

out vec4 out_frag_color;

void main()
{
	// Ambient
	vec3 ka = vec3(0.7);	
	vec4 ambient = io_color * vec4(ka, 1.0);

	// Diffuse
	float color_correction0 = 0.4;
	float color_correction1 = 0.3;
	vec3 normal = normalize(io_normal);
    vec3 light0_dir = normalize(io_light0_pos - io_frag_pos); 
	vec3 light1_dir = normalize(io_light1_pos - io_frag_pos);
	float diff0 = max(dot(normal, light0_dir), 0.0);
	float diff1 = max(dot(normal, light1_dir), 0.0);
	vec4 diffuse0 = io_color * diff0 * color_correction0;
	vec4 diffuse1 = io_color * diff1 * color_correction1;
	vec4 diffuse = diffuse0 + diffuse1;

	out_frag_color = ambient + diffuse;
}
