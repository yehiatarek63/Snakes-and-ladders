#pragma once
#include "Action.h"
#include "Grid.h"
class SwitchToPlay :public Action
{


public:
	SwitchToPlay(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~SwitchToPlay();
};


