#pragma once
#include "Action.h"
#include "Grid.h"
class SwitchToDesign :public Action
{


public:
	SwitchToDesign(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~SwitchToDesign();
};