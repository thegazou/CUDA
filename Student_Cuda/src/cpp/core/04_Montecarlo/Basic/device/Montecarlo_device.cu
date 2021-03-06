#include "Indice2D.h"
#include "Indice1D.h"
#include "cudaTools.h"
#include <curand_kernel.h>

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

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/
__device__ void reductionIntraThread(int* tabSM, curandState* ptrDevGeneratorGM, int nbFlecheByThread);
/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void montecarlo(curandState* ptrDevGeneratorGM, int* ptrDevNxTotalGM, int nbFlecheByThread)
    {
    extern __shared__ int tabSM[];
    reductionIntraThread(tabSM, ptrDevGeneratorGM, nbFlecheByThread);
    __syncthreads();
    reductionADD<int>(tabSM, ptrDevNxTotalGM);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ void reductionIntraThread(int* tabSM, curandState* ptrDevGeneratorGM, int nbFlecheByThread)
    {

    const int TID = Indice1D::tid();
    const int TID_LOCAL = Indice1D::tidLocalBlock();
    curandState localGenerator = ptrDevGeneratorGM[TID];
    int nx = 0;
    float xAlea, yAlea;
    for (int i = 1; i <= nbFlecheByThread; i++)
	{
	xAlea = curand_uniform(&localGenerator);
	yAlea = curand_uniform(&localGenerator);
	nx += (int) (1.f / (1.f + xAlea * xAlea) >= yAlea);
	}
    ptrDevGeneratorGM[TID] = localGenerator;
    tabSM[TID_LOCAL] = nx;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

