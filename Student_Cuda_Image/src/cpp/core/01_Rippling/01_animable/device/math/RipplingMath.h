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

class RipplingMath
    {
	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:
	__device__ RipplingMath(uint w)
	    {
	    this->dim2 = (float) w / 2.f;
	    }

	// constructeur copie: pas besoin car pas attribut ptr
	__device__
	   virtual ~RipplingMath(void)
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:
	__device__
	void colorIJ(uchar4* ptrColorIJ, float i, float j, float t)
	    {
	    uchar levelGris;

	    f(i, j, t, &levelGris);

	    ptrColorIJ->x = levelGris;
	    ptrColorIJ->y = levelGris;
	    ptrColorIJ->z = levelGris;

	    ptrColorIJ->w = 255; //opaque
	    }

    private:
	__device__
	void f(float i, float j, float t, uchar* ptrlevelGris)
	    {
	    float d;
	    dij(i, j, &d);
	    *ptrlevelGris = 128.f + 127.f * cosf((d / 10.f) - t / 7.f) / ((d / 10.f) + 1.f);
	    }
	__device__
	void dij(float i, float j, float* ptrResult)
	    {
	    float iDim = i - dim2;
	    float jDim = j - dim2;
	    *ptrResult = sqrtf(iDim * iDim + jDim * jDim);
	    }
	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    private:

	// Tools
	float dim2;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
