#pragma once
#include <math.h>
#include "MathTools.h"
#include "ColorTools_CPU.h"
#include <assert.h>
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

	RaytracingMath(Sphere* ptrTabSphere, uint nbSphere)
	    {
	    this->ptrTabSphere = ptrTabSphere;
	    this->nbSphere = nbSphere;
	    }

	// constructeur copie automatique car pas pointeur dans VagueMath

	virtual ~RaytracingMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	void colorIJ(uchar4* ptrColor, float i, float j, float t, float h, float w)
	    {
//	    assert(i>=0 && i<h);
//	    assert(j>=0 && j<w);
	    float hCarre, dz, minDz, distance;
	    int minIndex = -1;
	    float minDistance = 3.4028235E38f;
	    for (uint index = 0; index < nbSphere; index++)
		{
		Sphere s = ptrTabSphere[index];
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
		Sphere s = ptrTabSphere[minIndex];
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
	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

// Inputs
	Sphere* ptrTabSphere;
	uint nbSphere;
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
