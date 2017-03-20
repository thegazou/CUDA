#pragma once

#include <math.h>
#include "MathTools.h"

#include "Calibreur_CPU.h"
#include "ColorTools_CPU.h"
using namespace cpu;

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	MandelbrotMath(float t) :
		calibreur(Interval<float>(0.f, t), Interval<float>(0.f, 1.f))
	    {
	    this->t = t;
	    }

	virtual ~MandelbrotMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	void colorXY(uchar4* ptrColor, float x, float y)
	    {
	    ptrColor->x = 0;
	    ptrColor->y = 0;
	    ptrColor->z = 0;
	    ptrColor->w = 255;
	    float a = 0.f;
	    float b = 0.f;
	    float aCopy, k;
	    for (k = 0.f; k <= t; k++) //check k appartient à [0,N]
		{
		aCopy = a;
		a = (a * a - b * b) + x;
		b = 2.f * aCopy * b + y;
		if ((a * a + b * b) > 4.f)
		    {
		    calibreur.calibrer(k);
		    ColorTools::HSB_TO_RVB(k, ptrColor);
		    break;
		    }
		}
	    //Si le point ne converge pas => noir
	    }

    private:

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Input
	float t;

	// Tools
	Calibreur<float> calibreur;
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
