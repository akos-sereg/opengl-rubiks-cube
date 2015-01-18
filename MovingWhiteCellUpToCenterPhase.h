#pragma once

#include "ISolutionPhase.h"
#include "CubeModel.h"
#include "RuleEngine.h"

class MovingWhiteCellUpToCenterPhase: public ISolutionPhase
{
public:
	MovingWhiteCellUpToCenterPhase(RuleEngine *engine);
	~MovingWhiteCellUpToCenterPhase(void);
	void solvePhase(CubeModel* cubeModel);

private:
	RuleEngine* ruleEngine;
};

