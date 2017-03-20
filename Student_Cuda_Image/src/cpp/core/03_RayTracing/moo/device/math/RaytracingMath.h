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
	    //Version joli mais plus lente
//	    if (!isEndessous(ptrColor, i, j, t))
//		{
//		ptrColor->x = 0;
//		ptrColor->y = 0;
//		ptrColor->z = 0;
//		ptrColor->w = 255;
//		}
	    //14 registres
	    ptrColor->x = 0;
	    ptrColor->y = 0;
	    ptrColor->z = 0;
	    ptrColor->w = 255;
	    float hCarre;
	    for (uint index = 0; index < nbSphere; index++)
		{
		hCarre = ptrDevTabSphere[index].hCarre(i, j);
		if (ptrDevTabSphere[index].isEnDessous(hCarre))
		    {
		    ColorTools::HSB_TO_RVB(ptrDevTabSphere[index].hue(t), 1.f, ptrDevTabSphere[index].brightness(ptrDevTabSphere[index].dz(hCarre)), ptrColor);
		    break;
		    }
		}
	    //Si le point n'est pas sous une sphere => noir
	    }

    private:
// 16 registres, 170fps
	__device__
	bool isEndessous(uchar4* ptrColor, float i, float j, float t)
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
		    return true;
		    }
		}
	    return false;
	    }
// 17 registres, 270fps
	__device__
	bool isEndessous_sans_objet_sphere(uchar4* ptrColor, float i, float j, float t)
	    {
	    float hCarre;
//		    Sphere s = ptrDevTabSphere[0];
	    for (uint index = 0; index < nbSphere; index++)
		{
//			s = ptrDevTabSphere[index];
		hCarre = ptrDevTabSphere[index].hCarre(i, j);
		if (ptrDevTabSphere[index].isEnDessous(hCarre))
		    {
		    ColorTools::HSB_TO_RVB(ptrDevTabSphere[index].hue(t), 1.f, ptrDevTabSphere[index].brightness(ptrDevTabSphere[index].dz(hCarre)), ptrColor);
		    return true;
		    }
		}
	    return false;
	    }
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
