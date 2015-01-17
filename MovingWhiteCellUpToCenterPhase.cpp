#include "RubikCube.h"

MovingWhiteCellUpToCenterPhase::MovingWhiteCellUpToCenterPhase(void)
{
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
			case 1: cTransform("7j"); break;
			case 2: cTransform("8j"); break;
			case 3: cTransform("7b"); break;
			case 4: cTransform("8b"); break;
			case 5: break;
			case 6: 
				cTransform("8b");
				cTransform("8b");
				break;	
			}
			return;
		}
	}
}