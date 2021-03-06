#include "Mandelbrot.h"

#include <iostream>
#include <omp.h>
#include "OmpTools.h"

#include "IndiceTools_CPU.h"

#include "../a_animable/math/MandelbrotMath.h"
using cpu::IndiceTools;

using std::cout;
using std::endl;

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

Mandelbrot::Mandelbrot(uint w, uint h, int tMin, int tMax, const DomaineMath& domaineMath) :
	Animable_I<uchar4>(w, h, "Mandelbrot_OMP_rgba_uchar4", domaineMath), variateurAnimation(Interval<float>(tMin, tMax), 1)
    {
    // Input

    // Tools
    this->t = 0;					// protected dans super classe Animable
    this->parallelPatern = ParallelPatern::OMP_MIXTE;   // protected dans super classe Animable

    // OMP
    cout << "\n[Mandelbrot] : OMP : nbThread = " << this->nbThread << endl; // protected dans super classe Animable
    }

Mandelbrot::~Mandelbrot(void)
    {
    // rien
    }

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Override
 */
void Mandelbrot::animationStep()
    {
    this->t = variateurAnimation.varierAndGet();
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void Mandelbrot::processForAutoOMP(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    MandelbrotMath mandelbrotMath(t);

#pragma omp parallel for
    for (int i = 0; i < h; i++)
	{
	int s;
	for (int j = 0; j < w; j++)
	    {
	    s = IndiceTools::toS(w, i, j);   //1D to 2D
	    workPixel(&ptrTabPixels[s], i, j, domaineMath, &mandelbrotMath);
	    }
	}
    }

void Mandelbrot::processEntrelacementOMP(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    MandelbrotMath mandelbrotMath((float) t);
    const int WH = w * h;

#pragma omp parallel
	{
	const int NB_THREAD = OmpTools::getNbThread(); // dans region parallel
	const int TID = OmpTools::getTid();

	int i, j;

	int s = TID;
	while (s < WH)
	    {
	    IndiceTools::toIJ(s, w, &i, &j); // 1D -> 2D

	    workPixel(&ptrTabPixels[s], i, j, domaineMath, &mandelbrotMath);

	    s += NB_THREAD;
	    }
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void Mandelbrot::workPixel(uchar4* ptrColorIJ, int i, int j, const DomaineMath& domaineMath, MandelbrotMath* ptrMandelbrotMath)
    {
    double x;
    double y;
    domaineMath.toXY(i, j, &x, &y); // écran -> math

    ptrMandelbrotMath->colorXY(ptrColorIJ, (float) x, (float) y);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

