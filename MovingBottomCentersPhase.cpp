#include "RubikCube.h"


MovingBottomCentersPhase::MovingBottomCentersPhase(void)
{
}


MovingBottomCentersPhase::~MovingBottomCentersPhase(void)
{
}

void MovingBottomCentersPhase::solvePhase(CubeModel* cubeModel)
{
	cube = cubeModel;

	int iter=0;

	while(getRuleEngine()->findPattern(MINTA_FAZIS5) == -1)
	{
		executeAll();
		iter++;
		if(iter>5) return;
	}
}

void MovingBottomCentersPhase::executeAll()
{
	int s;
	int i,j;

	if(getRuleEngine()->findPattern(MINTA_FAZIS5) != -1) return;
	for(j=0; j!=10; j++)
	{
		for(i=0; i!=10; i++)
		{
			s = getRuleEngine()->findPattern(ALSO1);
			if(s!=-1)
			{
				getRuleEngine()->applySolution(s, 0);
				if(getRuleEngine()->findPattern(MINTA_FAZIS5) != -1)
				{
					return;
				}
			}
		}
		cube->getTransformEngine()->cTransform("6j");
	}
}