#include "SliceVariateur.h"

#include <iostream>

#include "Device.h"
#include "assert.h"
#include "Chrono.h"
#include "limits.h"
#include "MathTools.h"
#include "Slice.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur			*|
 \*-------------------------------------*/

SliceVariateur::SliceVariateur(const uint nbThreadMin, const uint nbThreadMax, const uint threadIncrement, const uint nbSliceMin, const uint nbSliceMax,
	const uint sliceIncrement) :
	nbThreadMin(nbThreadMin), nbThreadMax(nbThreadMax), nbSliceMin(nbSliceMin), nbSliceMax(nbSliceMax), threadIncrement(threadIncrement), sliceIncrement(
		sliceIncrement)
    {
    assert(nbThreadMin >= 0);
    assert(nbThreadMax <= 1024);
    assert(nbSliceMin >= 0);
    uint MAX = INT_MAX - 1;
    MAX *= 2;
    assert(nbSliceMax <= MAX);
    }

SliceVariateur::~SliceVariateur(void)
    {
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

bool SliceVariateur::run()
    {
    bool isOk = true;
    bool isOkLocal;
    float result;
    uint iteration = 1;
//    Chrono chrono = Chrono("Time:");
    dim3 dg = dim3(24, 1, 1);
    dim3 db = dim3(1024, 1, 1);
    Grid grid(dg, db);
    for (uint nbSlice = nbSliceMin; nbSlice <= nbSliceMax; nbSlice += sliceIncrement)
	{
	for (uint nbThread = nbThreadMin; nbThread <= nbThreadMax; nbThread += threadIncrement)
	    {
	    grid.db.x = nbThread;
	    Slice slice(grid, nbSlice);
//	    chrono.start();
	    slice.run();
//	    chrono.stop();
	    result = slice.getResult();
	    isOkLocal = MathTools::isEquals(result, PI_FLOAT, 0.0001f);
	    printf("Iteration %d: (%d, %d):", iteration, nbThread, nbSlice);
//	    cout << chrono;
	    printf("\tResult = %f, isOk=%d\n", result, isOkLocal);
	    isOk &= isOkLocal;
	    iteration++;
	    }
	}
    return isOk;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
