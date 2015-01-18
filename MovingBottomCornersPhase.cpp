#include "RubikCube.h"

MovingBottomCornersPhase::MovingBottomCornersPhase(void)
{
}


MovingBottomCornersPhase::~MovingBottomCornersPhase(void)
{
}

void MovingBottomCornersPhase::solvePhase(CubeModel* cubeModel)
{
	int i;
	int kesz;
	int fix;
	int iter=0;
	int find;

	kesz=1;
	for(i=1; i!=5; i++)
		if(sarokChkSum(i) != sarokPosChkSum(i)) 
			kesz = 0;
	if(kesz) 
		return;

	while(1)
	{
		iter++;

		fix = -1;
		for(i=1; i!=5; i++)
			if((double)sarokChkSum(i) == (double)sarokPosChkSum(i)) fix = i;


		switch(fix) 
		{
			case 1: find = getRuleEngine()->findPattern(SARKOK1);break;
			case 2: find = getRuleEngine()->findPattern(SARKOK2);break;
			case 3: find = getRuleEngine()->findPattern(SARKOK3);break;
			case 4: find = getRuleEngine()->findPattern(SARKOK4);break;
			default: find = getRuleEngine()->findPattern(SARKOK1);break;
		}

		getRuleEngine()->applySolution(find, 0);

		kesz=1;
		for(i=1; i!=5; i++)
			if((double)sarokChkSum(i) != (double)sarokPosChkSum(i)) 
			{
				kesz = 0;
			}
			if(kesz)  {
				return;
			}
	}

	return;
}

double MovingBottomCornersPhase::sarokChkSum(int num)
{
	CubeModel* cube = getCube();
	double retval;
	double ar, ag, ab, br, bg, bb, cr, cg, cb;
	if(num==1)
	{
		ar = cube->GetCellColor(1, 7).Red; ag = cube->GetCellColor(1, 7).Green; ab = cube->GetCellColor(1, 7).Blue;
		br = cube->GetCellColor(4, 7).Red; bg = cube->GetCellColor(4, 7).Green; bb = cube->GetCellColor(4, 7).Blue;
		cr = cube->GetCellColor(6, 7).Red; cg = cube->GetCellColor(6, 7).Green; cb = cube->GetCellColor(6, 7).Blue;
	}

	if(num==2)
	{
		ar = cube->GetCellColor(2, 7).Red; ag = cube->GetCellColor(2, 7).Green; ab = cube->GetCellColor(2, 7).Blue;
		br = cube->GetCellColor(1, 9).Red; bg = cube->GetCellColor(1, 9).Green; bb = cube->GetCellColor(1, 9).Blue;
		cr = cube->GetCellColor(6, 9).Red; cg = cube->GetCellColor(6, 9).Green; cb = cube->GetCellColor(6, 9).Blue;
	}
	if(num==3)
	{
		ar = cube->GetCellColor(2, 9).Red; ag = cube->GetCellColor(2, 9).Green; ab = cube->GetCellColor(2, 9).Blue;
		br = cube->GetCellColor(6, 3).Red; bg = cube->GetCellColor(6, 3).Green; bb = cube->GetCellColor(6, 3).Blue;
		cr = cube->GetCellColor(3, 9).Red; cg = cube->GetCellColor(3, 9).Green; cb = cube->GetCellColor(3, 9).Blue;
	}
	if(num==4)
	{
		ar = cube->GetCellColor(3, 7).Red; ag = cube->GetCellColor(3, 7).Green; ab = cube->GetCellColor(3, 7).Blue;
		br = cube->GetCellColor(4, 9).Red; bg = cube->GetCellColor(4, 9).Green; bb = cube->GetCellColor(4, 9).Blue;
		cr = cube->GetCellColor(6, 1).Red; cg = cube->GetCellColor(6, 1).Green; cb = cube->GetCellColor(6, 1).Blue;
	}

	double c[3];
	c[0] = 100.0*ar + 10.0*ag + 1.0*ab;
	c[1] = 100.0*br + 10.0*bg + 1.0*bb;
	c[2] = 100.0*cr + 10.0*cg + 1.0*cb;

	int i;
	int minIndex=0;
	int maxIndex=0;
	for(i=0; i!=3; i++)
		if(c[i] < c[minIndex]) minIndex = i;

	for(i=0; i!=3; i++)
		if(c[i] > c[maxIndex]) maxIndex = i;
	int kozepso = 3 - (maxIndex+minIndex);

	return c[minIndex]*100.0 + c[kozepso]*10.0 + c[maxIndex]*1.0;
}


double MovingBottomCornersPhase::sarokPosChkSum(int num)
{
	CubeModel* cube = getCube();
	double retval;
	double ar, ag, ab, br, bg, bb, cr, cg, cb;
	if(num==1)
	{
		ar = cube->GetCellColor(1, 5).Red; ag = cube->GetCellColor(1, 5).Green; ab = cube->GetCellColor(1, 5).Blue;
		br = cube->GetCellColor(4, 5).Red; bg = cube->GetCellColor(4, 5).Green; bb = cube->GetCellColor(4, 5).Blue;
		cr = cube->GetCellColor(6, 5).Red; cg = cube->GetCellColor(6, 5).Green; cb = cube->GetCellColor(6, 5).Blue;
	}

	if(num==2)
	{
		ar = cube->GetCellColor(2, 5).Red; ag = cube->GetCellColor(2, 5).Green; ab = cube->GetCellColor(2, 5).Blue;
		br = cube->GetCellColor(1, 5).Red; bg = cube->GetCellColor(1, 5).Green; bb = cube->GetCellColor(1, 5).Blue;
		cr = cube->GetCellColor(6, 5).Red; cg = cube->GetCellColor(6, 5).Green; cb = cube->GetCellColor(6, 5).Blue;
	}
	if(num==3)
	{
		ar = cube->GetCellColor(2, 5).Red; ag = cube->GetCellColor(2, 5).Green; ab = cube->GetCellColor(2, 5).Blue;
		br = cube->GetCellColor(6, 5).Red; bg = cube->GetCellColor(6, 5).Green; bb = cube->GetCellColor(6, 5).Blue;
		cr = cube->GetCellColor(3, 5).Red; cg = cube->GetCellColor(3, 5).Green; cb = cube->GetCellColor(3, 5).Blue;
	}
	if(num==4)
	{
		ar = cube->GetCellColor(3, 5).Red; ag = cube->GetCellColor(3, 5).Green; ab = cube->GetCellColor(3, 5).Blue;
		br = cube->GetCellColor(4, 5).Red; bg = cube->GetCellColor(4, 5).Green; bb = cube->GetCellColor(4, 5).Blue;
		cr = cube->GetCellColor(6, 5).Red; cg = cube->GetCellColor(6, 5).Green; cb = cube->GetCellColor(6, 5).Blue;
	}

	double c[3];
	c[0] = 100.0*ar + 10.0*ag + 1.0*ab;
	c[1] = 100.0*br + 10.0*bg + 1.0*bb;
	c[2] = 100.0*cr + 10.0*cg + 1.0*cb;

	int i;
	int minIndex=0;
	int maxIndex=0;
	for(i=0; i!=3; i++)
		if(c[i] < c[minIndex]) minIndex = i;

	for(i=0; i!=3; i++)
		if(c[i] > c[maxIndex]) maxIndex = i;
	int kozepso = 3 - (maxIndex+minIndex);


	return c[minIndex]*100.0 + c[kozepso]*10.0 + c[maxIndex]*1.0;
}