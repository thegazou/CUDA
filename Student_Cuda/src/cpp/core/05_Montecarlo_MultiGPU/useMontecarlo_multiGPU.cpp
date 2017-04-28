#include <iostream>
#include "Grid.h"
#include "Device.h"
#include "MathTools.h"
#include "limits.h"
#include "Chrono.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

#include "Montecarlo_multiGPU.h"

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useMontecarlo_multiGPU(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/
bool useMontecarlo_multiGPU(Grid grid);
/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useMontecarlo_multiGPU()
    {
    bool isOk = true;
    dim3 dg = dim3(2, 1, 1);
    dim3 db = dim3(1024, 1, 1); //Can be ANY number. If it is not a power of 2 it is andle later.
    Grid grid(dg, db);

    //Useful if you want to compare several implementations.
    isOk &= useMontecarlo_multiGPU(grid);

    return isOk;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

bool useMontecarlo_multiGPU(Grid grid)
    {
    float result;
    Chrono chrono = Chrono("Time:");
    int nbFlecheTotal = INT_MAX;

    Montecarlo_multiGPU montecarlo(grid, nbFlecheTotal);
    chrono.start();
    montecarlo.run();
    chrono.stop();
    result = montecarlo.getResult();
    printf("Montecarlo__multiGPU: ");
    chrono.print();
    printf(", Result = %f\n", result);

    return MathTools::isEquals(result, PI_FLOAT, 0.001f);
    }
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

