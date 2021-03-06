#include <iostream>
#include "Device.h"
#include "Montecarlo2.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void montecarlo2(curandState* ptrDevGeneratorGM, int* ptrDevNxTotalGM, int nbFlecheByThread);
extern __global__ void createGenerator2(curandState* tabDevGeneratorGM, int deviceId);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur			*|
 \*-------------------------------------*/

Montecarlo2::Montecarlo2(const Grid& grid, const int nbFlecheTotal) :
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
    createGenerator2<<<dg,db>>>(ptrDevGMTabGenerator, DEVICE_ID);
    Device::lastCudaError("Montecarlo (after)"); // temp debug
    }

Montecarlo2::~Montecarlo2(void)
    {
    Device::free(ptrDevGMResult);
    Device::free(ptrDevGMTabGenerator);
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void Montecarlo2::run()
    {
    Device::lastCudaError("Montecarlo (before)"); // temp debug
    montecarlo2<<<dg,db, sizeOctetSM>>>(ptrDevGMTabGenerator, ptrDevGMResult, nbFlecheParThread); // assynchrone
    Device::lastCudaError("Montecarlo (after)"); // temp debug

    int result_device;
    Device::memcpyDToH(&result_device, ptrDevGMResult, sizeOctetResultGM); // barriere synchronisation implicite
    this->result = 4.f * result_device / nbFlecheTotal;
    }

float Montecarlo2::getResult()
    {
    return this->result;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
