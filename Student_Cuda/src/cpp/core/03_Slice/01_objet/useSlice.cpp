#include <iostream>
#include "Grid.h"
#include "Device.h"
#include "MathTools.h"
#include "limits.h"
#include "Variateur_CPU.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

#include "Slice.h"

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useSlice(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useSlice()
    {
    uint nbSlice = INT_MAX - 1;
    nbSlice *= 2;
    float result;

    // Grid cuda

    dim3 dg = dim3(24, 1, 1);
    dim3 db = dim3(1024, 1, 1);  //faire varier
    Grid grid(dg, db);

    Slice slice(grid, nbSlice); // on passse la grille à AddVector pour pouvoir facilement la faire varier de l'extérieur (ici) pour trouver l'optimum
    slice.run();
    result = slice.getResult();
    printf("Result = %f\n", result);

    bool isOk = MathTools::isEquals(result, PI_FLOAT, 0.0001f);

    return isOk;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
