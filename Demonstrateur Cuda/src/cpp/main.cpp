#include <stdlib.h>
#include <assert.h>
#include <iostream>

#include "cudaTools.h"
#include "Device.h"

#include "Settings_GPU.h"
using namespace gpu;

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

int main(int argc, char** argv);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static int use(Settings& option);
static int start(Settings& option);
static void initCuda(Settings& option);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int main(int argc, char** argv)
    {
    // Server Cuda1: in [0,5]	(6 Devices)
    // Server Cuda2: in [0,3]	(4 Devices)
    // Server Cuda3: in [0,2]	(2 Devices)
    int DEVICE_ID = 2;

    LaunchMode launchMode = LaunchMode::IMAGE;
    Settings settings(launchMode, DEVICE_ID, argc, argv);

    return use(settings);
    }

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int use(Settings& settings)
    {
    if (Device::isCuda())
	{
	initCuda(settings);
	int isOk = start(settings);

	Device::reset();

	return isOk;
	}
    else
	{
	return EXIT_FAILURE;
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void initCuda(Settings& settings)
    {
    int deviceId = settings.getDeviceId();
    Device::setDevice(deviceId);
    Device::loadCudaDriver(deviceId);
    }

int start(Settings& settings)
    {
    return mainImage(settings);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

