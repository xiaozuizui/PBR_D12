#include "sphere.h"

bool Sphere::Intersection(Ray ray)
{
	//����ֱ�߷��̣�����ԭ����ֱ�ߵľ��룬��뾶�Ƚ�


	float A = ray.direction.x*ray.direction.x + ray.direction.y*ray.direction.y + ray.direction.z*ray.direction.z;
	float B = 2 * (ray.direction.x*ray.origin.x + ray.direction.y*ray.origin.y + ray.direction.z*ray.origin.z);
	float C = ray.origin.x*ray.origin.x + ray.origin.y*ray.origin.y +
		ray.origin.z*ray.origin.z - radius * radius;




	return false;
}