#include "CardTwelve.h"

CardTwelve::CardTwelve(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 12; // set the inherited cardNumber data member with the card number (1 here)
}

CardTwelve::~CardTwelve(void)
{
}

void CardTwelve::ReadCardParameters(Grid* pGrid)
{

}

void CardTwelve::Apply(Grid* pGrid, Player* pPlayer)
{
	Player* PlayerThatHasLowWallet = Player::GetPlayerThatHasLowWallet();
	int c9 = 0, c10 = 0, c11 = 0;
	bool card9 =pPlayer->gettheownership(9);
	bool card10 = pPlayer->gettheownership(10);
	bool card11 = pPlayer->gettheownership(11);
	Input* pin = pGrid->GetInput();
	Output* pout = pGrid->GetOutput();
	if (card9)
		c9 = CardNine::getprice();
	if (card10)
		c10 = CardTen::getprice();
	if (card11)
		c11 = CardEleven::getprice();
	if (PlayerThatHasLowWallet != NULL&& PlayerThatHasLowWallet!=pPlayer) {
		if (c9 > c11 && c9 > c10) {
			pPlayer->setownership(9,0);
			CardNine::setowner(NULL);
			CardNine::setowner(PlayerThatHasLowWallet);
			PlayerThatHasLowWallet->setownership(9, 1);
			pout->PrintMessage("Another player has Card 9! Click To Continue...");
		}
		else if (c10 > c11 && c10 > c9) {
			pPlayer->setownership(10, 0);
			CardTen::setowner(NULL);
			CardTen::setowner(PlayerThatHasLowWallet);
			PlayerThatHasLowWallet->setownership(10, 1);
			pout->PrintMessage("Another player has Card 10! Click To Continue...");
		}
		else if (c11 > c10 && c11 > c9)
		{
			pPlayer->setownership(11, 0);
			CardEleven::setowner(NULL);
			CardEleven::setowner(PlayerThatHasLowWallet);
			PlayerThatHasLowWallet->setownership(11, 1);
			pout->PrintMessage("Another player has Card 11! Click To Continue...");
		}
		else if (c9 == 0 && c10 == 0 && c11 == 0) {
			pout->PrintMessage("You do not have any cards! Click To Continue...");
		}
	}
	else
	{
		pout->PrintMessage("You have the lowest wallet");
	}
	int x, y;
	pin->GetPointClicked(x, y);
	pout->ClearStatusBar();
}
void CardTwelve::Save(ofstream& OutFile, Grid* pGrid, int typ) {
	Card::Save(OutFile, pGrid, typ);
	OutFile << endl;
}
CardTwelve* CardTwelve::Load(ifstream& InFile, Grid* pGrid, int typ) {
	CardTwelve* pLoaded = NULL;
	int CellPos;
	InFile >> CellPos;
	CellPosition Cardposition(CellPos);
	pLoaded = new CardTwelve(Cardposition);
	pGrid->AddObjectToCell(pLoaded);
	return pLoaded;
}
Card* CardTwelve::GetCopy() {
	return new CardTwelve(0);
}