#include <iostream>
#include <stdlib.h>

#include "Settings_CPU.h"
using namespace cpu;

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern int mainImage(Settings& settings);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static int use(Settings& settings);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int main(int argc, char** argv)
    {
    LaunchMode launchMode = LaunchMode::IMAGE; // IMAGE ANIMABLE
    Settings settings(launchMode, argc, argv);

    return use(settings);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

int use(Settings& settings)
    {
    return mainImage(settings); // Bloquant, Tant qu'une fenetre est ouverte
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

