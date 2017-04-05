#pragma once

#include "cudaTools.h"
#include "Grid.h"
#include <curand_kernel.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Montecarlo
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	Montecarlo(const Grid& grid, const int nbFlecheTotal);

	virtual ~Montecarlo(void);

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	void run();
	float getResult();

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	const dim3 dg;
	const dim3 db;
	int nbFlecheTotal;

	// Outputs
	float result;

	// Tools
	int nbFlecheParThread;
	int* ptrDevGMResult;
	curandState* ptrDevGMTabGenerator;
	size_t sizeOctetSM;
	size_t sizeOctetResultGM;
	size_t sizeOctetTabGenerator;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
