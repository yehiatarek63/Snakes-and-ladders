#include "CardSix.h"
#include "Ladder.h"
#include "Snake.h"

CardSix::CardSix(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	type = 3;
	cardNumber = 6; // set the inherited cardNumber data member with the card number (1 here)
}

CardSix::~CardSix(void)
{
}

void CardSix::ReadCardParameters(Grid* pGrid)
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==


	// 1- Get a Pointer to the Input / Output Interfaces from the Grid

	// 2- Read an Integer from the user using the Input class and set the cellnum parameter with it
	//    Don't forget to first print to a descriptive message to the user like:"New CardSix: Input cell to move to ..."


	// [ Note ]:
	// In CardSix, the only parameter of CardSix is the "cellNum" value to move player to
	// Card parameters are the inputs you need to take from the user in the time of adding the Card in the grid
	// to be able to perform his Apply() action

	// 3- Clear the status bar
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("New CardSix: Input Cell to move to: ");
	cellNum = pIn->GetInteger(pOut); //puts entered cell number in cellnum variable
	pOut->ClearStatusBar();
}

void CardSix::Apply(Grid* pGrid, Player* pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	// 1- Call Apply() of the base class Card to print the message that you reached this card number

	// 2- move player to entered cell num
	Card::Apply(pGrid, pPlayer);
	CellPosition* pos;
	pos->GetCellPositionFromNum(cellNum); // uses a pointer to get cell position from cell num
	pGrid->UpdatePlayerCell(pPlayer, pos->GetCellPositionFromNum(cellNum)); // updates cell position from above line
	if (pPlayer->GetCell()->HasLadder() != NULL) {
		Ladder* L = pPlayer->GetCell()->HasLadder();
		L->Apply(pGrid, pPlayer);
	}
	if (pPlayer->GetCell()->HasCard() != NULL) {
		Card* C = pPlayer->GetCell()->HasCard();
		C->Apply(pGrid, pPlayer);
	}
	if (pPlayer->GetCell()->HasSnake() != NULL) {
		Snake* S = pPlayer->GetCell()->HasSnake();
		S->Apply(pGrid, pPlayer);
	} // apply the effects of the game object

}

void CardSix::Save(ofstream& OutFile, Grid* pGrid, int typ) {
	Card::Save(OutFile, pGrid, typ);
	OutFile << cellNum << endl;
}

CardSix* CardSix::Load(ifstream& InFile, Grid* pGrid, int typ) {
	CardSix* pLoaded = NULL;
	int CellPos;
	InFile >> CellPos;
	CellPosition Cardposition(CellPos);
	pLoaded = new CardSix(Cardposition);
	int cellnumber;
	InFile >> cellnumber;
	pLoaded->SetcellNum(cellnumber);
	pGrid->AddObjectToCell(pLoaded);
	return pLoaded;
}

Card* CardSix::GetCopy() {
	CardSix* CardSixCopy = new CardSix(0);
	CardSixCopy->SetcellNum(getcellNum());
	return CardSixCopy;
}

void CardSix::SetcellNum(int c) {
	cellNum = c;
}
int CardSix::getcellNum() const{
	return cellNum;
}