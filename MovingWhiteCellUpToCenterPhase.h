#pragma once

#include "ISolutionPhase.h"
#include "CubeModel.h"

class MovingWhiteCellUpToCenterPhase: public ISolutionPhase
{
public:
	MovingWhiteCellUpToCenterPhase(void);
	~MovingWhiteCellUpToCenterPhase(void);

	void solvePhase(CubeModel* cubeModel);
};

