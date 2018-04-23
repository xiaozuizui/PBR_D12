#pragma once

#include "core.h"
#include "sphere.h"
#include "ImageFile.h"
#include "Primitive.h"
#include "scene.h"

inline bool Intersect(const Ray &r, float &t, int &id);

std::default_random_engine generator;
std::uniform_real_distribution<float> distr(0.0f, 1.0f);
inline float erand48(unsigned short X)
{
	return distr(generator);
}


class TestSphere
{
public:
	
	float rad;//radius
	XMFLOAT3 position, emission, color;
	Refl_t refl;
public:
	TestSphere(float r, XMFLOAT3 p, XMFLOAT3 e, XMFLOAT3 c,Refl_t re) :rad(r), position(p), emission(e), color(c),refl(re)
	{
	}

	float Intersect(const Ray &r) const 
	{ // returns distance, 0 if nohit 
		XMFLOAT3 op(position.x - r.origin.x, position.y - r.origin.y, position.z - r.origin.z);
			// Solve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0 

		float t, eps = 1e-4, b;
			 XMStoreFloat( &b,XMVector3Dot(XMLoadFloat3(&op), XMLoadFloat3(&r.direction)));
			//op.dot(r.d), 
				float det = b * b - (op.x*op.x+op.y*op.y+op.z*op.z) + rad * rad;
		if (det<0) return 0; else det = sqrt(det);
		return (t = b - det)>eps ? t : ((t = b + det)>eps ? t : 0);
	}
};

TestSphere TestSpheres[] = {//Scene: radius, position, emission, color, material 
	TestSphere(1e5f, XMFLOAT3(1e5f + 1,40.8f,81.6f), XMFLOAT3(0,0,0),XMFLOAT3(.75f,.25f,.25f),DIFF),//Left 
	TestSphere(1e5f, XMFLOAT3(-1e5 + 99,40.8,81.6),XMFLOAT3(0,0,0),XMFLOAT3(.25,.25,.75),DIFF),//Rght 
	TestSphere(1e5f, XMFLOAT3(50,40.8, 1e5),     XMFLOAT3(0,0,0),XMFLOAT3(.75,.75,.75),DIFF),//Back 
	TestSphere(1e5f, XMFLOAT3(50,40.8,-1e5 + 170), XMFLOAT3(0,0,0),XMFLOAT3(),           DIFF),//Frnt 
	TestSphere(1e5f, XMFLOAT3(50, 1e5, 81.6),    XMFLOAT3(0,0,0),XMFLOAT3(.75,.75,.75),DIFF),//Botm 
	TestSphere(1e5f, XMFLOAT3(50,-1e5 + 81.6,81.6),XMFLOAT3(0,0,0),XMFLOAT3(.75,.75,.75),DIFF),//Top 
	//TestSphere(16.5f,XMFLOAT3(27,16.5,47),       XMFLOAT3(),XMFLOAT3(1,1,1), SPEC),//Mirr 
	//TestSphere(16.5f,XMFLOAT3(73,16.5,78),       XMFLOAT3(),XMFLOAT3(1,1,1), REFR),//Glas 
	TestSphere(600, XMFLOAT3(50,681.6 - .27,81.6),XMFLOAT3(12,12,12),  XMFLOAT3(), DIFF) //Lite 
};



XMVECTOR radiance(const Ray &r, int depth, unsigned short *Xi) {
	float t;                               // distance to intersection 
	int id = 0;                               // id of intersected object 
	if (!Intersect(r, t, id)) 
		return XMVectorZero(); // if miss, return black 

	const TestSphere &obj = TestSpheres[id];        // the hit object 

	//XMFLOAT3 x;
	XMVECTOR x = XMLoadFloat3(&r.origin) + t * XMLoadFloat3(&r.direction);//交点x
	XMVECTOR n = (x - XMVector3Normalize(XMLoadFloat3(&obj.position))); //法向量

	float temp;
	XMStoreFloat(&temp, XMVector3Dot(n, XMLoadFloat3(&r.direction)));

	n = temp < 0 ? n : n * -1;//反转法线,指向外侧

	XMFLOAT3 f = obj.color;
	
	
	double p = f.x>f.y && f.x>f.z ? f.x : f.y>f.z ? f.y : f.z; // max refl 

	if (++depth>5)
		if (erand48(*Xi)<p) 
			f = XMFLOAT3(f.x * (1 / p),f.y*(1/p),f.z*(1/p)); //归一化
		else
			return XMLoadFloat3(& obj.emission); //R.R. 达到最大深度



	if (obj.refl == DIFF) {                  // Ideal DIFFUSE reflection 
		float r1 = 2 * M_PI*erand48(*Xi), r2 = erand48(*Xi), r2s = sqrt(r2); //

		XMVECTOR w = n;

		XMFLOAT3 wtemp;
		XMStoreFloat3(&wtemp, w);
		
		XMVECTOR u = XMVector3Normalize(XMVector3Cross(XMLoadFloat3( &(fabs(wtemp.x) > .1 ? XMFLOAT3(0, 1, 0) : XMFLOAT3(1, 0, 0))), w));
	//	XMVECTOR u = ( ) % w).norm(); //以法向量为w建立坐标系
		XMVECTOR v = XMVector3Cross(w , u);

		//XMFLOAT3 d = (u*cos(r1)*r2s + v * sin(r1)*r2s + w * sqrt(1 - r2)).norm();//没看懂
		XMVECTOR d = XMVector3Normalize( u * cos(r1)*r2s + v * sin(r1)*r2s + w * sqrt(1 - r2) );

		XMFLOAT3 next_hit;
		XMStoreFloat3(&next_hit, x);
		XMFLOAT3 next_direction;
		XMStoreFloat3(&next_direction, d);

		XMVECTOR re;
		
		return XMLoadFloat3(&obj.emission) + XMVectorMultiply(XMLoadFloat3(&f), radiance(Ray(next_hit, next_direction), depth, Xi)); //递归光线追踪
	}

	//else if (obj.refl == SPEC)            // Ideal SPECULAR reflection 
	//	return obj.e + f.mult(radiance(Ray(x, r.d - n * 2 * n.dot(r.d)), depth, Xi));


	//Ray reflRay(x, r.d - n * 2 * n.dot(r.d));     // Ideal dielectric REFRACTION 
	//bool into = n.dot(nl)>0;                // Ray from outside going in? 
	//double nc = 1, nt = 1.5, nnt = into ? nc / nt : nt / nc, ddn = r.d.dot(nl), cos2t;

	//if ((cos2t = 1 - nnt * nnt*(1 - ddn * ddn))<0)    // Total internal reflection 
	//	return obj.e + f.mult(radiance(reflRay, depth, Xi));

	//XMFLOAT3 tdir = (r.d*nnt - n * ((into ? 1 : -1)*(ddn*nnt + sqrt(cos2t)))).norm();
	//double a = nt - nc, b = nt + nc, R0 = a * a / (b*b), c = 1 - (into ? -ddn : tdir.dot(n));
	//double Re = R0 + (1 - R0)*c*c*c*c*c, Tr = 1 - Re, P = .25 + .5*Re, RP = Re / P, TP = Tr / (1 - P);
	//return obj.e + f.mult(depth>2 ? (erand48(Xi)<P ?   // Russian roulette 
	//	radiance(reflRay, depth, Xi)*RP : radiance(Ray(x, tdir), depth, Xi)*TP) :
	//	radiance(reflRay, depth, Xi)*Re + radiance(Ray(x, tdir), depth, Xi)*Tr);
}

inline void Test()
{
	int w = 512, h = 512, samps = 2; //  samples

	XMFLOAT3 d(0, -0.042612, -1);
	XMStoreFloat3(&d, XMVector3Normalize(XMLoadFloat3(&d)));
	Ray cam(XMFLOAT3(50, 52, 295.6), d); // cam pos, dir 

	//Vec cx = Vec(w*.5135 / h), cy = (cx%cam.d).norm()*.5135, r, *c = new Vec[w*h];
	XMVECTOR cx = XMVectorSet(w*.5135 / h, 0, 0, 0);
	XMVECTOR cy = XMVector3Normalize(XMVector3Cross(cx, XMLoadFloat3(&cam.direction)))*.5135;

	XMVECTOR *image = new XMVECTOR[w*h];
	XMFLOAT3 position;
	//#pragma omp parallel for schedule(dynamic, 1) private(r)     // OpenMP 

	for (int y = 0; y < h; y++) {                       // Loop over image rows 
		fprintf(stderr, "\rRendering (%d spp) %5.2f%%", samps * 4, 100.*y / (h - 1));

		for (unsigned short x = 0, Xi[3] = { 0,0,y*y*y }; x < w; x++)   // Loop cols 

			for (int sy = 0, i = (h - y - 1)*w + x; sy < 2; sy++)
			{
				image[i] = XMVectorZero();
				// 2x2 subpixel rows 
				for (int sx = 0; sx < 2; sx++)
				{        // 2x2 subpixel cols 
					XMVECTOR  r = XMVectorZero();

					for (int s = 0; s < samps; s++)  //loop sample
					{
						float r1 = 2 * erand48(*Xi), dx = r1 < 1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
						float r2 = 2 * erand48(*Xi), dy = r2 < 1 ? sqrt(r2) - 1 : 1 - sqrt(2 - r2);
						rand();
						XMVECTOR d = cx * (((sx + .5 + dx) / 2 + x) / w - .5) +
							cy * (((sy + .5 + dy) / 2 + y) / h - .5) + XMLoadFloat3(&cam.direction);

						XMVECTOR R0 = XMLoadFloat3(&cam.origin) + d * 140;
						XMVECTOR D0 = XMVector3Normalize(d);

						XMFLOAT3 r0;
						XMFLOAT3 d0;

						XMStoreFloat3(&r0, R0);
						XMStoreFloat3(&d0, D0);
						r = r + radiance(Ray(r0, d0), 0, Xi)*(1. / samps);
					} // Camera rays are pushed ^^^^^ forward to start in interior 
					XMFLOAT3 r_;
					XMStoreFloat3(&r_, r);

					image[i] = image[i] + XMVectorSet(clamp(r_.x), clamp(r_.y), clamp(r_.z), 0)*.25;
				}
			}
			
	}
	FILE *f = fopen("image.ppm", "w");         // Write image to PPM file. 
	fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
	for (int i = 0; i < w*h; i++)
	{
		XMFLOAT3 temp;
		XMStoreFloat3(&temp, image[i]);
		fprintf(f, "%d %d %d ", toInt(temp.x), toInt(temp.y), toInt(temp.z));
	}
}

void TestN()
{
	XMFLOAT4X4 obj2world(1, 0, 0, -27, 0, 1, 0, 16.5, 0, 0, 1, 47, 0, 0, 0, 1);

	Sphere s(obj2world, obj2world, 16.5);
	Primitive p(&s);
	Scene sc(1, &p);


	int width = 512, height = 512;

	ImageFile::Initial(width, height);

	XMFLOAT3 d(0, -0.042612, -1);
	XMStoreFloat3(&d, XMVector3Normalize(XMLoadFloat3(&d)));
	Ray cam(XMFLOAT3(50, 52, 295.6), d); // cam pos, dir 
	XMVECTOR cx = XMVectorSet(width*.5135 / height, 0, 0, 0);
	XMVECTOR cy = XMVector3Normalize(XMVector3Cross(cx, XMLoadFloat3(&cam.direction)))*.5135;

	for (int x = 0; x < width; x++)
	{
		unsigned int Xi[3] = { 0,0,x*x*x };
		for (int y = 0; y < height; y++)
		{
			float r1 = 2 * erand48(*Xi), dx = r1 < 1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
			float r2 = 2 * erand48(*Xi), dy = r2 < 1 ? sqrt(r2) - 1 : 1 - sqrt(2 - r2);
			rand();
			XMVECTOR d = cx * (((x + .5 + dx) / 2 + x) / width - .5) +
				cy * (((y + .5 + dy) / 2 + y) / height - .5) + XMLoadFloat3(&cam.direction);

			XMVECTOR R0 = XMLoadFloat3(&cam.origin) + d * 140;
			XMVECTOR D0 = XMVector3Normalize(d);

			XMFLOAT3 r0;
			XMFLOAT3 d0;
			Intersection p;
			XMStoreFloat3(&r0, R0);
			XMStoreFloat3(&d0, D0);
			sc.Intersect(Ray(r0, d0), &p);
			ImageFile::SavePi(RGB_COLOR(255, 255, 255), x*width + y);
		}
	}
	ImageFile::SaveFile();
}

inline bool Intersect(const Ray &r, float &t, int &id) {
	double n = sizeof(TestSpheres) / sizeof(TestSphere), d, inf = t = 1e20;
	for (int i = int(n); i--;) if ((d = TestSpheres[i].Intersect(r)) && d<t) { t = d; id = i; }
	return t<inf;
}