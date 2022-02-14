#include "CardTwo.h"
#include "Ladder.h"
CardTwo::CardTwo(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 2; // set the inherited cardNumber data member with the card number (2 here)
}

CardTwo::~CardTwo(void)
{
}

void CardTwo::Apply(Grid* pGrid, Player* pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid, pPlayer);
	//2- Get the player's current position
	Cell* currentCell = pPlayer->GetCell();
	CellPosition currentPos = currentCell->GetCellPosition();
	//3- Check Where the next ladder is on the grid
	Ladder* nextladder = pGrid->GetNextLadder(currentPos);
	//4- Move the player to the next Ladder if there is one
	if (nextladder) {
		pGrid->UpdatePlayerCell(pPlayer, nextladder->GetEndPosition());
	}
	else if (!nextladder) {
		pOut->PrintMessage("No Ladders Ahead! You will remain in your Cell Click to Continue...");
		int x, y;
		pIn->GetPointClicked(x, y);
	}
	pOut->ClearStatusBar();
}
void CardTwo::Draw(Output* pOut) {
	Card::Draw(pOut);
}
void CardTwo::Save(ofstream& OutFile, Grid* pGrid, int typ) {
	Card::Save(OutFile, pGrid, typ);
	OutFile << endl;
}
CardTwo* CardTwo::Load(ifstream& InFile, Grid* pGrid, int typ) {
	CardTwo* pLoaded = NULL;
	int CellPos;
	InFile >> CellPos;
	CellPosition Cardposition(CellPos);
	pLoaded = new CardTwo(Cardposition);
	pGrid->AddObjectToCell(pLoaded);
	return pLoaded;
}
Card* CardTwo::GetCopy() {
	return new CardTwo(0);
}