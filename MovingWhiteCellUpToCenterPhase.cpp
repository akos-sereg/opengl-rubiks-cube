#include "RubikCube.h"

MovingWhiteCellUpToCenterPhase::MovingWhiteCellUpToCenterPhase(RuleEngine *engine)
{
	ruleEngine = engine;
}


MovingWhiteCellUpToCenterPhase::~MovingWhiteCellUpToCenterPhase(void)
{
}

void MovingWhiteCellUpToCenterPhase::solvePhase(CubeModel* cubeModel) 
{
	setInfo("Running Phase 1");

	int i;
	
	for(i=1; i!=7; i++)
	{
		if((int)cubeModel->GetCellColor(i, 5).Red == 1 &&
			(int)cubeModel->GetCellColor(i, 5).Green == 1 &&
			(int)cubeModel->GetCellColor(i, 5).Blue == 1)
		{
			switch(i)
			{
			case 1: cubeModel->getTransformEngine()->cTransform("7j"); break;
			case 2: cubeModel->getTransformEngine()->cTransform("8j"); break;
			case 3: cubeModel->getTransformEngine()->cTransform("7b"); break;
			case 4: cubeModel->getTransformEngine()->cTransform("8b"); break;
			case 5: break;
			case 6: 
				cubeModel->getTransformEngine()->cTransform("8b");
				cubeModel->getTransformEngine()->cTransform("8b");
				break;	
			}
			return;
		}
	}
}