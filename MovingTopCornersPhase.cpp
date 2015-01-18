#include "RubikCube.h"

MovingTopCornersPhase::MovingTopCornersPhase(void)
{
}


MovingTopCornersPhase::~MovingTopCornersPhase(void)
{
}

void MovingTopCornersPhase::solvePhase(CubeModel* cubeModel)
{
	cube = cubeModel;

	int iter = 0;
	while(getRuleEngine()->findPattern(MINTA_FAZIS2) == -1) 
	{
		executeAll();

		iter++;
		if(iter > 5) return;
	}
}

void MovingTopCornersPhase::executeAll() 
{
	int j,i,k;
	for(j=0; j!=4; j++)
	{
		if(executeBottom()) continue;
		for(i=0; i!=getRuleEngine()->rulesLen();  i++)
		{
			if(rules[i].group == FEHERET_ALULRA)
			{
				if(getRuleEngine()->checkPattern(i)) 
				{	
					getRuleEngine()->applySolution(i, 0);
					int k;
					for(k=0; k!=4; k++)
					{
						if(executeBottom()) break;
						cube->getTransformEngine()->cTransform("6j");
					}
				}
			}
		}
	}

	for(i=0; i!=getRuleEngine()->rulesLen(); i++)
	{
		if(rules[i].group == MINTA_FAZIS2) 
			if(!getRuleEngine()->checkPattern(i)) setWarning("Error: phase 2 was not successful. Rule set should be extended to cover this situation.");
	}
}

int MovingTopCornersPhase::executeBottom() 
{
	int i=0;
	for(i=0; i!=getRuleEngine()->rulesLen(); i++)
	{
		if(rules[i].group == MINTA_KORONA_FELPORGET)
		{
			if(getRuleEngine()->checkPattern(i))
			{
				char buff[256];
				sprintf(buff, "%d true", i);
				setWarning(buff);
				getRuleEngine()->applySolution(i,0);
				return 1; 
			} else setWarning("");
		}
	}
	return 0; 
}