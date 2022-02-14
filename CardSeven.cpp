#include "CardSeven.h"

CardSeven::CardSeven(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	type = 3;
	cardNumber = 7; // set the inherited cardNumber data member with the card number (1 here)
}

CardSeven::~CardSeven(void)
{
}

void CardSeven::ReadCardParameters(Grid* pGrid)
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==


	// 1- Get a Pointer to the Input / Output Interfaces from the Grid

	// 2- Read an Integer from the user using the Input class and set the walletAmount parameter with it




	// 3- Clear the status bar


}
void CardSeven::Apply(Grid* pGrid, Player* pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	int x, y;
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	Card::Apply(pGrid, pPlayer);
	Player* NextPlayer = pGrid->GetClosestPlayer();
	CellPosition pos(8, 0); //Cellposition of cell number 1
	if (NextPlayer != NULL) {
		pGrid->UpdatePlayerCell(NextPlayer, pos); // Updates the cell of player
		NextPlayer->SetstepCount(1); //updates the step count to cell num 1
	}
	else {
		pOut->PrintMessage("No Players ahead, Click to continue "); //if nextplayer equal null this message will be printed
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
	}
	NextPlayer = NULL;
}

void CardSeven::Save(ofstream& OutFile, Grid* pGrid, int typ) {
	Card::Save(OutFile, pGrid, typ);
	OutFile << endl;
}

CardSeven* CardSeven::Load(ifstream& InFile, Grid* pGrid, int typ) {
	CardSeven* pLoaded = NULL;
	int CellPos;
	InFile >> CellPos;
	CellPosition Cardposition(CellPos);
	pLoaded = new CardSeven(Cardposition);
	pGrid->AddObjectToCell(pLoaded);
	return pLoaded;
}

Card* CardSeven::GetCopy() {
	return new CardSeven(0);
}