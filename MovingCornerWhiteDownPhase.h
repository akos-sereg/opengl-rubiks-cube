#pragma once

#include "ISolutionPhase.h"
#include "CubeModel.h"

class MovingCornerWhiteDownPhase: public ISolutionPhase
{
public:
	MovingCornerWhiteDownPhase(RuleEngine* engine);
	~MovingCornerWhiteDownPhase(void);

	void solvePhase(CubeModel* cubeModel);
	void executeAll();

private:
	CubeModel* cube;
	RuleEngine* ruleEngine;
};

