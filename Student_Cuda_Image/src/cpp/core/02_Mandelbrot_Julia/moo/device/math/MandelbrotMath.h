#pragma once

#include <math.h>
#include "MathTools.h"

#include "Calibreur_GPU.h"
#include "ColorTools_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ MandelbrotMath(uint t) :
		calibreur(Interval<float>(0.f, t), Interval<float>(0.f, 1.f))
	    {
	    this->t = t;
	    }

	__device__
		     virtual ~MandelbrotMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorXY(uchar4* ptrColor, float x, float y, float t)
	    {
	    float z = f(x, y, t);
	    if (z != -1.f) //Vérifie la convergence
		{
		calibreur.calibrer(z);

		ColorTools::HSB_TO_RVB(z, ptrColor); // update color
		}
	    //Si le point ne converge pas => noir
	    else
		{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		ptrColor->w = 255;
		}
	    }

    private:

	__device__
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
	__device__
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
