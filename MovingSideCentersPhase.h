#pragma once

#include "ISolutionPhase.h"
#include "CubeModel.h"

class MovingSideCentersPhase: public ISolutionPhase
{
public:
	MovingSideCentersPhase(void);
	~MovingSideCentersPhase(void);

	void solvePhase(CubeModel* cubeModel);
	void executeAll();

private:
	CubeModel* cube;
};

