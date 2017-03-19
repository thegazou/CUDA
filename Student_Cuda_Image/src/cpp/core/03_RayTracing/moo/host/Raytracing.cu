#include "Sphere.h"
#include "Raytracing.h"
#include <iostream>
#include <assert.h>

#include "Device.h"
#include "SphereCreator.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void raytracing(uchar4* ptrDevPixels, uint w, uint h, float t, Sphere* ptrSphere, uint nbSphere);

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

Raytracing::Raytracing(const Grid& grid, uint w, uint h, float dt, uint nbSphere) :
	Animable_I<uchar4>(grid, w, h, "Raytracing_Cuda_RGBA_uchar4")
    {
    // Inputs
    this->dt = dt;
    this->nbSphere = nbSphere;

    // Tools
    this->t = 0; // protected dans Animable
    SphereCreator sphereCreator = SphereCreator(nbSphere, w, h);
    this->ptrDevTabSphere = sphereCreator.getTabSphere();

    //MemoryManagement
    this->sizeOctet = nbSphere * sizeof(Sphere);
    Device::malloc(&ptrDevTabSphere, sizeOctet);
    Device::memclear(ptrDevTabSphere, sizeOctet);
    Device::memcpyHToD(ptrDevTabSphere, ptrTabSphere, sizeOctet);
    //Device::lastCudaError("Raytracing MM (end allocation)");
    }

Raytracing::~Raytracing()
    {
    Device::free(ptrDevTabSphere);
    //Device::lastCudaError("Raytracing MM (end deallocation)");
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 * Call periodicly by the API
 *
 * Note : domaineMath pas use car pas zoomable
 */
void Raytracing::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    //Device::lastCudaError("Raytracing rgba uchar4 (before)"); // facultatif, for debug only, remove for release

    raytracing<<<dg,db>>>(ptrDevPixels,w,h,t, ptrDevTabSphere, nbSphere);

    //Device::lastCudaError("Raytracing rgba uchar4 (after)"); // facultatif, for debug only, remove for release
    }

/**
 * Override
 * Call periodicly by the API
 */
void Raytracing::animationStep()
    {
    t += dt;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/