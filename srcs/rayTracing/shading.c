#include "../../include/miniRT.h"
#include <math.h>


// # The material parameters are constants independant of the object for now
// ambient = 0.4 * Vec3(0.4, 0.4, 1)
// k_ambient = 1
// k_diffuse = 2
// k_specular = 10
// n_specular = 50
// https://github.com/nesvoboda/minirt/blob/master/srcs/shading.c
uint32_t shading_sp(uint32_t color, t_Ray ray, t_Ray_hit hit){
	t_shape *light = init_vars()->light;

	// double index_diffuse = 2;
	double index_specular = 10;
	double n_specular = 50;
	t_Vector3d s_normal = shape_normal(hit.shape, Point3d_to_Vector3d(light->coord));
	t_Vector3d l = Vector3d_sub(Point3d_to_Vector3d(light->coord), hit.coord);
	t_Vector3d r = Vector3d_norm(Vector3d_sub(Vector3d_mult(s_normal,2), l));

	(void)ray;

	// uint32_t ambient_color = init_vars()->ambient_light->color;
	// uint32_t ambient_res = brightness(mix_colors(color, ambient_color), to_double(init_vars()->ambient_light->light_ratio));
	
	//ambient
	color = ambient(color);
	color = brightness(color, Vector3d_dot(s_normal, Vector3d_norm(l)));
	// double diffuse_res = index_diffuse  * max(Vector3d_dot(s_normal, Vector3d_norm(l)), 0) * to_double(light->light_ratio);
	double specular = index_specular * pow(max(Vector3d_dot(r, Vector3d_norm(Vector3d_mult(hit.coord, -1))), 0), n_specular) *  to_double(light->light_ratio);

if (hit.color == 0xFFC0CBFF){

	printf("\nInfo\n");
	// printf("ambient_res = %f\n", ambient_res);
	printf("diffuse_res = %f\n", Vector3d_dot(s_normal, Vector3d_norm(l)));
	printf("specular = %f\n", specular);
}

		// c = mul(asset.color, i_ambient + i_diffuse + i_specular)

	// color = 
	return (color);
}



// def render_pixel(u, v, camera, light, asset, file):
// 	c = Vec3(0, 0, 0)
// 	ray = camera.shoot_ray(u, v)
// 	intersect, i = asset.intersect(ray)
// 	if intersect:
// 		n = asset.normal(i)
// 		l = light.pos - i
// 		r = normalize(2 * n - l)

// 		l_intensity = light.strength(i) * light.color
// 		i_ambient = k_ambient * ambient
// 		i_diffuse = k_diffuse * max(dot(n, normalize(l)), 0) * l_intensity
// 		i_specular = k_specular * pow(max(dot(r, normalize(-1 * i)), 0), n_specular) * l_intensity

// 		c = mul(asset.color, i_ambient + i_diffuse + i_specular)
// 	file.write("{} {} {}\n".format(floatto8bit(c.x), floatto8bit(c.y), floatto8bit(c.z)))
