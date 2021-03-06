#pragma once
#include <math.h>
#include "MathTools.h"
#include "ColorTools_GPU.h"
using namespace gpu;

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

	__device__ RaytracingMath(Sphere* ptrDevTabSphere, uint nbSphere)
	    {
	    this->ptrDevTabSphere = ptrDevTabSphere;
	    this->nbSphere = nbSphere;
	    }

	// constructeur copie automatique car pas pointeur dans VagueMath

	__device__           virtual ~RaytracingMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorIJ(uchar4* ptrColor, float i, float j, float t)
	    {
	    float hCarre, dz, minDz, distance;
	    int minIndex = -1;
	    float minDistance = 3.4028235E38f;
	    for (uint index = 0; index < nbSphere; index++)
		{
		Sphere s = ptrDevTabSphere[index];
		hCarre = s.hCarre(i, j);
		if (s.isEnDessous(hCarre))
		    {
		    dz = s.dz(hCarre);
		    distance = s.distance(dz);
		    if (distance < minDistance)
			{
			minDistance = distance;
			minDz = dz;
			minIndex = index;
			}
		    }
		}
	    if (minIndex != -1)
		{
		Sphere s = ptrDevTabSphere[minIndex];
		ColorTools::HSB_TO_RVB(s.hue(t), 1.f, s.brightness(minDz), ptrColor);
		}
	    else // Si le point n'est pas sous une sphere => noir
		{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		ptrColor->w = 255;
		}
	    }

    private:

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

// Inputs
	Sphere* ptrDevTabSphere;
	uint nbSphere;
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
