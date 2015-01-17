#pragma once

#include "CubeModel.h"

class ISolutionPhase
{
public:

	virtual void solvePhase(CubeModel* cubeModel) = 0;

};

