#pragma once
#include "Action.h"
#include "Grid.h"
#include "Player.h"

class InputDice : public Action
{

	int DiceNumber;

public:
	InputDice(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~InputDice();
};
