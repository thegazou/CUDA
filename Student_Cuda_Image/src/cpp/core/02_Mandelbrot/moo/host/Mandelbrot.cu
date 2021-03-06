#include "Mandelbrot.h"

#include <iostream>
#include <assert.h>

#include "Device.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

__global__ void mandelbrot(uchar4* ptrDevPixels, uint w, uint h, DomaineMath domaineMath, float t);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

Mandelbrot::Mandelbrot(const Grid& grid, uint w, uint h, uint tMin, uint tMax, const DomaineMath& domaineMath) :
	Animable_I<uchar4>(grid, w, h, "Mandelbrot_Cuda_RGBA_uchar4", domaineMath), variateurAnimation(Interval<float>(tMin, tMax), 1)
    {
    // Inputs

    // Tools
    this->t = 0;  // protected dans Animable
    }

Mandelbrot::~Mandelbrot()
    {
    // rien
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

void Mandelbrot::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    //Device::lastCudaError("Mandelbrot rgba uchar4 (before)"); // facultatif, for debug only, remove for release

mandelbrot<<<dg,db>>>(ptrDevPixels, w, h, domaineMath, t);

//Device::lastCudaError("Mandelbrot rgba uchar4 (after)"); // facultatif, for debug only, remove for release
}

void Mandelbrot::animationStep()
{
this->t = variateurAnimation.varierAndGet();
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

