#pragma once

#include "ISolutionPhase.h"
#include "CubeModel.h"

class MovingBottomCentersPhase: public ISolutionPhase
{
public:
	MovingBottomCentersPhase(void);
	~MovingBottomCentersPhase(void);

	void solvePhase(CubeModel* cubeModel);
	void executeAll();

private:
	CubeModel* cube;
};

