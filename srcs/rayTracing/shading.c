#include "../../include/miniRT.h"
#include <math.h>


uint32_t shading_sp(uint32_t color, t_Ray ray, t_Ray_hit hit){
	(void)hit;
	(void)ray;

	// t_Vector3d cc = ray.o;
	// t_Vector3d cd = Vector3d_mult(Vector3d_norm(ray.d), -1);
	// t_Vector3d sc = Point3d_to_Vector3d(hit.shape->coord);
	

	// double sr = to_double(hit.shape->radius);
	// double t = Vector3d_dot(Vector3d_sub(sc, cc), cd)/ Vector3d_dot(cd, cd) ;
	// double c = 0;
	// t_Vector3d p = Vector3d_add(cc, Vector3d_mult(cd, t));
	// double y = Vector3d_length(Vector3d_sub(sc,p));
	// if(y < sr)
	// {
	// 	double x = sqrt((sr * sr) - (y * y));
	// 	double t1 = t - x;
	// 	c = remap( sc.z, sc.z - sr, t1);
	// 	// c = clampd(c, 0, 1);
	// 	printf("Aft c = %f\n", c);
	// 	color = brightness(color, c);
	// }
	// return color;
  
	// //Shape Coords(sc)
	// t_Vector3d sc = Point3d_to_Vector3d(hit.shape->coord);

	// //Light Coords(lc) 
	// t_Vector3d lc = hit.coord;

	// //Light Direction(ld)
	// t_Vector3d ld = ray_direction(sc,lc);

	// //Light color(lcolor)
	// uint32_t lcolor = init_vars()->light->color;

	// //diffuse
	// t_Vector3d norm = Vector3d_init(0.0, 0.0, 1.0);
    // double diffuse = fmax(Vector3d_dot(ld, norm),0.0) * mix_colors(color, lcolor, 0.5);
	// //Specular
	// //Camera Coords(cc)
	// t_Vector3d cc = Point3d_to_Vector3d(init_vars()->camera->coord);
	// t_Vector3d point =  Vector3d_add(Vector3d_init(0.0, 0.0, 0.0), Vector3d_mult(norm,5.0));
	
	// t_Vector3d toEye = Vector3d_norm(Vector3d_sub(cc, point));
	// t_Vector3d reflectLight = Vector3d_norm(reflect(ld, norm));
	// float specPower = 30.0;
	// // t_Vector3d specMaterial = Vector3d_init(1.0, 1.0, 0.75);

	// // uint32_t specColor = lc * specMaterial * pow(fmax(dot(toEye, reflectLight), 0.0), specPower);
	// uint32_t specColor = lcolor * pow(fmax(Vector3d_dot(toEye, reflectLight), 0.0), specPower);
	
	// // color = + diffuse + specColor;
	// color = ambient(hit.color) + diffuse + specColor;

	color = brightness(color, 1.2);
	return (color);
}

/*
     	vec3 lightDirection = vec3(1.0, -1.0, 0.0);
        vec3 lightColor = vec3(1, 1, 1);

       lightDirection = normalize(lightDirection);
        
        //ambient
        vec3 ambient = color * 0.1;

        //diffuse
        vec3 diffuse = max(dot(lightDirection, norm),0.0) * (color * lightColor);

        //specular
        vec3 eyePos = vec3(0.0,0.0,-1.0);
        vec3 point = vec3(0.0, 0.0, 0.0) + 5.0 * norm;
        
        vec3 toEye = normalize(eyePos - point);
        vec3 reflectLight = normalize(reflect(lightDirection, norm));
        float specPower = 30.0;
        vec3 specMaterial = vec3(1.0, 1.0, 0.75);

        vec3 specColor = lightColor * specMaterial * pow(max(dot(toEye, reflectLight), 0.0), specPower);
        
        color = ambient + diffuse + specColor;*/




//ro 	ray origin 
//rd 	ray direction
//col 	color
//s 	center sphere
//r 	radius
//t		variable
//p		ro + rd * t




// uint32_t shading_sp(uint32_t color, t_Ray_hit hit)
// {

// 	return color;
// }