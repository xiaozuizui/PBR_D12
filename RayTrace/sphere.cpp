#include "sphere.h"

bool Sphere::Intersection(Ray ray)
{
	//计算直线方程，计算原点与直线的距离，与半径比较


	float A = ray.direction.x*ray.direction.x + ray.direction.y*ray.direction.y + ray.direction.z*ray.direction.z;
	float B = 2 * (ray.direction.x*ray.origin.x + ray.direction.y*ray.origin.y + ray.direction.z*ray.origin.z);
	float C = ray.origin.x*ray.origin.x + ray.origin.y*ray.origin.y +
		ray.origin.z*ray.origin.z - radius * radius;




	return false;
}