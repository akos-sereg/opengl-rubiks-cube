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
	solutionPhases.push_back(new CheckSolvedCubePhase());
	
	for (std::list<ISolutionPhase*>::const_iterator iterator = solutionPhases.begin(), end = solutionPhases.end(); iterator != end; ++iterator) {
		ISolutionPhase* currentPhase = *iterator;
		currentPhase->solvePhase(getCube());
	}

	if(getRuleEngine()->findPattern(MINTA_FAZIS5) == -1) return 0;

	return 1;
}
