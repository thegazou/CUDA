#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "Device.h"
#include "cudaTools.h"

#include "RipplingProvider.h"
#include "RaytracingProvider.h"
#include "MandelbrotProvider.h"

#include "Settings_GPU.h"
#include "Viewer_GPU.h"

using namespace gpu;

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
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

int mainImage(Settings& settings)
    {
    GLUTWindowManagers::init(settings.getArgc(), settings.getArgv()); //only once

    // ImageOption : (boolean,boolean) : (isSelection,isAnimation)
    ImageOption zoomable(true, true, false, false);
    ImageOption nozoomable(false, true, false, false);

    GLUTWindowManagers* windowManager = GLUTWindowManagers::getInstance();

    Viewer < RipplingProvider > rippling (nozoomable, 25, 0);
    rippling.setSize(450, 450);
    Viewer < MandelbrotProvider > mandelbrot (zoomable, 500, 0);
//    mandelbrot.setSize(800, 450);
    Viewer < RaytracingProvider > raytracing (nozoomable, 0, 100);
    raytracing.setSize(1250, 450);

    windowManager->addWindow(rippling.getGLUTWindowImage());
    windowManager->addWindow(mandelbrot.getGLUTWindowImage());
    windowManager->addWindow(raytracing.getGLUTWindowImage());

//    GLImageFactory* factory = GLImageFactory().create();
//    LImageDisplayable lImageDisplayble = LImageDisplayable(factory, mandelbrot, zoomable);
//    //GLUTWindowImage glutWindowImage = GLUTWindowImage(lIMageDisplayble.getImage(), "Mandelbrot", 300, 300);
//    GLUTWindow* glutWindow = new GLUTWindow(lImageDisplayble.getImage(), "Mandelbrot", 300, 300, 300, 300);
//    windowManager->addWindow(glutWindow);

    // Common
    windowManager->runALL(); // Bloquant, Tant qu'une fenetre est ouverte

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

