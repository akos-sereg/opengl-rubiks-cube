#include "RubikCubeController.h"
#include <time.h>

#ifdef MODE_COMMAND_LINE


int main() 
{

	// Init
	//getRubikCubeController()->init();
	getRubikCubeController()->getCube()->DefaultColors();

	// Random rotate
	srand (time(NULL));
	for (int i=0; i!=50; i++) {
		getRubikCubeController()->getCube()
			->getTransformEngine()->stopRotating();         // to register cTransform

		getRubikCubeController()->setStepCount(0);                // collecting graphical movements from 0 index
		int random = rand()%16;
		printf("Random rotation direction identifier: %d\r\n", random);
		getRubikCubeController()->getCube()->getTransformEngine()->cTransformN(random);  // random transformation saved to history
	}

	// Solve cube
	getRubikCubeController()->saveCubeColors();                // save current cube. solutionStrategy will do transformations on it
	getRubikCubeController()->setStepCount(0);                 // start step count from zero
	getRubikCubeController()->setRotatingStep(0);
	getRubikCubeController()->getCube()
		->getTransformEngine()->stopRotating();          // no graphical movements allowed
				
	if(getSolutionStrategy()->run())                          // solve cube. this will make transformations on current cube
	{
		getRubikCubeController()->getCube()->getTransformEngine()->startRotating();      // graphics movements are allowed
		printf("Cube solved in %d steps", getRubikCubeController()->getStepCount());
	} else {
		printf("Cube could not be soleved");
	}

	scanf("hi");

	// Exit
	getRubikCubeController()->shutDown(); 
}

#endif
