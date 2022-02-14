#include "CardOne.h"

CardOne::CardOne(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 1; // set the inherited cardNumber data member with the card number (1 here)
	type = 3; //card
}

CardOne::~CardOne(void)
{
}
void CardOne::setwalletAmount(int x) {
	walletAmount = x;
}
int CardOne::getwalletAmount() {
	return walletAmount;
}
void CardOne::ReadCardParameters(Grid * pGrid)
{
	
	
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==


	// 1- Get a Pointer to the Input / Output Interfaces from the Grid
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// 2- Read an Integer from the user using the Input class and set the walletAmount parameter with it
	//    Don't forget to first print to a descriptive message to the user like:"New CardOne: Enter its wallet amount ..."
	// [ Note ]:
	// In CardOne, the only parameter of CardOne is the "walletAmount" value to decrease from player
	// Card parameters are the inputs you need to take from the user in the time of adding the Card in the grid
	// to be able to perform his Apply() action
	pOut->PrintMessage("Enter Fine amount: ");
	int x = pIn->GetInteger(pOut);
	setwalletAmount(x);

	// 3- Clear the status bar
	pOut->ClearStatusBar();
}

void CardOne::Apply(Grid* pGrid, Player* pPlayer)
{
		
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	

	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid, pPlayer);
	int x = getwalletAmount();
	int y = pPlayer->GetWallet();
	// 2- Decrement the wallet of pPlayer by the walletAmount data member of CardOne
	pPlayer->SetWallet(y - x);
}
void CardOne::Draw(Output* pOut) {
	Card::Draw(pOut);
}
void CardOne::Save(ofstream& OutFile, Grid* pGrid, int typ) {
	Card::Save(OutFile, pGrid, typ);
	if (type==3){
		OutFile << getwalletAmount() << endl;
	}	
}


CardOne* CardOne::Load(ifstream& InFile, Grid* pGrid, int typ) {
	CardOne* pLoaded = NULL;
	int CellPos;
	InFile >> CellPos;
	CellPosition Cardposition(CellPos);
	pLoaded = new CardOne(Cardposition);
	int wallet;
	InFile >> wallet;
	pLoaded->setwalletAmount(wallet);
	pGrid->AddObjectToCell(pLoaded);
	return pLoaded;
}

Card* CardOne::GetCopy() {
	CardOne* CardOneCopy = new CardOne(0);
	CardOneCopy->setwalletAmount(getwalletAmount());
	return CardOneCopy;
}