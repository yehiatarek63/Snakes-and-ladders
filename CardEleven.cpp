#include "CardEleven.h"
#include <iostream>
using namespace std;
int CardEleven::fees = 0;
int CardEleven::price = 0;
bool CardEleven::owned = 0;
Player* CardEleven::owner = NULL;
CardEleven::CardEleven(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 11; // set the inherited cardNumber data member with the card number (1 here)
	type = 3;
}
bool CardEleven::setfees(int x) {
	if (x > 0) {
		fees = x;
		return true;
	}
	return false;
}
int CardEleven::getfees() {
	return fees;
}
void CardEleven::setowner(Player* p) {
	owner = p;
}
Player* CardEleven::getowner() {
	if (owner == NULL) {
		return NULL;
	}
	return owner;
}
bool CardEleven::setprice(int x) {
	if (x > 0) {
		price = x;
		return true;
	}
	return false;
}
int CardEleven::getprice() {
	return price;
}
CardEleven::~CardEleven() {

}
void CardEleven::setown(bool x) {   // set the bool which refers that card has owner or no
	owned = x;
}
bool CardEleven::getown() {    //get the bool which used to check if card has owner or not
	return owned;
}
void CardEleven::ReadCardParameters(Grid* pGrid) {
	Input* pin = pGrid->GetInput();
	Output* pout = pGrid->GetOutput();
	if (getfees() == 0 && getprice() == 0) {
		pout->PrintMessage("Enter the Fees of Card: ");
		int x = pin->GetInteger(pout);
		setfees(x);
		while (setfees(x) == 0) {
			pout->PrintMessage("Invalid! Please Enter a Positive Number: ");
			x = pin->GetInteger(pout);
			setfees(x);
		}
		pout->PrintMessage("Enter the Price of Card: ");
		int y = pin->GetInteger(pout);
		setprice(y);
		while (setprice(y) == 0) {
			pout->PrintMessage("Invalid! Please Enter a Positive Number: ");
			y = pin->GetInteger(pout);
			setprice(y);
		}
		pGrid->GetOutput()->ClearStatusBar();
	}
}
void CardEleven::Apply(Grid* pGrid, Player* pPlayer) {
	Input* pin = pGrid->GetInput();
	Output* pout = pGrid->GetOutput();
	string cost = std::to_string(getprice());
	if (getown() == 1) {   //if card has owner 
		pout->PrintMessage("You Stepped on a Property, You will be charged " + cost + " Click To Continue...");
		int x, y;
		pin->GetPointClicked(x, y);
		pout->ClearStatusBar();
		if (pPlayer->gettheownership(11) == 0) {
			if ((pPlayer->GetWallet() - getfees()) < 0)  
				pPlayer->SetWallet(0);
			else {
				pPlayer->SetWallet(pPlayer->GetWallet() - getfees());    // if he has fess then remove it form its wallet and add it to owner wallet
			}
			getowner()->SetWallet(getowner()->GetWallet() + getfees());
		}
	}
	else {
		pout->PrintMessage("You have Entered a Property, Cost = " + cost + "... Enter 1 to Buy/Enter 2 to Dismiss");
		int x = pin->GetInteger(pout);
		if (x == 1) {
			if ((pPlayer->GetWallet() - getprice()) > 0) {   
				pPlayer->SetWallet(pPlayer->GetWallet() - getprice());
				setown(1);
				pPlayer->setownership(11, 1);  //here we give the ownership of card11 to player
				setowner(pPlayer);
			}
			else {
				pout->PrintMessage("No Enough money :( Click to Continue...");  //print this if player didnot have price
			}
		}
	}
	pout->ClearStatusBar();
}
void CardEleven::Save(ofstream& OutFile, Grid* pGrid, int typ) {
	Card::Save(OutFile, pGrid, typ);
	OutFile << fees << " " << price << endl;
}

Card* CardEleven::GetCopy() {
	CardEleven* CardElevenCopy = new CardEleven(0);
	CardElevenCopy->setowner(getowner());
	CardElevenCopy->setfees(getfees());
	CardElevenCopy->setprice(getprice());
	CardElevenCopy->setown(getown());
	return CardElevenCopy;
}

void CardEleven::Reset() {
	getowner()->setownership(11, false);
	setown(false);
	setowner(NULL);
}


CardEleven* CardEleven::Load(ifstream& InFile, Grid* pGrid, int typ) {
	CardEleven* pLoaded = NULL;
	int CellPos;
	InFile >> CellPos;
	CellPosition Cardposition(CellPos);
	pLoaded = new CardEleven(Cardposition);
	int fees;
	InFile >> fees;
	pLoaded->setfees(fees);
	int price;
	InFile >> price;
	pLoaded->setprice(price);
	pGrid->AddObjectToCell(pLoaded);
	return pLoaded;
}