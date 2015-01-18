#pragma once

#include "ISolutionPhase.h"
#include "CubeModel.h"

class MovingCornerWhiteDownPhase: public ISolutionPhase
{
public:
	MovingCornerWhiteDownPhase(void);
	~MovingCornerWhiteDownPhase(void);

	void solvePhase(CubeModel* cubeModel);
	void executeAll();

private:
	CubeModel* cube;
};

