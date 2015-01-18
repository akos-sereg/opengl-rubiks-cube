#include "RubikCube.h"


MovingBottomCentersPhase::MovingBottomCentersPhase(RuleEngine *engine)
{
	ruleEngine = engine;
}


MovingBottomCentersPhase::~MovingBottomCentersPhase(void)
{
}

void MovingBottomCentersPhase::solvePhase(CubeModel* cubeModel)
{
	cube = cubeModel;

	int iter=0;

	while(ruleEngine->findPattern(MINTA_FAZIS5) == -1)
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

	if(ruleEngine->findPattern(MINTA_FAZIS5) != -1) return;
	for(j=0; j!=10; j++)
	{
		for(i=0; i!=10; i++)
		{
			s = ruleEngine->findPattern(ALSO1);
			if(s!=-1)
			{
				ruleEngine->applySolution(s, 0);
				if(ruleEngine->findPattern(MINTA_FAZIS5) != -1)
				{
					return;
				}
			}
		}
		cube->getTransformEngine()->cTransform("6j");
	}
}