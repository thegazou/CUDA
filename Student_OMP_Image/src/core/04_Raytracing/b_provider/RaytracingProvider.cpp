#include "RaytracingProvider.h"

#include "MathTools.h"

#include "ImageAnimable_CPU.h"
#include "DomaineMath_CPU.h"

#include "../a_animable/Raytracing.h"
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
Animable_I<uchar4>* RaytracingProvider::createAnimable(void)
    {
    DomaineMath domaineMath = DomaineMath(-2.1f, -1.3, 0.8f, 1.3f);

    // Animation;
    uint nbSphere = 1;

    // Dimension
    uint dw = 16 * 60 * 2;
    uint dh = 16 * 60;

    return new Raytracing(dw, dh, nbShpere, domaineMath);
    }

/**
 * Override
 */
Image_I* RaytracingProvider::createImageGL(void)
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
