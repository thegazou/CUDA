#include "MandelbrotProvider.h"

#include "MathTools.h"

#include "ImageAnimable_CPU.h"
#include "DomaineMath_CPU.h"

#include "../a_animable/Mandelbrot.h"
using namespace cpu;

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Surcharge		*|
 \*-------------------------------------*/

/**
 * Override
 */
Animable_I<uchar4>* MandelbrotProvider::createAnimable(void)
    {
    DomaineMath domaineMath = DomaineMath(-2.1f, -1.3, 0.8f, 1.3f);

    // Animation;
    int tMin = 30;
    int tMax = 100;

    // Dimension
    int dw = 16 * 60 * 2;
    int dh = 16 * 60;

    return new Mandelbrot(dw, dh, tMin, tMax, domaineMath);
    }

/**
 * Override
 */
Image_I* MandelbrotProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(0, 0, 0); // black
    return new ImageAnimable_RGBA_uchar4(createAnimable(),colorTexte);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
