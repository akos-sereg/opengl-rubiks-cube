#include "RubikCube.h"


MovingSideCentersPhase::MovingSideCentersPhase(void)
{
}


MovingSideCentersPhase::~MovingSideCentersPhase(void)
{
}

void MovingSideCentersPhase::solvePhase(CubeModel* cubeModel)
{
	int iter=0;

	while(getRuleEngine()->findPattern(MINTA_FAZIS4) == -1)
	{
		executeAll();
		iter++;
		if(iter>5) return;
	}
}

void MovingSideCentersPhase::executeAll()
{
	int find;
	int iteration;
	for(iteration=0; iteration!=15; iteration++)
	{

		if(getRuleEngine()->findPattern(MINTA_FAZIS3) == -1)
		{
			setInfo("Phase 3 (prerequisite) failed");
			return;
		}
		
		find = getRuleEngine()->findPattern(NAGYT_KIST);
		if(find != -1) 
		{
			if(rules[find].elofeltetel[0] != RESCUE) 
			{
				setH(0);
				getRuleEngine()->applySolution(find, 0);
			} else 
			{
				incrementH();
				cTransform("6j");
				if(getH()>4) {
					getRuleEngine()->applySolution(find, 0);
					setH(0);
				}

			}
		}
		else 
		{
			cTransform("6j");
		}
		
		if(getRuleEngine()->findPattern(MINTA_FAZIS4) == -1)
			setInfo("Phase 4 failed");
		else
			setInfo("Phase 4 succeeded");
	}
}
