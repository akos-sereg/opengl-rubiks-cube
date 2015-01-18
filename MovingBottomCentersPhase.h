#pragma once

#include "ISolutionPhase.h"
#include "CubeModel.h"

class MovingBottomCentersPhase: public ISolutionPhase
{
public:
	MovingBottomCentersPhase(RuleEngine* engine);
	~MovingBottomCentersPhase(void);

	void solvePhase(CubeModel* cubeModel);
	void executeAll();

private:
	CubeModel* cube;
	RuleEngine* ruleEngine;
};

