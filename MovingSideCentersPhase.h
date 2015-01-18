#pragma once

#include "ISolutionPhase.h"
#include "CubeModel.h"

class MovingSideCentersPhase: public ISolutionPhase
{
public:
	MovingSideCentersPhase(RuleEngine* engine);
	~MovingSideCentersPhase(void);

	void solvePhase(CubeModel* cubeModel);
	void executeAll();

private:
	CubeModel* cube;
	RuleEngine* ruleEngine;
};

