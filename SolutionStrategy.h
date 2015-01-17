#pragma once

#ifndef _STRATEGY_H_INCLUDED_
#define _STRATEGY_H_INCLUDED_

class SolutionStrategy
{
	public:
		int run();

	private: 
		void solvePhase5();
		void solvePhase6();
		void solvePhase7();

		double sarokChkSum(int num);
		double sarokPosChkSum(int num);

		int compareColors(int side1, int place1, int side2, int place2);
};

#endif