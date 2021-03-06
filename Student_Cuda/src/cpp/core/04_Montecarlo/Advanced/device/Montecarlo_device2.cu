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
__device__ void reductionIntraThread2(int* tabSM, curandState* ptrDevGeneratorGM, int nbFlecheByThread);
__device__ void throwFleche(float xAlea, float yAlea, int* nx);
/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void montecarlo2(curandState* ptrDevGeneratorGM, int* ptrDevNxTotalGM, int nbFlecheByThread)
    {
    extern __shared__ int tabSM[];
    reductionIntraThread2(tabSM, ptrDevGeneratorGM, nbFlecheByThread);
    __syncthreads();
    reductionADD<int>(tabSM, ptrDevNxTotalGM);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ void reductionIntraThread2(int* tabSM, curandState* ptrDevGeneratorGM, int nbFlecheByThread)
    {

    const int TID = Indice1D::tid();
    const int TID_LOCAL = Indice1D::tidLocalBlock();
    curandState localGenerator = ptrDevGeneratorGM[TID];
    int nx = 0;
    float xAlea;
    float yAlea;

    //Unroll loop is useless
    for (int i = 1; i <= nbFlecheByThread * 1024; i++)
	{
	xAlea = curand_uniform(&localGenerator);
	yAlea = curand_uniform(&localGenerator);
	throwFleche(xAlea, yAlea, &nx);
	}
    ptrDevGeneratorGM[TID] = localGenerator;
    tabSM[TID_LOCAL] = nx;
    }

__device__ void throwFleche(float xAlea, float yAlea, int* nx)
    {
    nx += (int) (1.f / (1.f + xAlea * xAlea) >= yAlea);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

