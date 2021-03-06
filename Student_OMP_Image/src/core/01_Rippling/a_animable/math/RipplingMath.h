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

class RipplingMath
    {
	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	RipplingMath(uint w)
	    {
	    this->dim2 = (float) w / 2.f;
	    }

	// constructeur copie: pas besoin car pas attribut ptr

	virtual ~RipplingMath(void)
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	void colorIJ(uchar4* ptrColorIJ, float i, float j, float t)
	    {
	    uchar levelGris;

	    f(j, i, t, &levelGris);

	    ptrColorIJ->x = levelGris;
	    ptrColorIJ->y = levelGris;
	    ptrColorIJ->z = levelGris;

	    ptrColorIJ->w = 255; //opaque
	    }

    private:

	void f(float i, float j, float t, uchar* ptrlevelGris)
	    {
	    float d;
	    dij(i, j, &d);
	    *ptrlevelGris = 128.f + 127.f * cosf((d / 10.f) - t / 7.f) / ((d / 10.f) + 1.f);

	    }

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
