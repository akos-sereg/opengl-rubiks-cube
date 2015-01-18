#pragma once

#include "isolutionphase.h"

class MovingBottomCornersPhase: public ISolutionPhase
{
public:
	MovingBottomCornersPhase(RuleEngine* engine);
	~MovingBottomCornersPhase(void);

	void solvePhase(CubeModel* cubeModel);
	double sarokChkSum(int num);
	double sarokPosChkSum(int num);

private:
	RuleEngine* ruleEngine;
};

