#pragma once

#include <math.h>
#include "MathTools.h"

#include "Calibreur_CPU.h"
#include "ColorTools_CPU.h"
using namespace cpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RaytracingMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	RaytracingMath(uint t) :
		calibreur(Interval<float>(0.f, t), Interval<float>(0.f, 1.f))
	    {
	    this->t = t;
	    }


	virtual ~RaytracingMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	void colorXY(uchar4* ptrColor, float x, float y, int t)
	    {
	    //calibreur.calibrer(dz);
	     float3 hsb;
	     hsb.x=0.5; //jaune
	     hsb.y=1.f;
	     hsb.z=1.f;

	    ColorTools::HSB_TO_RVB(hsb, ptrColor); // update color

	    ptrColor->w = 255; // opaque
	    }

    private:

	//Calcule la distance au centre de la sphère
	float dz(float r, float h)
	    {

	    return sqrtf(r*r - h*h);
	    }

	//Calcule le point de la shère le plus proche du sol
	float2 I(float2 c, float r, float h)
	    {
	    float dz=1;
	    float2 result;
	    result.x=c.x-dz;
	    result.y=c.y-dz;
	    return result;
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Input
	uint t;

	// Tools
	Calibreur<float> calibreur;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
