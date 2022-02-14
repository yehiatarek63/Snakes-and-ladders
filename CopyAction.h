#pragma once
#include "Action.h"

class CopyAction : public Action
{
	// [Action Parameters]
	CellPosition pos;

public:
	CopyAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads action parameters

	virtual void Execute();

	virtual ~CopyAction(); // A Virtual Destructor
};
