#include "RubikCube.h"

using namespace std;

SolutionStrategy::SolutionStrategy(RuleEngine *engine)
{
	ruleEngine = engine;
}

int SolutionStrategy::run()
{
	std::list<ISolutionPhase*> solutionPhases;
	solutionPhases.push_back(new MovingWhiteCellUpToCenterPhase(ruleEngine));
	solutionPhases.push_back(new MovingTopCornersPhase(ruleEngine));
	solutionPhases.push_back(new MovingCornerWhiteDownPhase(ruleEngine));
	solutionPhases.push_back(new MovingSideCentersPhase(ruleEngine));
	solutionPhases.push_back(new MovingBottomCentersPhase(ruleEngine));
	solutionPhases.push_back(new MovingBottomCornersPhase(ruleEngine));
	solutionPhases.push_back(new CheckSolvedCubePhase(ruleEngine));
	
	for (std::list<ISolutionPhase*>::const_iterator iterator = solutionPhases.begin(), end = solutionPhases.end(); iterator != end; ++iterator) {
		ISolutionPhase* currentPhase = *iterator;
		currentPhase->solvePhase(getCube());
	}

	if(ruleEngine->findPattern(MINTA_FAZIS5) == -1) return 0;

	return 1;
}
