#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"

#include "IndiceTools_GPU.h"
#include "RipplingMath.h"

using namespace gpu;

// Attention : 	Choix du nom est impotant!
//		VagueDevice.cu et non Vague.cu
// 		Dans ce dernier cas, probl�me de linkage, car le nom du .cu est le meme que le nom d'un .cpp (host)
//		On a donc ajouter Device (ou n'importequoi) pour que les noms soient diff�rents!

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void rippling(uchar4* ptrDevPixels, uint w, uint h, float t);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void rippling(uchar4* ptrDevPixels, uint w, uint h, float t)
    {
    RipplingMath ripplingMath = RipplingMath(w);

    int i, j;
    const int WH = w * h;
    const int NB_THREAD = Indice2D::nbThread();
    const int TID = Indice2D::tid();
    int s = TID;

    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &i, &j);

	ripplingMath.colorIJ(&ptrDevPixels[s], (float) i, (float) j, t);

	s += NB_THREAD;
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

