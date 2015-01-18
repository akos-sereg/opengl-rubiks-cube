#pragma once

#ifndef _STRATEGY_H_INCLUDED_
#define _STRATEGY_H_INCLUDED_

class SolutionStrategy
{
	public:
		SolutionStrategy(RuleEngine* engine);
		int run();

	private:
		RuleEngine* ruleEngine;
};

#endif