#pragma once

#ifndef _CUBEMODEL_H_INCLUDED_
#define _CUBEMODEL_H_INCLUDED_

#include "CubeTransform.h"

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
		CubeTransform* getTransformEngine(void);
		~CubeModel(void);

	private: 
		CubeColor cubeColors[7][10];
		CubeTransform* transformEngine;
};

#endif
