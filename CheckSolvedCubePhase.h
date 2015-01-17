#pragma once

#include "ISolutionPhase.h"
#include "CubeModel.h"

class CheckSolvedCubePhase: public ISolutionPhase
{
public:
	CheckSolvedCubePhase(void);
	~CheckSolvedCubePhase(void);

	void solvePhase(CubeModel* cubeModel);
};

