#pragma once

#include <algorithm>

class CubeModel
{
	public:
		struct CubeColor
		{
			double Red;
			double Green;
			double Blue;
		};

		CubeModel(void);
		void DefaultColors();
		void SetCellColor(int side, int cellId, const CubeColor color);
		CubeColor GetCellColor(int side, int cellId);
		~CubeModel(void);

	private: 
		CubeColor cubeColors[7][10];
};

