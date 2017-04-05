#include <iostream>

#include "Device.h"

#include "Montecarlo.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void montecarlo(curandState* ptrDevGeneratorGM, int* ptrDevNxTotalGM, int nbFlecheByThread);
extern __global__ void createGenerator(curandState* tabDevGeneratorGM, int deviceId);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur			*|
 \*-------------------------------------*/

Montecarlo::Montecarlo(const Grid& grid, const int nbFlecheTotal) :
	dg(grid.dg), db(grid.db), sizeOctetSM(db.x * sizeof(int)), result(0.f)
    {
    this->nbFlecheParThread = nbFlecheTotal / grid.threadCounts();
    this->nbFlecheTotal = grid.threadCounts() * nbFlecheParThread;
    this->sizeOctetResultGM = sizeof(int);
    this->sizeOctetTabGenerator = grid.threadCounts() * sizeof(curandState);

    Device::malloc(&ptrDevGMResult, sizeOctetResultGM);
    Device::memclear(ptrDevGMResult, sizeOctetResultGM);

    Device::malloc(&ptrDevGMTabGenerator, sizeOctetTabGenerator);
    Device::memclear(ptrDevGMTabGenerator, sizeOctetTabGenerator);

    const int DEVICE_ID = Device::getDeviceId();
    Device::lastCudaError("Montecarlo (before)"); // temp debug
    createGenerator<<<dg,db>>>(ptrDevGMTabGenerator, DEVICE_ID);
    Device::lastCudaError("Montecarlo (after)"); // temp debug

    // MM (copy Host->Device)
	{
	//Device::memcpyHToD(ptrDevV1, ptrV1, sizeOctet);
	}

//    Device::lastCudaError("Slice MM (end allocation)"); // temp debug, facultatif
    }

Montecarlo::~Montecarlo(void)
    {
    Device::free(ptrDevGMResult);
    Device::free(ptrDevGMTabGenerator);
    Device::lastCudaError("Slice MM (end deallocation)"); // temp debug, facultatif
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void Montecarlo::run()
    {
    Device::lastCudaError("Montecarlo (before)"); // temp debug
    montecarlo<<<dg,db, sizeOctetSM>>>(ptrDevGMTabGenerator, ptrDevGMResult, nbFlecheParThread); // assynchrone
    Device::lastCudaError("Montecarlo (after)"); // temp debug

//Device::synchronize(); // Temp,debug, only for printf in  GPU
    int result_device;
    float aireTotale = 4.f;
// MM (Device -> Host)
	{
	Device::memcpyDToH(&result_device, ptrDevGMResult, sizeOctetResultGM); // barriere synchronisation implicite
	}
    this->result = 4.f * result_device / nbFlecheTotal * aireTotale;
    }

float Montecarlo::getResult()
    {
    return this->result;
    }
/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
