#include "RubikCube.h"

struct cubeTransform
{
	cubeTransformStep steps[24];
} cubeTransform[20] =
{ 
	{ // 1. right
		{
			{5, 7, 4, 7}, {5, 8, 4, 4}, {5, 9, 4, 1}, {2, 1, 5, 7}, {2, 4, 5, 8},
			{2, 7, 5, 9}, {6, 9, 2, 1}, {6, 8, 2, 4}, {6, 7, 2, 7}, {4, 1, 6, 7},
			{4, 4, 6, 8}, {4, 7, 6, 9}, {1, 1, 1, 7}, {1, 2, 1, 4}, {1, 3, 1, 1}, 
			{1, 4, 1, 8}, {1, 5, 1, 5}, {1, 6, 1, 2}, {1, 7, 1, 9}, {1, 8, 1, 6}, 
			{1, 9, 1, 3}, {-1, -1, -1, -1}
		} 
	}, { // 1. left
		{
			{5, 7, 2, 1}, {5, 8, 2, 4}, {5, 9, 2, 7}, {2, 1, 6, 9}, {2, 4, 6, 8},
			{2, 7, 6, 7}, {6, 9, 4, 7}, {6, 8, 4, 4}, {6, 7, 4, 1}, {4, 1, 5, 9},
			{4, 4, 5, 8}, {4, 7, 5, 7}, {1, 1, 1, 3}, {1, 2, 1, 6}, {1, 3, 1, 9},
			{1, 4, 1, 2}, {1, 5, 1, 5}, {1, 6, 1, 8}, {1, 7, 1, 1}, {1, 8, 1, 4},
			{1, 9, 1, 7}, {-1, -1, -1, -1}
		}
	}, { // 2. right
		{
			{3, 3, 5, 9}, {3, 6, 5, 6}, {3, 9, 5, 3}, {6, 3, 3, 3}, {6, 6, 3, 6},
			{6, 9, 3, 9}, {1, 3, 6, 9}, {1, 6, 6, 6}, {1, 9, 6, 3}, {5, 9, 1, 9},
			{5, 6, 1, 6}, {5, 3, 1, 3}, {2, 1, 2, 7}, {2, 2, 2, 4}, {2, 3, 2, 1},
			{2, 4, 2, 8}, {2, 5, 2, 5}, {2, 6, 2, 2}, {2, 7, 2, 9}, {2, 8, 2, 6},
			{2, 9, 2, 3}, {-1, -1, -1, -1}
		}
	}, { // 2. left
		{
			{3, 3, 6, 3}, {3, 6, 6, 6}, {3, 9, 6, 9}, {6, 3, 1, 9}, {6, 6, 1, 6},
			{6, 9, 1, 3}, {1, 3, 5, 3}, {1, 6, 5, 6}, {1, 9, 5, 9}, {5, 9, 3, 3},
			{5, 6, 3, 6}, {5, 3, 3, 9}, {2, 1, 2, 3}, {2, 2, 2, 6}, {2, 3, 2, 9},
			{2, 4, 2, 2}, {2, 5, 2, 5}, {2, 6, 2, 8}, {2, 7, 2, 1}, {2, 8, 2, 4},
			{2, 9, 2, 7}, {-1, -1, -1, -1}
		}
	}, { // 3. right
		{
			{2, 3, 6, 3}, {2, 6, 6, 2}, {2, 9, 6, 1}, {6, 3, 4, 9}, {6, 2, 4, 6},
			{6, 1, 4, 3}, {4, 3, 5, 3}, {4, 6, 5, 2}, {4, 9, 5, 1}, {5, 3, 2, 9},
			{5, 2, 2, 6}, {5, 1, 2, 3}, {3, 1, 3, 3}, {3, 2, 3, 6}, {3, 3, 3, 9},
			{3, 4, 3, 2}, {3, 5, 3, 5}, {3, 6, 3, 8}, {3, 7, 3, 1}, {3, 8, 3, 4},
			{3, 9, 3, 7}, {-1, -1, -1, -1}
		}
	}, { // 3. left
		{
			{2, 3, 5, 1}, {2, 6, 5, 2}, {2, 9, 5, 3}, {6, 3, 2, 3}, {6, 2, 2, 6},
			{6, 1, 2, 9}, {4, 3, 6, 1}, {4, 6, 6, 2}, {4, 9, 6, 3}, {5, 3, 4, 3},
			{5, 2, 4, 6}, {5, 1, 4, 9}, {3, 1, 3, 7}, {3, 2, 3, 4}, {3, 3, 3, 1},
			{3, 4, 3, 8}, {3, 5, 3, 5}, {3, 6, 3, 2}, {3, 7, 3, 9}, {3, 8, 3, 6},
			{3, 9, 3, 3}, {-1, -1, -1, -1}
		}
	}, { // 4. right
		{
			{1, 1, 5, 1}, {1, 4, 5, 4}, {1, 7, 5, 7}, {6, 1, 1, 7}, {6, 4, 1, 4},
			{6, 7, 1, 1}, {3, 1, 6, 1}, {3, 4, 6, 4}, {3, 7, 6, 7}, {5, 7, 3, 1},
			{5, 4, 3, 4}, {5, 1, 3, 7}, {4, 1, 4, 3}, {4, 2, 4, 6}, {4, 3, 4, 9},
			{4, 4, 4, 2}, {4, 5, 4, 5}, {4, 6, 4, 8}, {4, 7, 4, 1}, {4, 8, 4, 4},
			{4, 9, 4, 7}, {-1, -1, -1, -1}
		}
	}, { // 4. left
	{	
			{1, 1, 6, 7}, {1, 4, 6, 4}, {1, 7, 6, 1}, {6, 7, 3, 7}, {6, 4, 3, 4},
			{6, 1, 3, 1}, {3, 7, 5, 1}, {3, 4, 5, 4}, {3, 1, 5, 7}, {5, 1, 1, 1},
			{5, 4, 1, 4}, {5, 7, 1, 7}, {4, 1, 4, 7}, {4, 2, 4, 4}, {4, 3, 4, 1},
			{4, 4, 4, 8}, {4, 5, 4, 5}, {4, 6, 4, 2}, {4, 7, 4, 9}, {4, 8, 4, 6},
			{4, 9, 4, 3}, {-1, -1, -1, -1}
		}
	}, { // 5. right
		{
			{1, 3, 4, 1}, {1, 2, 4, 2}, {1, 1, 4, 3}, {2, 3, 1, 3}, {2, 2, 1, 2},
			{2, 1, 1, 1}, {3, 1, 2, 3}, {3, 2, 2, 2}, {3, 3, 2, 1}, {4, 1, 3, 1},
			{4, 2, 3, 2}, {4, 3, 3, 3}, {5, 1, 5, 3}, {5, 2, 5, 6}, {5, 3, 5, 9},
			{5, 4, 5, 2}, {5, 5, 5, 5}, {5, 6, 5, 8}, {5, 7, 5, 1}, {5, 8, 5, 4},
			{5, 9, 5, 7}, {-1, -1, -1, -1}
		}
	}, { // 5. left
		{
			{1, 1, 2, 1}, {1, 2, 2, 2}, {1, 3, 2, 3}, {2, 1, 3, 3}, {2, 2, 3, 2},
			{2, 3, 3, 1}, {3, 3, 4, 3}, {3, 2, 4, 2}, {3, 1, 4, 1}, {4, 3, 1, 1},
			{4, 2, 1, 2}, {4, 1, 1, 3}, {5, 1, 5, 7}, {5, 2, 5, 4}, {5, 3, 5, 1},
			{5, 4, 5, 8}, {5, 5, 5, 5}, {5, 6, 5, 2}, {5, 7, 5, 9}, {5, 8, 5, 6},
			{5, 9, 5, 3}, {-1, -1, -1, -1}
		}
	}, { // 6. right
		{
			{1, 9, 4, 7}, {1, 8, 4, 8}, {1, 7, 4, 9}, {2, 9, 1, 9}, {2, 8, 1, 8},
			{2, 7, 1, 7}, {3, 7, 2, 9}, {3, 8, 2, 8}, {3, 9, 2, 7}, {4, 7, 3, 7},
			{4, 8, 3, 8}, {4, 9, 3, 9}, {6, 1, 6, 3}, {6, 2, 6, 6}, {6, 3, 6, 9},
			{6, 4, 6, 2}, {6, 5, 6, 5}, {6, 6, 6, 8}, {6, 7, 6, 1}, {6, 8, 6, 4},
			{6, 9, 6, 7}, {-1, -1, -1, -1}
		}
	}, { // 6. left
		{
			{1, 7, 2, 7}, {1, 8, 2, 8}, {1, 9, 2, 9}, {2, 7, 3, 9}, {2, 8, 3, 8},
			{2, 9, 3, 7}, {3, 9, 4, 9}, {3, 8, 4, 8}, {3, 7, 4, 7}, {4, 9, 1, 7},
			{4, 8, 1, 8}, {4, 7, 1, 9}, {6, 1, 6, 7}, {6, 2, 6, 4}, {6, 3, 6, 1},
			{6, 4, 6, 8}, {6, 5, 6, 5}, {6, 6, 6, 2}, {6, 7, 6, 9}, {6, 8, 6, 6},
			{6, 9, 6, 3}, {-1, -1, -1, -1}
		}
	}, 
	{
		{
			{6, 8, 3, 8}, {6, 5, 3, 5}, {6, 2, 3, 2}, {3, 8, 5, 2}, {3, 5, 5, 5},
			{3, 2, 5, 8}, {5, 2, 1, 2}, {5, 5, 1, 5}, {5, 8, 1, 8}, {1, 2, 6, 8},
			{1, 5, 6, 5}, {1, 8, 6, 2}, {-1, -1, -1, -1}
		}
	}, 
	{
		{
			{1, 8, 5, 8}, {1, 5, 5, 5}, {1, 2, 5, 2}, {5, 8, 3, 2}, {5, 5, 3, 5},
			{5, 2, 3, 8}, {3, 2, 6, 2}, {3, 5, 6, 5}, {3, 8, 6, 8}, {6, 2, 1, 8},
			{6, 5, 1, 5}, {6, 8, 1, 2}, {-1, -1, -1, -1}
		}
	}, 
	{
		{
			{2, 2, 6, 6}, {2, 5, 6, 5}, {2, 8, 6, 4}, {6, 6, 4, 8}, {6, 5, 4, 5},
			{6, 4, 4, 2}, {4, 8, 5, 4}, {4, 5, 5, 5}, {4, 2, 5, 6}, {5, 4, 2, 2},
			{5, 5, 2, 5}, {5, 6, 2, 8}, {-1, -1, -1, -1}
		}
	}, 
	{
		{
			{2, 8, 5, 6}, {2, 5, 5, 5}, {2, 2, 5, 4}, {5, 6, 4, 2}, {5, 5, 4, 5},
			{5, 4, 4, 8}, {4, 2, 6, 4}, {4, 5, 6, 5}, {4, 8, 6, 6}, {6, 4, 2, 8},
			{6, 5, 2, 5}, {6, 6, 2, 2}, {-1, -1, -1, -1}
		}
	}, 
	{
		{
			{2, 6, 1, 6}, {2, 5, 1, 5}, {2, 4, 1, 4}, {3, 6, 2, 4}, {3, 5, 2, 5}, 
			{3, 4, 2, 6}, {4, 6, 3, 6}, {4, 5, 3, 5}, {4, 4, 3, 4}, {1, 4, 4, 6},
			{1, 5, 4, 5}, {1, 6, 4, 4}, {-1, -1, -1, -1}
		}
	}, 
	{
		{
			{1, 6, 2, 6}, {1, 5, 2, 5}, {1, 4, 2, 4}, {2, 4, 3, 6}, {2, 5, 3, 5}, 
			{2, 6, 3, 4}, {3, 6, 4, 6}, {3, 5, 4, 5}, {3, 4, 4, 4}, {4, 6, 1, 4},
			{4, 5, 1, 5}, {4, 4, 1, 6}, {-1, -1, -1, -1}
		}
	}
};

CubeTransform::CubeTransform(void)
{
	rotated = 0;
	showRotating = 0;
}

void CubeTransform::cTransformN(int n)
{
	char retval[6];
	switch(n)
	{
		case 0: sprintf(retval, "1j"); break;
		case 1: sprintf(retval, "1b"); break;
		case 2: sprintf(retval, "2j"); break;
		case 3: sprintf(retval, "2b"); break;
		case 4: sprintf(retval, "3j"); break;
		case 5: sprintf(retval, "3b"); break;
		case 6: sprintf(retval, "4j"); break;
		case 7: sprintf(retval, "4b"); break;
		case 8: sprintf(retval, "5j"); break;
		case 9: sprintf(retval, "5b"); break;
		case 10: sprintf(retval, "6j"); break;
		case 11: sprintf(retval, "6b"); break;
		case 12: sprintf(retval, "7j"); break;
		case 13: sprintf(retval, "7b"); break;
		case 14: sprintf(retval, "8j"); break;
		case 15: sprintf(retval, "8b"); break;
		case 16: sprintf(retval, "9j"); break;
		case 17: sprintf(retval, "9b"); break;
	}
	cTransform(retval);
}

void CubeTransform::setRotated(int rot) 
{
	rotated = rot;
}

int CubeTransform::getRotated() 
{
	return rotated;
}

void CubeTransform::startRotating() 
{
	showRotating = 1;
}

void CubeTransform::stopRotating() 
{
	showRotating = 0;
}

int CubeTransform::getRotating() 
{
	return showRotating;
}

void CubeTransform::cTransform(char *id)
{
	if(!showRotating) getRubikCube()->cAddQueue(id);

	CubeModel tempCube;

	int transid=-1;
	if(strcmp(id, "1j") == 0) transid = 0;
	else if(strcmp(id, "1b") == 0) transid = 1;
	else if(strcmp(id, "2j") == 0) transid = 2;
	else if(strcmp(id, "2b") == 0) transid = 3;
	else if(strcmp(id, "3j") == 0) transid = 4;
	else if(strcmp(id, "3b") == 0) transid = 5;
	else if(strcmp(id, "4j") == 0) transid = 6;
	else if(strcmp(id, "4b") == 0) transid = 7;
	else if(strcmp(id, "5j") == 0) transid = 8;
	else if(strcmp(id, "5b") == 0) transid = 9;
	else if(strcmp(id, "6j") == 0) transid = 10;
	else if(strcmp(id, "6b") == 0) transid = 11;
	else if(strcmp(id, "7j") == 0) transid = 12;
	else if(strcmp(id, "7b") == 0) transid = 13;
	else if(strcmp(id, "8j") == 0) transid = 14;
	else if(strcmp(id, "8b") == 0) transid = 15;
	else if(strcmp(id, "9j") == 0) transid = 16;
	else if(strcmp(id, "9b") == 0) transid = 17;

	if(showRotating == 1) 
	{	
		getRubikCube()->rotateColorSide(transid);
	}
	
	CubeModel* cube = getCube();

	int side, cellId;
	for(side=1; side!=7; side++) {
		for(cellId=1; cellId!=10; cellId++) {
			tempCube.SetCellColor(side, cellId, cube->GetCellColor(side, cellId));
		}
	}

	int i=0;
	int tside, tplace, sside, splace;
	while(cubeTransform[transid].steps[i].target_side != -1)
	{
		if(cubeTransform[transid].steps[i].target_side != -1)
		{
			tside = cubeTransform[transid].steps[i].target_side;
			tplace = cubeTransform[transid].steps[i].target_place;
			sside = cubeTransform[transid].steps[i].source_side;
			splace = cubeTransform[transid].steps[i].source_place;

			cube->SetCellColor(tside, tplace, tempCube.GetCellColor(sside, splace));
		}
		i++;
	}
}

