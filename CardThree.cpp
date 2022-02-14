#include "CardThree.h"
#include "ApplicationManager.h"
CardThree::CardThree(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 3; // set the inherited cardNumber data member with the card number (1 here)
}
CardThree::~CardThree(void)
{
}
void CardThree::Apply(Grid* pGrid, Player* pPlayer) 
{
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	
	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==
	Output* pOut = pGrid->GetOutput();
	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid, pPlayer);
	// 2- Get the current player
	pPlayer = pGrid->GetCurrentPlayer();
	//3- Generate Random
	int diceNumber = 1 + rand() % 6;
	//4- Move the Player
	pPlayer->Move(pGrid, diceNumber);

}
void CardThree::Save(ofstream& OutFile, Grid* pGrid, int typ) {
	Card::Save(OutFile, pGrid, typ);
	OutFile << endl;
}
CardThree* CardThree::Load(ifstream& InFile, Grid* pGrid, int typ) {
	CardThree* pLoaded = NULL;
	int CellPos;
	InFile >> CellPos;
	CellPosition Cardposition(CellPos);
	pLoaded = new CardThree(Cardposition);
	pGrid->AddObjectToCell(pLoaded);
	return pLoaded;
}

Card* CardThree::GetCopy() {
	return new CardThree(0);
}