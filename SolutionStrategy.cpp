#include "RubikCube.h"

using namespace std;

int SolutionStrategy::run()
{
	std::list<ISolutionPhase*> solutionPhases;
	solutionPhases.push_back(new MovingWhiteCellUpToCenterPhase());
	solutionPhases.push_back(new MovingTopCornersPhase());
	solutionPhases.push_back(new MovingCornerWhiteDownPhase());
	solutionPhases.push_back(new MovingSideCentersPhase());
	solutionPhases.push_back(new MovingBottomCentersPhase());
	solutionPhases.push_back(new MovingBottomCornersPhase());
	
	for (std::list<ISolutionPhase*>::const_iterator iterator = solutionPhases.begin(), end = solutionPhases.end(); iterator != end; ++iterator) {
		ISolutionPhase* currentPhase = *iterator;
		currentPhase->solvePhase(getCube());
	}

	solvePhase7();

	if(getRuleEngine()->findPattern(MINTA_FAZIS5) == -1) return 0;

	return 1;
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

