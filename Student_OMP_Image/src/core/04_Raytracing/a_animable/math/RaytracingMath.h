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

	void colorIJ(uchar4* ptrColor, float i, float j, float t)
	    {
	    ptrColor->x = 0;
	    ptrColor->y = 0;
	    ptrColor->z = 0;
	    ptrColor->w = 255;
	    float hCarre;
	    for (uint index = 0; index < nbSphere; index++)
		{
		hCarre = ptrTabSphere[index].hCarre(i, j);
		if (ptrTabSphere[index].isEnDessous(hCarre))
		    {
		    ColorTools::HSB_TO_RVB(ptrTabSphere[index].hue(t), 1.f, ptrTabSphere[index].brightness(ptrTabSphere[index].dz(hCarre)), ptrColor);
		    break;
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
	Sphere* ptrTabSphere;
	uint nbSphere;
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
