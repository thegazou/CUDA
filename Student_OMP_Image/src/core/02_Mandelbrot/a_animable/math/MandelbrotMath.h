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
		calibreur(Interval<float>(0.f, (float) t), Interval<float>(0.f, 1.f))
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

	void colorXY(uchar4* ptrColor, float x, float y, float t)
	    {
	    float z = f(x, y, t);
	    if (z != -1.f) //Vérifie la convergence
		{
		calibreur.calibrer(z);
		ColorTools::HSB_TO_RVB(z, ptrColor); // update color
		}
	    //Si le point ne converge pas => noir
	    }

    private:

	float f(float x, float y, float t)
	    {
	    float a = 0.f;
	    float b = 0.f;
	    float aCopy;
	    for (float k = 0; k <= t; k++) //check k appartient à [0,N]
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
	    return -1.f; //noir car convergent
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
	float t;

	// Tools
	Calibreur<float> calibreur;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
