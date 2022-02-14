#include "CardFive.h"
#include "Cell.h"
#include "Ladder.h"
#include "Snake.h"
CardFive::CardFive(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	type = 3;
	cardNumber = 5; // set the inherited cardNumber data member with the card number (1 here)
}

CardFive::~CardFive(void)
{
}

void CardFive::ReadCardParameters(Grid* pGrid)
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==


	// 1- Get a Pointer to the Input / Output Interfaces from the Grid

	// 2- Read an Integer from the user using the Input class and set the walletAmount parameter with it
	//    Don't forget to first print to a descriptive message to the user like:"New CardOne: Enter its wallet amount ..."


	// [ Note ]:
	// In CardOne, the only parameter of CardOne is the "walletAmount" value to decrease from player
	// Card parameters are the inputs you need to take from the user in the time of adding the Card in the grid
	// to be able to perform his Apply() action

	// 3- Clear the status bar



}

void CardFive::Apply(Grid* pGrid, Player* pPlayer)
{

	Card::Apply(pGrid, pPlayer); //Apply function of base card class
	CellPosition Pos = pPlayer->GetCell()->GetCellPosition(); //gets cell position of the current player
	Pos.AddCellNum(pPlayer->getjustrolleddicenumber() * -1); //Updates the cell position by adding the negative rolled dice using add cell num
	pGrid->UpdatePlayerCell(pPlayer, Pos); //updates player cell using updated Pos
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
	}
} // apply the effects of game objects after updating


void CardFive::Save(ofstream& OutFile, Grid* pGrid, int typ) {
	Card::Save(OutFile, pGrid, typ);
	OutFile << endl;
}

CardFive* CardFive::Load(ifstream& InFile, Grid* pGrid, int typ) {
	CardFive* pLoaded = NULL;
	int CellPos;
	InFile >> CellPos;
	CellPosition Cardposition(CellPos);
	pLoaded = new CardFive(Cardposition);
	pGrid->AddObjectToCell(pLoaded);
	return pLoaded;
}
Card* CardFive::GetCopy() {
	return new CardFive(0);
}