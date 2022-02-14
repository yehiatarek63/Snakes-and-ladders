#include "CardFour.h"
//CardFour(const CellPosition& pos);
//virtual void ReadCardParameters(Grid* pGrid);
//virtual void Apply(Grid* pGrid, Player* pPlayer);
//virtual ~CardFour();


CardFour::CardFour(const CellPosition& pos) : Card(pos) {
	type = 3;
	cardNumber = 4;
}
CardFour::~CardFour() {};
void CardFour::ReadCardParameters(Grid* pGrid) {};
void CardFour::Apply(Grid* pGrid, Player* pPlayer) {
	Card::Apply(pGrid, pPlayer);
	pPlayer->setcard4affect(1);
}
void CardFour::Save(ofstream& OutFile, Grid* pGrid, int typ) {
	Card::Save(OutFile, pGrid, typ);
	OutFile << endl;
}
CardFour* CardFour::Load(ifstream& InFile, Grid* pGrid, int typ) {
	CardFour* pLoaded = NULL;
	int CellPos;
	InFile >> CellPos;
	CellPosition Cardposition(CellPos);
	pLoaded = new CardFour(Cardposition);
	pGrid->AddObjectToCell(pLoaded);
	return pLoaded;
}

Card* CardFour::GetCopy() {
	return new CardFour(0);
}