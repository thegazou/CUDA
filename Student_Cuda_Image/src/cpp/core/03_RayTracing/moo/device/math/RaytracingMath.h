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

	__device__
	         virtual ~RaytracingMath()
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
	    float hCarre;
	    Sphere s = ptrDevTabSphere[0];
	    for (uint index = 0; index < nbSphere; index++)
		{
		s = ptrDevTabSphere[index];
		hCarre = s.hCarre(i, j);
		if (s.isEnDessous(hCarre))
		    {
		    ColorTools::HSB_TO_RVB(s.hue(t), 1.f, s.brightness(s.dz(hCarre)), ptrColor);
		    }
		}
	    //Si le point n'est pas sous une sphere => noir
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
