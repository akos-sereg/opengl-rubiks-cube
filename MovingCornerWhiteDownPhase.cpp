#include "RubikCube.h"

MovingCornerWhiteDownPhase::MovingCornerWhiteDownPhase(void)
{
}


MovingCornerWhiteDownPhase::~MovingCornerWhiteDownPhase(void)
{
}

void MovingCornerWhiteDownPhase::solvePhase(CubeModel* cubeModel)
{
	int iter = 0;
	while(getRuleEngine()->findPattern(MINTA_FAZIS3) == -1)
	{
		executeAll();
		iter++;
		if(iter >5) return;
	}
}

void MovingCornerWhiteDownPhase::executeAll() 
{
	int find;
	int i,j,old,m;
	int find2;
	if(getRuleEngine()->findPattern(MINTA_FAZIS2) == -1) 
	{
		setInfo("Second phase (prerequisite) is not complete. Please extend rule base to cover this situation.");
		return;
	}
	
	for(old=0; old!=4; old++)
	{
		find2 = getRuleEngine()->findPattern(SAROKFEHER_LE);
		if(find2!=-1)
			getRuleEngine()->applySolution(find2, 0);

		for(j=0; j!=5; j++)
		{
			find = getRuleEngine()->findPattern(FEHER_LENT_POZICIOBAN);
			if(find != -1) 
				getRuleEngine()->applySolution(find, 0);

			cTransform("6j");
		}
	}
}