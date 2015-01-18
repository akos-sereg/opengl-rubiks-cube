#pragma once

#include "ISolutionPhase.h"
#include "CubeModel.h"

class MovingTopCornersPhase: public ISolutionPhase
{
public:
	MovingTopCornersPhase(void);
	~MovingTopCornersPhase(void);
	void solvePhase(CubeModel* cubeModel);

private:
	void executeAll();
	int executeBottom();
	CubeModel* cube;
};

