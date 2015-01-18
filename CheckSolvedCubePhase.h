#pragma once

#include "ISolutionPhase.h"
#include "CubeModel.h"

class CheckSolvedCubePhase: public ISolutionPhase
{
public:
	CheckSolvedCubePhase(RuleEngine *engine);
	~CheckSolvedCubePhase(void);

	void solvePhase(CubeModel* cubeModel);
private:
	RuleEngine *ruleEngine;
};

