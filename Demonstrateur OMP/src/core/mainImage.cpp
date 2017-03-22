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

    Viewer < RipplingProvider > rippling = Viewer < RipplingProvider > (nozoomable, 0, 0);
    rippling.setSize(450, 450);
    Viewer < MandelbrotProvider > mandelbrot = Viewer < MandelbrotProvider > (zoomable, 500, 0);
    mandelbrot.setSize(800, 450);
    Viewer < RaytracingProvider > raytracing = Viewer < RaytracingProvider > (nozoomable, 0, 450);
    raytracing.setSize(1250, 450);

    // Common
    GLUTImageViewers::runALL(); // Bloquant, Tant qu'une fenetre est ouverte

    return EXIT_SUCCESS;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

