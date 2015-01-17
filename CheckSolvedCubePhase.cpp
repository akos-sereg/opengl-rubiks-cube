#include "RubikCube.h"

CheckSolvedCubePhase::CheckSolvedCubePhase(void)
{
}


CheckSolvedCubePhase::~CheckSolvedCubePhase(void)
{
}

void CheckSolvedCubePhase::solvePhase(CubeModel* cubeModel)
{
	int find;

	while(getRuleEngine()->findPattern(KIRAKOTT) == -1)
	{
		find = getRuleEngine()->findPattern(FINISH);
		if(find == -1) find = getRuleEngine()->findPattern(FINISH_RESC);
		if(find != -1)
			getRuleEngine()->applySolution(find, 0);
	} 

	setInfo("Cube solved");
}