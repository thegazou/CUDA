#pragma once
#include <math.h>
#include "MathTools.h"
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

	RaytracingMath(Sphere* ptrDevTabSphere, uint nbSphere)
	    {
	    this->ptrDevTabSphere = ptrDevTabSphere;
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
