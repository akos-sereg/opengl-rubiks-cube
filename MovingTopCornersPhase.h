#pragma once

#include "ISolutionPhase.h"
#include "CubeModel.h"

class MovingTopCornersPhase: public ISolutionPhase
{
public:
	MovingTopCornersPhase(RuleEngine* engine);
	~MovingTopCornersPhase(void);
	void solvePhase(CubeModel* cubeModel);

private:
	void executeAll();
	int executeBottom();
	CubeModel* cube;
	RuleEngine* ruleEngine;
};

