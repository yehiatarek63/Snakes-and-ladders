#include "InputDice.h"
InputDice::InputDice(ApplicationManager* pApp) : Action(pApp) {
	pManager = pApp;
};
InputDice::~InputDice() {};
void InputDice::ReadActionParameters() {
	Grid* pGrid = pManager->GetGrid();
	Input* pin = pGrid->GetInput();
	Output* pout = pGrid->GetOutput();
	pout->PrintMessage("Enter a Dice value: ");
	DiceNumber=pin->GetInteger(pout);
	while (DiceNumber < 0 || DiceNumber > 6) { //Validation on the entered Number
		pout->PrintMessage("Please Enter a Number From 1 to 6: ");
		DiceNumber = pin->GetInteger(pout);
	}
	pout->ClearStatusBar();
}
void InputDice::Execute() {
	ReadActionParameters();
	Player* pPlayer;
	Grid* pGrid = pManager->GetGrid();
	pPlayer = pGrid->GetCurrentPlayer();
	pPlayer->Move(pGrid, DiceNumber);
	pGrid->AdvanceCurrentPlayer();
};