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

extern __global__ void raytracingGM(uchar4* ptrDevPixels, uint w, uint h, float t, Sphere* ptrSphere, uint nbSphere);
extern __global__ void raytracingCM(uchar4* ptrDevPixels, uint w, uint h, float t);
extern __global__ void raytracingSM(uchar4* ptrDevPixels, uint w, uint h, float t, Sphere* ptrSphere, uint nbSphere);
extern __host__ void uploadGPU(Sphere* ptrTabSphere);

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
    Sphere* ptrTabSphere = sphereCreator.getTabSphere();
    this->sizeOctet = nbSphere * sizeof(Sphere);
    this->i = 0;

    //MemoryManagement
    Device::malloc(&ptrDevTabSphere, sizeOctet);
    Device::memclear(ptrDevTabSphere, sizeOctet);
    Device::memcpyHToD(ptrDevTabSphere, ptrTabSphere, sizeOctet);
    uploadGPU(ptrTabSphere);

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
    Device::lastCudaError("Raytracing rgba uchar4 (before)"); // facultatif, for debug only, remove for release

    i = 3;
//i++;
    if (i % 3 == 0)
	{
	raytracingGM<<<dg,db>>>(ptrDevPixels,w,h,t, ptrDevTabSphere, nbSphere);
	Device::lastCudaError("Raytracing rgba uchar4 (before)"); // facultatif, for debug only, remove for release
	}
    else if (i % 3 == 1)
	{
	raytracingCM<<<dg,db>>>(ptrDevPixels,w,h,t);
	Device::lastCudaError("Raytracing rgba uchar4 (before)"); // facultatif, for debug only, remove for release
	}
    else if (i % 3 == 2)
	{
	raytracingSM<<<dg,db, sizeOctet>>>(ptrDevPixels,w,h,t,ptrDevTabSphere,nbSphere);
	Device::lastCudaError("Raytracing rgba uchar4 (before)"); // facultatif, for debug only, remove for release
	}

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
