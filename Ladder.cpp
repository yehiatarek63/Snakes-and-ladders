#include "Ladder.h"
#include "Cell.h"
#include "Player.h"
#include "Card.h"
Ladder::Ladder(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{
	this->endCellPos = endCellPos;
	this->startCellPos = startCellPos;
	type = 1;
	///TODO: Do the needed validation
}


void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);
}



void Ladder::Apply(Grid* pGrid, Player* pPlayer) 
{
	

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function 
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	int x, y;
	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click
	pOut->PrintMessage("You have reached a ladder. Click to continue ...");
	pIn->GetPointClicked(x,y);
	// 2- Apply the ladder's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	pGrid->UpdatePlayerCell(pPlayer,endCellPos);
	if (pPlayer->GetCell()->HasCard() != NULL) {
		Card* C = pPlayer->GetCell()->HasCard();
		C->Apply(pGrid, pPlayer);
	}
	pOut->ClearStatusBar();
}

void Ladder::Save(ofstream& OutFile, Grid* pGrid, int typ) {
	if (typ != type) {
		return;
	}
	else {
		OutFile << GetStartPosition().GetCellNum() << " " << GetEndPosition().GetCellNum() << " " << endl; //Saving the Ladder Start and End Position
	}
}

Ladder* Ladder::Load(ifstream& InFile, Grid* pGrid, int typ) {
	Ladder* pLoaded = NULL;
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	if (typ != type) {
		return pLoaded;
	}
	else {
		int Start;
		int End;

		InFile >> Start;
		InFile >> End;

		CellPosition CStart(Start);
		CellPosition CEnd(End);
		pLoaded = new Ladder(CStart, CEnd);
		pGrid->AddObjectToCell(pLoaded);
		return pLoaded;
	}
	return pLoaded;
}
CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}
CellPosition Ladder::GetStartPosition() const
{
	return startCellPos;
}

bool Ladder::IsOverlapping(GameObject* newObj) {
	
	if (dynamic_cast<Ladder*>(newObj)) {
		Ladder* pLadder = dynamic_cast<Ladder*>(newObj);
		if (newObj->GetEndPosition().HCell() == GetEndPosition().HCell()) {
			for (int i = newObj->GetEndPosition().VCell(); i <= newObj->GetStartPosition().VCell(); i++){
				if (i == GetStartPosition().VCell() || i == GetEndPosition().VCell()) { //Checking if the new Ladder has the same VCell of the start/end position of an already existing ladder
					return true;
				}
			}
		}
		if (GetStartPosition().VCell() < newObj->GetStartPosition().VCell() && GetStartPosition().VCell() > newObj->GetEndPosition().VCell()) {
			return true;
		}
	}
	return false;
}

int Ladder::GetStartNum() const {
	return startCellPos.GetCellNum();
}

int Ladder::GetEndNum() const {
	return endCellPos.GetCellNum();
}
Ladder::~Ladder()
{
}
