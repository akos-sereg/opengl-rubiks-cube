#include "RubikCube.h"

using namespace std;

int SolutionStrategy::run()
{
	int iter=0;
	
	std::list<ISolutionPhase*> solutionPhases;
	solutionPhases.push_back(new MovingWhiteCellUpToCenterPhase());
	solutionPhases.push_back(new MovingTopCornersPhase());
	
	for (std::list<ISolutionPhase*>::const_iterator iterator = solutionPhases.begin(), end = solutionPhases.end(); iterator != end; ++iterator) {
		ISolutionPhase* currentPhase = *iterator;
		currentPhase->solvePhase(getCube());
	}

	while(getRuleEngine()->findPattern(MINTA_FAZIS3) == -1)
	{
		solvePhase3();
		iter++;
		if(iter >5) return 0;
	}

	iter=0;
	while(getRuleEngine()->findPattern(MINTA_FAZIS4) == -1)
	{
		solvePhase4();
		iter++;
		if(iter>5) return 0;
	}

	iter=0;
	while(getRuleEngine()->findPattern(MINTA_FAZIS5) == -1)
	{
		solvePhase5();
		iter++;
		if(iter>5) return 0;
	}

	solvePhase6();
	solvePhase7();

	if(getRuleEngine()->findPattern(MINTA_FAZIS5) == -1) return 0;

	return 1;

}

void SolutionStrategy::solvePhase3()
{
	int find;
	int i,j,old,m;
	int find2;
	if(getRuleEngine()->findPattern(MINTA_FAZIS2) == -1) 
	{
		setInfo("Nincs kesz a masodik fazis!");
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

void SolutionStrategy::solvePhase4()
{
	int find;
	int iteration;
	for(iteration=0; iteration!=15; iteration++)
	{

		if(getRuleEngine()->findPattern(MINTA_FAZIS3) == -1)
		{
			setInfo("Nincs harmadik fazisban!");
			return;
		}
		
		find = getRuleEngine()->findPattern(NAGYT_KIST);
		if(find!=-1) 
		{
			if(rules[find].elofeltetel[0] != RESCUE) 
			{
				setH(0);
				getRuleEngine()->applySolution(find, 0);
			} else 
			{
				incrementH();
				cTransform("6j");
				if(getH()>4) {	// nincs mit tenni.
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


void SolutionStrategy::solvePhase5()
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
					return; // kesz van az 5. fazis
				}
			}
		}
		cTransform("6j");
	}
}


void SolutionStrategy::solvePhase6()
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


void SolutionStrategy::solvePhase7()
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

double SolutionStrategy::sarokChkSum(int num)
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


double SolutionStrategy::sarokPosChkSum(int num)
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

int SolutionStrategy::compareColors(int side1, int place1, int side2, int place2)
{
	CubeModel* cube = getCube();
	if((cube->GetCellColor(side1, place1).Red == cube->GetCellColor(side2, place2).Red) &&
		(cube->GetCellColor(side1, place1).Green == cube->GetCellColor(side2, place2).Green) &&
		(cube->GetCellColor(side1, place1).Blue == cube->GetCellColor(side2, place2).Blue))
	{
		return 1;
	} else return 0;
}

