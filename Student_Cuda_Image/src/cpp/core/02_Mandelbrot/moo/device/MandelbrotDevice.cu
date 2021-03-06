#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"

#include "IndiceTools_GPU.h"
#include "DomaineMath_GPU.h"

#include "MandelbrotMath.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void mandelbrot(uchar4* ptrDevPixels, uint w, uint h, DomaineMath domaineMath, float t);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__global__ void mandelbrot(uchar4* ptrDevPixels, uint w, uint h, DomaineMath domaineMath, float t)
    {
    MandelbrotMath mandelbrotMath = MandelbrotMath(t);

    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();
    const int WH = w * h;

    double x,y;
    int i,j;
    int s = TID;

    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &i, &j); // update (i, j)
	domaineMath.toXY(i, j, &x, &y); //  (i,j) -> (x,y)

	mandelbrotMath.colorXY(&ptrDevPixels[s], (float) x, (float) y); // update ptrDevPixels[s]

	s += NB_THREAD;
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

