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

	MandelbrotMath(uint t) :
		calibreur(Interval<float>(0, t), Interval<float>(0.f, 1.f))
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

	void colorXY(uchar4* ptrColor, float x, float y, int t)
	    {
	    float z = f(x, y, t);
	    if (z != -1) //Vérifie la convergence
		{
		calibreur.calibrer(z);
		float hue01 = z;

		ColorTools::HSB_TO_RVB(hue01, ptrColor); // update color

		}
	    else
		{
		ptrColor->x = 0;//noir
		ptrColor->y = 0;
		ptrColor->z = 0;
		}
	    ptrColor->w = 255; // opaque
	    }

    private:

	float f(float x, float y, int t)
	    {
	    int k;
	    float a = 0;
	    float b = 0;
	    float aCopy;
	    for (k = 0; k <= t; k++) //check k appartient à [0,N]
		{
		aCopy = a;
		a = (a * a - b * b) + x;
		b = 2.f * aCopy * b + y;
		if (isDivergent(a, b) == true)
		    {
		    return k;
		    }
		k++;
		}
	    return -1; //noir car convergent
	    }

	bool isDivergent(float a, float b)
	    {
	    return (a * a + b * b) > 4.f;
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
