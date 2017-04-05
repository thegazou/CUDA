#pragma once

#include "cudaTools.h"
#include "Grid.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Slice
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	Slice(const Grid& grid, const uint nbSlice);

	virtual ~Slice(void);

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
	const uint nbSlice;

	// Outputs
	float result;

	// Tools
	float* ptrDevGMResult;
	const size_t sizeOctetSM;
	const size_t sizeOctetGM;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
