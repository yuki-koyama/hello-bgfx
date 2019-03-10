$input v_pos, v_view, v_normal, v_color0

#include <bgfx_shader.sh>

void main()
{
	vec3 light_dir = normalize(vec3(1.0, 1.0, 1.0));
	vec3 normal = normalize(v_normal);
	vec3 view = normalize(v_view);
	vec3 ambient = vec3(0.1, 0.1, 0.1);
	vec3 lambert = max(0.0, dot(normal, light_dir)) * v_color0.xyz;

	gl_FragColor.xyz = pow(ambient + lambert, vec3_splat(1.0 / 2.2));
	gl_FragColor.w = 1.0;
}
