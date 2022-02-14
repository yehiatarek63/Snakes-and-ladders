#include "DeleteGameObjectAction .h"
#include "Input.h"
#include "Output.h"
#include "GameObject.h"
#include "Cell.h"
#include "Snake.h"
#include "Ladder.h"

DeleteGameObjectAction::DeleteGameObjectAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

DeleteGameObjectAction::~DeleteGameObjectAction()
{
}
void DeleteGameObjectAction::ReadActionParameters() {
	check = true;
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Delete Game Object: Click on object you want to delete: ");
	pos = pIn->GetCellClicked();
	if (pos.VCell() == -1 || pos.HCell() == -1) { // Validation in case of invalid cell
		pOut->PrintMessage("Invalid! Location outside valid boundaries!  Click to continue ...");
		int x, y;
		pIn->GetPointClicked(x, y);
		check = false;
	}
	pOut->ClearStatusBar();
}
void DeleteGameObjectAction::Execute() {
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	if (check) { // if cell is valid it removes cobject from cell
		bool deleted = pGrid->RemoveObjectFromCell(pos);
	}
	
}