#include "CardTen.h"
#include <iostream>
using namespace std;
int CardTen::fees = 0;
int CardTen::price = 0;
bool CardTen::owned = 0;
Player* CardTen::owner = NULL;
CardTen::CardTen(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 10; // set the inherited cardNumber data member with the card number (1 here)
	type = 3;
}
bool CardTen::setfees(int x) {
	if (x > 0) {   //set the fees with validtion if fees is +ve number will set it and return true , if not return false and fees stay = 0
		fees = x;
		return true;
	}
	return false;
}
int CardTen::getfees() {
	return fees;
}
void CardTen::setowner(Player* p) {
	owner = p;   //set a pointer of type player which refers to player who had bought the card
}
Player* CardTen::getowner() {
	if (owner == NULL) {
		return NULL;    //get a pointer of type player which refers to player who had bought the card, card donot have owner return NULL
	}
	return owner;
}
bool CardTen::setprice(int x) {
	if (x > 0) {
		price = x;
		return true; //set the price with validtion if price is +ve number will set it and return true , if not return false and price stay = 0
	}
	return false;
}
int CardTen::getprice() {
	return price;
}
CardTen::~CardTen() {

}
void CardTen::setown(bool x) {
	owned = x; //set the price with validtion if price is +ve number will set it and return true , if not return false and price stay = 0
}
bool CardTen::getown() {   //get the bool which used to check if card has owner or not
	return owned;
}
void CardTen::ReadCardParameters(Grid* pGrid) {
	Input* pin = pGrid->GetInput();
	Output* pout = pGrid->GetOutput();
	if (getfees() == 0 && getprice() == 0) {  //read input (fees.price) with valition by while loop
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
void CardTen::Apply(Grid* pGrid, Player* pPlayer) {
	Input* pin = pGrid->GetInput();
	Output* pout = pGrid->GetOutput();
	string cost = std::to_string(getprice());
	if (getown() == 1) {  //if card has owner 
		pout->PrintMessage("You Stepped on a Property, You will be charged " + cost + " Click To Continue");
		int x, y;
		pin->GetPointClicked(x, y);
		pout->ClearStatusBar();
		if (pPlayer->gettheownership(10) == 0) {
			if ((pPlayer->GetWallet() - getfees()) < 0)//check the player has fees in his wallet if not set his wallet to 0 
				pPlayer->SetWallet(0);
			else {
				pPlayer->SetWallet(pPlayer->GetWallet() - getfees());  // if he has fess then remove it form its wallet and add it to owner wallet
			}
			getowner()->SetWallet(getowner()->GetWallet() + getfees());
		}
	}
	else {
		pout->PrintMessage("You have Entered a Property, Cost = " + cost + "... Enter 1 to Buy/Enter 2 to Dismiss");  //print message and get answer as input form user
		int x = pin->GetInteger(pout);
		if (x == 1) {     
			if ((pPlayer->GetWallet() - getprice()) > 0) {     //check the player who want to buy the card if he has the price or not
				pPlayer->SetWallet(pPlayer->GetWallet() - getprice());
				setown(1);
				pPlayer->setownership(10, 1);  //here we give the ownership of card10 to player
				setowner(pPlayer);
			}
			else {
				pout->PrintMessage("No Enough money :( Click to Continue...");   //print this if player didnot have price
			}
		}
	}
	pout->ClearStatusBar();
}

Card* CardTen::GetCopy() {
	CardTen* CardTenCopy = new CardTen(0);
	CardTenCopy->setowner(getowner());
	CardTenCopy->setfees(getfees());
	CardTenCopy->setprice(getprice());
	CardTenCopy->setown(getown());
	return CardTenCopy;
}

void CardTen::Reset() {
	getowner()->setownership(10, false);
	setown(false);
	setowner(NULL);
}

void CardTen::Save(ofstream& OutFile, Grid* pGrid, int typ) {
	Card::Save(OutFile, pGrid, typ);
	OutFile << fees << " " << price << endl;
}

CardTen* CardTen::Load(ifstream& InFile, Grid* pGrid, int typ) {
	CardTen* pLoaded = NULL;
	int CellPos;
	InFile >> CellPos;
	CellPosition Cardposition(CellPos);
	pLoaded = new CardTen(Cardposition);
	int fees;
	InFile >> fees;
	pLoaded->setfees(fees);
	int price;
	InFile >> price;
	pLoaded->setprice(price);
	pGrid->AddObjectToCell(pLoaded);
	return pLoaded;
}