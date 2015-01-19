#include "RubikCube.h"


MovingSideCentersPhase::MovingSideCentersPhase(RuleEngine* engine, CubeModel* cubeModel)
{
	ruleEngine = engine;
	cube = cubeModel;
}

MovingSideCentersPhase::~MovingSideCentersPhase(void)
{
}

void MovingSideCentersPhase::solvePhase()
{
	int iter=0;

	while(ruleEngine->findPattern(MINTA_FAZIS4) == -1)
	{
		executeAll();
		iter++;
		if(iter>5) return;
	}
}

void MovingSideCentersPhase::executeAll()
{
	int h;
	int find;
	int iteration;
	for(iteration=0; iteration!=15; iteration++)
	{

		if(ruleEngine->findPattern(MINTA_FAZIS3) == -1)
		{
			setInfo("Phase 3 (prerequisite) failed");
			return;
		}
		
		find = ruleEngine->findPattern(NAGYT_KIST);
		if(find != -1) 
		{
			if(rules[find].elofeltetel[0] != RESCUE) 
			{
				h = 0;
				ruleEngine->applySolution(find, 0);
			} else 
			{
				h++;
				cube->getTransformEngine()->cTransform("6j");
				if(h>4) {
					ruleEngine->applySolution(find, 0);
					h = 0;
				}

			}
		}
		else 
		{
			cube->getTransformEngine()->cTransform("6j");
		}
		
		if(ruleEngine->findPattern(MINTA_FAZIS4) == -1)
			setInfo("Phase 4 failed");
		else
			setInfo("Phase 4 succeeded");
	}
}
