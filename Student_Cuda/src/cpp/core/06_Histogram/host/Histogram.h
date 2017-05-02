#pragma once

#include "cudaTools.h"
#include "Grid.h"

class Histogram
    {

    public:
	Histogram(const Grid& grid);

	virtual ~Histogram();

    public:

	void run();
	bool checkResult();

    private:
	dim3 dg;
	dim3 db;

	//Data
	int dataMax;
	int dataSize;
	int* tabData;

	//Output
	int* tabResult;

	//GM
	int* ptrDevGMData;
	size_t sizeOctetGM;

	//SM
	size_t sizeOctetSM;
    };