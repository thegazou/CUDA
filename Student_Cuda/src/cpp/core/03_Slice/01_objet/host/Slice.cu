#include <iostream>

#include "Device.h"
#include "Slice.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void slice(float* ptrDevGMResult, uint nbSlice);

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

Slice::Slice(const Grid& grid, const uint nbSlice) :
	nbSlice(nbSlice), dg(grid.dg), db(grid.db), sizeOctetSM(db.x * sizeof(float)), sizeOctetGM(sizeof(float)), result(0.f)
    {
    Device::malloc(&ptrDevGMResult, sizeOctetGM);
    Device::memclear(ptrDevGMResult, sizeOctetGM);

    // MM (copy Host->Device)
	{
	//Device::memcpyHToD(ptrDevV1, ptrV1, sizeOctet);
	}

//    Device::lastCudaError("Slice MM (end allocation)"); // temp debug, facultatif
    }

Slice::~Slice(void)
    {
    Device::free(ptrDevGMResult);
//    Device::lastCudaError("Slice MM (end deallocation)"); // temp debug, facultatif
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void Slice::run()
    {
//    Device::lastCudaError("Slice (before)"); // temp debug
    slice<<<dg,db, sizeOctetSM>>>(ptrDevGMResult, nbSlice);// assynchrone
//    Device::lastCudaError("Slice (after)"); // temp debug

//Device::synchronize(); // Temp,debug, only for printf in  GPU

// MM (Device -> Host)
	{
	Device::memcpyDToH(&result, ptrDevGMResult, sizeOctetGM); // barriere synchronisation implicite
	}
    this->result *= 4.f / (float) nbSlice;
    }

float Slice::getResult()
    {
    return this->result;
    }
/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/