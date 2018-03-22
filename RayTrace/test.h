#pragma once

#include "core.h"





inline bool Intersect(const Ray &r, float &t, int &id) {
	double n = sizeof(TestSpheres) / sizeof(TestSphere), d, inf = t = 1e20;
	for (int i = int(n); i--;) if ((d = TestSpheres[i].Intersect(r)) && d<t) { t = d; id = i; }
	return t<inf;
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
	TestSphere(1e5f, XMFLOAT3(1e5f + 1,40.8f,81.6f), XMFLOAT3(),XMFLOAT3(.75f,.25f,.25f),DIFF),//Left 
	TestSphere(1e5f, XMFLOAT3(-1e5 + 99,40.8,81.6),XMFLOAT3(),XMFLOAT3(.25,.25,.75),DIFF),//Rght 
	TestSphere(1e5f, XMFLOAT3(50,40.8, 1e5),     XMFLOAT3(),XMFLOAT3(.75,.75,.75),DIFF),//Back 
	TestSphere(1e5f, XMFLOAT3(50,40.8,-1e5 + 170), XMFLOAT3(),XMFLOAT3(),           DIFF),//Frnt 
	TestSphere(1e5f, XMFLOAT3(50, 1e5, 81.6),    XMFLOAT3(),XMFLOAT3(.75,.75,.75),DIFF),//Botm 
	TestSphere(1e5f, XMFLOAT3(50,-1e5 + 81.6,81.6),XMFLOAT3(),XMFLOAT3(.75,.75,.75),DIFF),//Top 
	TestSphere(16.5f,XMFLOAT3(27,16.5,47),       XMFLOAT3(),XMFLOAT3(1,1,1), SPEC),//Mirr 
	TestSphere(16.5f,XMFLOAT3(73,16.5,78),       XMFLOAT3(),XMFLOAT3(1,1,1), REFR),//Glas 
	TestSphere(600, XMFLOAT3(50,681.6 - .27,81.6),XMFLOAT3(12,12,12),  XMFLOAT3(), DIFF) //Lite 
};



XMFLOAT3 radiance(const Ray &r, int depth, unsigned short *Xi) {
	float t;                               // distance to intersection 
	int id = 0;                               // id of intersected object 
	if (!Intersect(r, t, id)) 
		return XMFLOAT3(); // if miss, return black 

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
			f = XMFLOAT3(f.x * (1 / p),f.y*(1/p),f.z*(1/p)); 
		else
			return obj.emission; //R.R. 



	if (obj.refl == DIFF) {                  // Ideal DIFFUSE reflection 
		float r1 = 2 * M_PI*erand48(*Xi), r2 = erand48(*Xi), r2s = sqrt(r2);
		XMVECTOR w = n, u = ((fabs(w.x)>.1 ? XMFLOAT3(0, 1) : XMFLOAT3(1)) % w).norm(), v = w % u;
		XMFLOAT3 d = (u*cos(r1)*r2s + v * sin(r1)*r2s + w * sqrt(1 - r2)).norm();


		return obj.emission+ f.mult(radiance(Ray(x, d), depth, Xi));
	}

	else if (obj.refl == SPEC)            // Ideal SPECULAR reflection 
		return obj.e + f.mult(radiance(Ray(x, r.d - n * 2 * n.dot(r.d)), depth, Xi));


	Ray reflRay(x, r.d - n * 2 * n.dot(r.d));     // Ideal dielectric REFRACTION 
	bool into = n.dot(nl)>0;                // Ray from outside going in? 
	double nc = 1, nt = 1.5, nnt = into ? nc / nt : nt / nc, ddn = r.d.dot(nl), cos2t;

	if ((cos2t = 1 - nnt * nnt*(1 - ddn * ddn))<0)    // Total internal reflection 
		return obj.e + f.mult(radiance(reflRay, depth, Xi));

	XMFLOAT3 tdir = (r.d*nnt - n * ((into ? 1 : -1)*(ddn*nnt + sqrt(cos2t)))).norm();
	double a = nt - nc, b = nt + nc, R0 = a * a / (b*b), c = 1 - (into ? -ddn : tdir.dot(n));
	double Re = R0 + (1 - R0)*c*c*c*c*c, Tr = 1 - Re, P = .25 + .5*Re, RP = Re / P, TP = Tr / (1 - P);
	return obj.e + f.mult(depth>2 ? (erand48(Xi)<P ?   // Russian roulette 
		radiance(reflRay, depth, Xi)*RP : radiance(Ray(x, tdir), depth, Xi)*TP) :
		radiance(reflRay, depth, Xi)*Re + radiance(Ray(x, tdir), depth, Xi)*Tr);
}

void Test()
{
	int w = 1024, h = 768, samps = 4; // # samples

	Ray cam(Vec(50, 52, 295.6), Vec(0, -0.042612, -1).norm()); // cam pos, dir 
	Vec cx = Vec(w*.5135 / h), cy = (cx%cam.d).norm()*.5135, r, *c = new Vec[w*h];

//#pragma omp parallel for schedule(dynamic, 1) private(r)     // OpenMP 

	for (int y = 0; y<h; y++) {                       // Loop over image rows 
		fprintf(stderr, "\rRendering (%d spp) %5.2f%%", samps * 4, 100.*y / (h - 1));

		for (unsigned short x = 0, Xi[3] = { 0,0,y*y*y }; x<w; x++)   // Loop cols 

			//for (int sy = 0, i = (h - y - 1)*w + x; sy<2; sy++)     // 2x2 subpixel rows 
			//	for (int sx = 0; sx<2; sx++, r = Vec()) {        // 2x2 subpixel cols 

					for (int s = 0; s<samps; s++)  //loop sample
					{
						float r1 = 2 * erand48(*Xi), dx = r1<1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
						float r2 = 2 * erand48(*Xi), dy = r2<1 ? sqrt(r2) - 1 : 1 - sqrt(2 - r2);

						Vec d = cx * (((sx + .5 + dx) / 2 + x) / w - .5) +
							cy * (((sy + .5 + dy) / 2 + y) / h - .5) + cam.d;
						r = r + radiance(Ray(cam.o + d * 140, d.norm()), 0, Xi)*(1. / samps);
					} // Camera rays are pushed ^^^^^ forward to start in interior 
					c[i] = c[i] + Vec(clamp(r.x), clamp(r.y), clamp(r.z))*.25;
				}
	}
	FILE *f = fopen("image.ppm", "w");         // Write image to PPM file. 
	fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
	for (int i = 0; i<w*h; i++)
		fprintf(f, "%d %d %d ", toInt(c[i].x), toInt(c[i].y), toInt(c[i].z));
}