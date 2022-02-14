#include "CardNine.h"
#include <iostream>
using namespace std;
 int CardNine:: fees=0;
 int CardNine:: price=0;
 bool CardNine:: owned=0;
 Player* CardNine::owner=NULL;
 CardNine::CardNine(const CellPosition& pos) : Card(pos) // set the cell position of the card
 {
	 cardNumber = 9; // set the inherited cardNumber data member with the card number (1 here)
	 type = 3;
 }
bool CardNine::setfees(int x) {
	if (x > 0) {
		fees = x;					//set the fees with validtion if fees is +ve number will set it and return true , if not return false and fees stay = 0
		return true;
	}
	return false;
}
int CardNine::getfees() {
	return fees;
}
void CardNine::setowner(Player* p) {
	owner = p;        //set a pointer of type player which refers to player who had bought the card
}
Player* CardNine::getowner() {
	if (owner == NULL) {
		return NULL;				 //get a pointer of type player which refers to player who had bought the card, card donot have owner return NULL
	}
	return owner;
}
bool CardNine::setprice(int x) {
	if (x > 0) {
		price = x;						//set the price with validtion if price is +ve number will set it and return true , if not return false and price stay = 0
		return true;
	}
	return false;
}
int CardNine::getprice() {
	return price;    //return price
}
CardNine::~CardNine() {    

}  //empty destructor
void CardNine::setown(bool x) {		// set the bool which refers that card has owner or no
	owned = x;					
}		
bool CardNine::getowned() {  //get the bool which used to check if card has owner or not
	return owned;
}
void CardNine::ReadCardParameters(Grid* pGrid) {
	Input* pin = pGrid->GetInput();
	Output* pout = pGrid->GetOutput();     //read input (fees.price) with valition by while loop
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
void CardNine::Apply(Grid* pGrid, Player* pPlayer) {
	Input* pin = pGrid->GetInput();
	Output* pout = pGrid->GetOutput();
	string cost = std::to_string(getprice());
	if (getowned() == 1) {    //if card has owner 
		pout->PrintMessage("You Stepped on a Property, You will be charged " + cost + " Click To Continue");
		int x, y;
		pin->GetPointClicked(x, y);
		pout->ClearStatusBar();
		if (pPlayer->gettheownership(9) == 0) {
			if ((pPlayer->GetWallet() - getfees()) < 0)			//check the player has fees in his wallet if not set his wallet to 0 
				pPlayer->SetWallet(0);
			else {
				pPlayer->SetWallet(pPlayer->GetWallet() - getfees()); // if he has fess then remove it form its wallet and add it to owner wallet
			}
			getowner()->SetWallet(getowner()->GetWallet() + getfees());
		}
	}
	else {       // if card donot have owner
		pout->PrintMessage("You have Entered a Property, Cost = " + cost + "... Enter 1 to Buy/Enter 2 to Dismiss");  //print message and get answer as input form user
		int x = pin->GetInteger(pout);
		if (x == 1) {
			if ((pPlayer->GetWallet() - getprice()) > 0) {   //check the player who want to buy the card if he has the price or not
				pPlayer->SetWallet(pPlayer->GetWallet() - getprice());
				setown(1);   //set the bool
				pPlayer->setownership(9, 1);  //here we give the ownership of card9 to player
				setowner(pPlayer); //set the owner of card
			}
			else {
				pout->PrintMessage("No Enough money :( Click to Continue...");   //print this if player didnot have price
			}
		}
	}
	pout->ClearStatusBar();
}

Card* CardNine::GetCopy() {
	CardNine* CardNineCopy = new CardNine(0);
	CardNineCopy->setowner(getowner());
	CardNineCopy->setfees(getfees());
	CardNineCopy->setprice(getprice());
	CardNineCopy->setown(getowned());
	return CardNineCopy;
}

void CardNine::Reset() {
	getowner()->setownership(9,false);
	setown(false);
	setowner(NULL);
}

void CardNine::Save(ofstream& OutFile, Grid* pGrid, int typ) {
	Card::Save(OutFile, pGrid, typ);
	OutFile << fees << " " << price << endl;
}

CardNine* CardNine::Load(ifstream& InFile, Grid* pGrid, int typ) {
	CardNine* pLoaded = NULL;
	int CellPos;
	InFile >> CellPos;
	CellPosition Cardposition(CellPos);
	pLoaded = new CardNine(Cardposition);
	int fees;
	InFile >> fees;
	pLoaded->setfees(fees);
	int price;
	InFile >> price;
	pLoaded->setprice(price);
	pGrid->AddObjectToCell(pLoaded);
	return pLoaded;
}