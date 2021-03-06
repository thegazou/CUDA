#include "Raytracing.h"
#include "SphereCreator.h"
#include "RaytracingMath.h"

#include <iostream>
#include <omp.h>
#include "OmpTools.h"

#include "IndiceTools_CPU.h"
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

Raytracing::Raytracing(uint w, uint h, float dt, uint nbSphere) :
	Animable_I<uchar4>(w, h, "Raytracing_OMP_RGBA_uchar4")
    {
    // Inputs
    this->dt = dt;
    this->nbSphere = nbSphere;

    // Tools
    this->t = 0; // protected dans Animable
    SphereCreator sphereCreator = SphereCreator(nbSphere, w, h);
    this->ptrTabSphere = sphereCreator.getTabSphere();

    this->parallelPatern = ParallelPatern::OMP_MIXTE; // protected dans super classe Animable

    // OMP
    cout << "\n[Raytracing] : OMP : nbThread = " << this->nbThread << endl; // protected dans super classe Animable
    }

Raytracing::~Raytracing(void)
    {
    delete[] ptrTabSphere;
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
    t += dt;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * Override (code naturel omp)
 * Image non zoomable : domaineMath pas use ici
 */
void Raytracing::processForAutoOMP(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    RaytracingMath raytracingMath = RaytracingMath(ptrTabSphere, nbSphere);

#pragma omp parallel for
    for (int i = 0; i < h; i++)
	{
	for (int j = 0; j < w; j++)
	    {
	    int s = IndiceTools::toS(w, i, j);    // i[0,H[ j[0,W[  --> s[0,W*H[

	    raytracingMath.colorIJ(&ptrTabPixels[s], i, j, t, h, w);
	    }
	}
    }

void Raytracing::processEntrelacementOMP(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    const int WH = w * h;
    RaytracingMath raytracingMath = RaytracingMath(ptrTabSphere, nbSphere);

#pragma omp parallel
	{
	const int TID = OmpTools::getTid();
	const int NB_THREAD = OmpTools::getNbThread(); // dans region parallel

	int i, j;
	int s = TID;
	while (s < WH)
	    {
	    IndiceTools::toIJ(s, w, &i, &j);

	    raytracingMath.colorIJ(&ptrTabPixels[s], i, j, t, h, w);

	    s += NB_THREAD;
	    }
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

