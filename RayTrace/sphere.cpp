#include "sphere.h"

bool Sphere::Intersection(Ray ray)
{
	//光线方程带入球方程解出t  At^2+Bt+C = 0

	
	float A = ray.direction.x*ray.direction.x + ray.direction.y*ray.direction.y + ray.direction.z*ray.direction.z;
	float B = 2 * (ray.direction.x*ray.origin.x + ray.direction.y*ray.origin.y + ray.direction.z*ray.origin.z);
	float C = ray.origin.x*ray.origin.x + ray.origin.y*ray.origin.y +
		ray.origin.z*ray.origin.z - radius * radius;
	float t0, t1;
	if (!Quadratic(A, B, C, &t0, &t1))
		return false; //无交点

	Point hit;
	float phit;

	if (t0 > ray.maxt || t1 < ray.mint)
		return false;
	float thit = t0;
	if (t0 < ray.mint) {
		thit = t1;
		if (thit > ray.maxt) return false;
	}

	hit = ray.GetPoint(thit);

	if (hit.x == 0.f && hit.y == 0.f) hit.x = 1e-5f * radius;
	phit = atan2f(phit.y, phit.x);
	if (phi < 0.) phi += 2.f*M_PI;


	return false;
}