#include <iostream>

#include "RipplingProvider.h"
#include "MandelbrotProvider.h"
#include "RaytracingProvider.h"

#include "Viewer_CPU.h"
#include "Settings_CPU.h"
using namespace cpu;

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported		*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainImage(Settings& settings);

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

int mainImage(Settings& settings)
    {
    GLUTImageViewers::init(settings.getArgc(), settings.getArgv()); //only once

    // ImageOption : (boolean,boolean) : (isSelection,isAnimation)
    ImageOption zoomable(true, true, false, false);
    ImageOption nozoomable(false, true, false, false);

    Viewer < RaytracingProvider > raytracing(nozoomable, 0, 0);
    raytracing.setSize(1920, 960);
    Viewer < MandelbrotProvider > mandelbrot(zoomable, 0, 0);
    mandelbrot.setSize(1100, 960);
    Viewer < RipplingProvider > rippling(nozoomable, 0, 0);
    rippling.setSize(960, 960);

    // Common
    GLUTImageViewers::runALL(); // Bloquant, Tant qu'une fenetre est ouverte

    return EXIT_SUCCESS;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

