#ifndef SPHERE_H
#define SPHERE_H

#include <math.h>
#include "MathTools.h"
#include "cudaType_CPU.h"
#include <assert.h>
using namespace cpu;

class Sphere
    {
    public:
	Sphere(float3 centre, float rayon, float hue, int w, int h)
	    {
// Inputs
	    this->centre = centre;
//	    assert(centre.y>=0 && centre.y<h);
//	    assert(centre.x>=0 && centre.x<w);
	    this->r = rayon;
	    this->hueStart = hue;
// Tools
	    this->rCarre = rayon * rayon;
	    }
	/**
	 * required by example for new Sphere[n]
	 */
	Sphere()
	    {
	    this->centre = float3();
	    this->r = 0.f;
	    this->hueStart = 0.f;
	    // Tools
	    this->rCarre = 0.f;
	    }

	float3 getCentre()
	    {
	    return centre;
	    }
	float hCarre(float i, float j)
	    {
	    float a = (centre.y - i);
	    float b = (centre.x - j);
	    return a * a + b * b;
	    }
	bool isEnDessous(float hCarre)
	    {
	    return hCarre < rCarre;
	    }
	float dz(float hCarre)
	    {
	    return sqrtf(rCarre - hCarre);
	    }
	float brightness(float dz)
	    {
	    return dz / r;
	    }
	float distance(float dz)
	    {
	    return centre.z - dz;
	    }
	float getHueStart()
	    {
	    return hueStart;
	    }
	float hue(float t) // usefull for animation
	    {
	    return 0.5f + 0.5f * sinf(t + hueStart + 3.f * PI_FLOAT / 2.f);
	    }
    private:
// Inputs
	float r;
	float3 centre;
	float hueStart;
// Tools
	float rCarre;
    };
#endif
