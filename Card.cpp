#include "Card.h"
#include "CardOne.h"



Card::Card(const CellPosition & pos) : GameObject(pos) // sets the cell position of the GameObject
{
	cardCell = pos;
}

void Card::SetCardNumber(int cnum)
{
	cardNumber = (cnum>=1) && (cnum<=12) ? cnum:-1; // needs validation
}

void Card::SetCardCell(CellPosition & pos) {
	cardCell = pos;
}

int Card::GetCardNumber()
{
	return cardNumber;
}

void Card::Draw(Output* pOut) const
{
	///TODO: call the appropriate Ouput function that draws a cell containing the "cardNumber" in "position"
	pOut->DrawCell(position,cardNumber);
}

void Card::ReadCardParameters(Grid * pGrid)
{
	// we should not make it pure virtual because some Cards doesn't have parameters
	// and if we make it pure virtual, that will make those Cards abstract classes
}

void Card::Apply(Grid* pGrid, Player* pPlayer) 
{
	// As written below the "Roll Dice" action in the document ==> Check the Project Document
	// "If a player reaches a card of any other type", the following message should be printed then wait mouse click
	pGrid->PrintErrorMessage("You have reached card " + to_string(cardNumber) + ". Click to continue ...");
}

Card::~Card()
{
}

int Card::GetCardCellNum() const {
	return cardCell.GetCellNum();
}

int Card::GetStartNum() const{
	return cardCell.GetCellNum();
}

int Card::GetEndNum() const {
	return cardCell.GetCellNum();
}

bool Card::IsOverlapping(GameObject* newObj) {
	return false; //Card cannot overlap with snakes or ladders so the function always returns false
}

void Card::Save(ofstream& OutFile, Grid* pGrid, int typ) {
	if (typ == 1 || typ == 2) {
		return;
	}
	else {
		OutFile << GetCardNumber() << " " << GetCardCellNum() << " "; //Saving The Card Number and Card Position
	}
		
}
Card* Card::Load(ifstream& InFile, Grid* pGrid, int typ) {
	Card* C = NULL;
	return C;
}