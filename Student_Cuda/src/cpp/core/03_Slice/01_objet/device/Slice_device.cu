#include "Indice2D.h"
#include "Indice1D.h"
#include "cudaTools.h"

#include <stdio.h>
#include <reductionADD.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void slice(float* ptrDevGMResult, const uint nbSlice);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/
__device__ void reductionIntraThread(float* tabSM, const uint nbSlice);
/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * output : void required !!
 */
__global__ void slice(float* ptrDevGMResult, const uint nbSlice)
    {
    extern __shared__ float tabSM[]; //extern signifie que la taille est définit par le host.
    reductionIntraThread(tabSM, nbSlice);
    __syncthreads();
    reductionADD<float>(tabSM, ptrDevGMResult);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ void reductionIntraThread(float* tabSM, const uint nbSlice)
    {

    const int NB_THREAD = Indice1D::nbThread();
    const int TID = Indice1D::tid();
    const int TID_LOCAL = Indice1D::tidLocal();
    const float DX = 1.f / (float) nbSlice;
    float x;
    uint s = TID;
    float sumThread = 0.f;
    while (s < nbSlice)
	{
	x = (float) s * DX;
	sumThread += 1.f / (1.f + x * x);
	s += NB_THREAD;
	}
    tabSM[TID_LOCAL] = sumThread;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

