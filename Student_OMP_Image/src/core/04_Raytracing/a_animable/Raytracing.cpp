#include "Raytracing.h"

#include <iostream>
#include <omp.h>
#include "OmpTools.h"

#include "IndiceTools_CPU.h"

#include "../a_animable/math/RaytracingMath.h"
#include "../a_animable/geometry/Sphere.h"
#include "../a_animable/geometry/SphereCreator.h"
using cpu::IndiceTools;

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

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

Raytracing::Raytracing(uint w, uint h, uint nbSphere, const DomaineMath& domaineMath) :
	Animable_I<uchar4>(w, h, "Raytracing_OMP_rgba_uchar4", domaineMath), variateurAnimation(Interval<float>(0.f, 1.f), 0.1)
    {
    // Input

    // Tools
    this->t = 0;					// protected dans super classe Animable
    this->parallelPatern = ParallelPatern::OMP_MIXTE;   // protected dans super classe Animable

    ShereCreator shereCreator(nbSphere, w, h); // sur la pile
    this->ptrTabSphere = shereCreator.getTab();

    toGM(ptrTabSphere);

    toCM(ptrTabSphere);
    }

// OMP
cout << "\n[Raytracing] : OMP : nbThread = " << this->nbThread << endl;// protected dans super classe Animable
}

Raytracing::~Raytracing(void)
{
// rien
}

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Override
 */
void Raytracing::animationStep()
{
this->t = variateurAnimation.varierAndGet(); // in [0,2pi]
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void Raytracing::toGM(Sphere* ptrTabSphere)
{
//TODO
}

void Raytracing::toCM(Sphere* ptrTabSphere)
{
//TODO
}

/**
 * Override (code naturel omp)
 */
void Raytracing::processForAutoOMP(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath)
{
RaytracingMath raytracingMath(t); // ici pour preparer cuda

#pragma omp parallel for
for (int i = 0; i < h; i++)
    {
    for (int j = 0; j < w; j++)
	{
	// int s = i * W + j;
	int s = IndiceTools::toS(w, i, j);    // i[0,H[ j[0,W[  --> s[0,W*H[

	workPixel(&ptrTabPixels[s], i, j, domaineMath, &raytracingMath);
	}
    }
}

/**
 * Override (code entrainement cuda)
 */
void Raytracing::processEntrelacementOMP(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath)
{
RaytracingMath raytracingMath(t); // ici pour preparer cuda

const int WH = w * h;

#pragma omp parallel
    {
    const int NB_THREAD = OmpTools::getNbThread(); // dans region parallel
    const int TID = OmpTools::getTid();

    int i;
    int j;

    int s = TID; // in [0,...
    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &i, &j); // s[0,W*H[ --> i[0,H[ j[0,W[

	workPixel(&ptrTabPixels[s], i, j, domaineMath, &raytracingMath);

	s += NB_THREAD;
	}
    }
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * i in [0,h[
 * j in [0,w[
 *
 * code commun a:
 * 	- entrelacementOMP
 * 	- forAutoOMP
 */
void Raytracing::workPixel(uchar4* ptrColorIJ, int i, int j, const DomaineMath& domaineMath, RaytracingMath* ptrRaytracingMath)
{
// (i,j) domaine ecran dans N2
// (x,y) domaine math dans R2

double x;
double y;
domaineMath.toXY(i, j, &x, &y); // fill (x,y) from (i,j)

// float t=variateurAnimation.get();

ptrRaytracingMath->colorXY(ptrColorIJ, x, y, ptrTabSphere, t); // in [01]
}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

