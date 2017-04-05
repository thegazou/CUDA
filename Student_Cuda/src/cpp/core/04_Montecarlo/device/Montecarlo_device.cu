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

__global__ void montecarlo(curandState* ptrDevGeneratorGM, int* ptrDevNxTotalGM, int nbFlecheByThread);

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

/**
 * output : void required !!
 */
__global__ void montecarlo(curandState* ptrDevGeneratorGM, int* ptrDevNxTotalGM, int nbFlecheByThread)
    {
    extern __shared__ int tabSM[]; //extern signifie que la taille est définit par le host.
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
    // Global Memory -> Register (optimization)
    curandState localGenerator = ptrDevGeneratorGM[TID];
    int nx = 0;
    float xAlea;
    float yAlea;
    float result;
    for (int i = 1; i <= nbFlecheByThread; i++)
	{
	xAlea = curand_uniform(&localGenerator);
	yAlea = 4 * curand_uniform(&localGenerator);
	result = (1.f / (1.f + xAlea * xAlea));
	if (result >= yAlea)
	    {
	    nx++;
	    }
//	nx += (int) (4.f / (1.f + xAlea * xAlea) >= yAlea);
	}
//Register -> Global Memory
//Necessaire si on veut utiliser notre generator
// - dans dautre kernel
// - avec dautres nombres aleatoires !
    ptrDevGeneratorGM[TID] = localGenerator;
    tabSM[TID_LOCAL] = nx;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

