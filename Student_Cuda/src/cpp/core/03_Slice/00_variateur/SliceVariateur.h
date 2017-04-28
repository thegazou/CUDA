#pragma once

#include "cudaTools.h"
#include "Grid.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class SliceVariateur
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	SliceVariateur(const uint nbThreadMin, const uint nbThreadMax, const uint threadIncrement, const uint nbSliceMin, const uint nbSliceMax,
		const uint sliceIncrement);

	virtual ~SliceVariateur(void);

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	bool run();

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	uint nbSliceMin;
	uint nbSliceMax;
	uint nbThreadMin;
	uint nbThreadMax;
	uint threadIncrement;
	uint sliceIncrement;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
