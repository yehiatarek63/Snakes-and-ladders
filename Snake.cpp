#include "Snake.h"
#include "Player.h"
#include "Card.h"
Snake::Snake(const CellPosition& startCellPos, const CellPosition& endCellPos) : GameObject(startCellPos)
{
	this->endCellPos = endCellPos;
	this->startCellPos = startCellPos;
	type = 2;
	///TODO: Do the needed validation
}

void Snake::Draw(Output* pOut) const
{
	pOut->DrawSnake(position, endCellPos);
}

void Snake::Apply(Grid* pGrid, Player* pPlayer)
{
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function 
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	int x, y;
	// 1- Print a message "You have reached a snake. Click to continue ..." and wait mouse click
	pOut->PrintMessage("You have reached a snake. Click to continue ...");
	pIn->GetPointClicked(x, y);
	// 2- Apply the snake effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	Cell c(endCellPos);
	if (pPlayer->GetCell()->HasCard() != NULL) {
		Card* C = pPlayer->GetCell()->HasCard();
		C->Apply(pGrid, pPlayer);
	}
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);
	pOut->ClearStatusBar();
}
bool Snake::IsOverlapping(GameObject* newObj) {

	if (dynamic_cast<Snake*>(newObj)) {
		Snake* pSnake = dynamic_cast<Snake*>(newObj);
		if (newObj->GetEndPosition().HCell() == GetEndPosition().HCell()) {
			for (int i = newObj->GetStartPosition().VCell(); i <= newObj->GetEndPosition().VCell(); i++) {
				if (i == GetStartPosition().VCell() || i == GetEndPosition().VCell()) {
					return true;
				}
			}
		}
		if (GetEndPosition().VCell() > newObj->GetEndPosition().VCell() && GetEndPosition().VCell() < newObj->GetStartPosition().VCell()) {
			return true;
		}
	}
	return false;
}

CellPosition Snake::GetStartPosition() const {
	return startCellPos;
}
CellPosition Snake::GetEndPosition() const
{
	return endCellPos;
}

int Snake::GetStartNum() const{
	return startCellPos.GetCellNum();
}

int Snake::GetEndNum() const {
	return endCellPos.GetCellNum();
}

void Snake::Save(ofstream& OutFile, Grid* pGrid, int typ) {
	if (typ != type) {
		return;
	}
	else {
		OutFile << GetStartPosition().GetCellNum() << " " << GetEndPosition().GetCellNum() << " " << endl;
	}
}
Snake* Snake::Load(ifstream& InFile, Grid* pGrid, int typ) {
	Snake* pLoaded = NULL;
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

		pLoaded = new Snake(CStart, CEnd);
		pGrid->AddObjectToCell(pLoaded);
		return pLoaded;
	}
	return pLoaded;
}

Snake::~Snake()
{
}