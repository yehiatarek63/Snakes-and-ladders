#include "CardEight.h"

CardEight::CardEight(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 8;
}

CardEight::~CardEight(void)
{
}
void CardEight::setcoinsneededtogo(int x) {    //set fees that the player pay to go out of prison
	coinsneedtedogo = x;
}
int CardEight::getcoinsneededtogo() {     //get fees that the player pay to go out of prison
	return coinsneedtedogo;
}
void CardEight::ReadCardParameters(Grid* pGrid)
{
	Input* pin = pGrid->GetInput();
	Output* pout = pGrid->GetOutput();
	pout->PrintMessage("Enter Amount to Get Freed: ");
	int x = pin->GetInteger(pout);         //read the fees form user in design mode and set it
	setcoinsneededtogo(x);
	pout->ClearStatusBar();
}

void CardEight::Apply(Grid* pGrid, Player* pPlayer)
{
	Input* pin = pGrid->GetInput();
	Output* pout = pGrid->GetOutput();
	pout->PrintMessage("Make Your choice... (1) To stay in prison OR (2) To pay fees then go free...");  //get the choice of player as input
	int x = pin->GetInteger(pout);
	pout->ClearStatusBar();
	switch (x)
	{
	case 1:
		pPlayer->setmoveability(0);   //if he choose to stay prison so we set the move ability to false
		break;
	case 2:
		if (pPlayer->GetWallet() - getcoinsneededtogo() >= 0) {					//if he choose to pay the fees then remove it form has wallet
			pPlayer->SetWallet(pPlayer->GetWallet() - getcoinsneededtogo());
		}
		else {
			pout->PrintMessage("No Money Sir ^_^ click to continue...");    //print this message if the player donot have the price
			int x, y;
			pin->GetPointClicked(x, y);
		}
		break;
	default:
		break;
	}
}

void CardEight::Save(ofstream& OutFile, Grid* pGrid, int typ) {
	Card::Save(OutFile, pGrid, typ);
	OutFile << getcoinsneededtogo() << endl;
}

Card* CardEight::GetCopy() {
	CardEight* CardEightCopy = new CardEight(0);
	CardEightCopy->setcoinsneededtogo(getcoinsneededtogo());
	return CardEightCopy;
}

CardEight* CardEight::Load(ifstream& InFile, Grid* pGrid, int typ) {
	CardEight* pLoaded = NULL;
	int CellPos;
	InFile >> CellPos;
	CellPosition Cardposition(CellPos);
	pLoaded = new CardEight(Cardposition);
	int coins;
	InFile >> coins;
	pLoaded->setcoinsneededtogo(coins);
	pGrid->AddObjectToCell(pLoaded);
	return pLoaded;
}