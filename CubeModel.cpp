#include "CubeModel.h"

CubeModel::CubeModel(void)
{
}

void CubeModel::SetCellColor(int side, int cellId, const CubeColor color) 
{
	CubeColor* existingColor = &cubeColors[side][cellId];
	existingColor->Red = color.Red;
	existingColor->Green = color.Green;
	existingColor->Blue = color.Blue;
}

CubeModel::CubeColor CubeModel::GetCellColor(int side, int cellId) 
{
	return cubeColors[side][cellId];
}

void CubeModel::DefaultColors()
{
	int i;

	// Reset cube
	for(i=1; i!=10; i++) { cubeColors[1][i].Red=1.0; cubeColors[1][i].Green=0.0; cubeColors[1][i].Blue=0.0; }
	for(i=1; i!=10; i++) { cubeColors[2][i].Red=0.0; cubeColors[2][i].Green=0.0; cubeColors[2][i].Blue=1.0; }
	for(i=1; i!=10; i++) { cubeColors[3][i].Red=1.0; cubeColors[3][i].Green=0.5; cubeColors[3][i].Blue=0.0; }
	for(i=1; i!=10; i++) { cubeColors[4][i].Red=0.0; cubeColors[4][i].Green=1.0; cubeColors[4][i].Blue=0.0; }
	for(i=1; i!=10; i++) { cubeColors[5][i].Red=1.0; cubeColors[5][i].Green=1.0; cubeColors[5][i].Blue=1.0; }
	for(i=1; i!=10; i++) { cubeColors[6][i].Red=1.0; cubeColors[6][i].Green=1.0; cubeColors[6][i].Blue=0.0; }
}

CubeModel::~CubeModel(void)
{
}
