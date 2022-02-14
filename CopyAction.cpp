#include "CopyAction.h"

#include "Input.h"
#include "Output.h"
#include "GameObject.h"
#include "Cell.h"
#include "Card.h"
CopyAction::CopyAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

CopyAction::~CopyAction()
{
}
void CopyAction::ReadActionParameters() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Copy card: Click on card you want to Copy: ");
	pos = pIn->GetCellClicked();
	if (pos.VCell() == -1 || pos.HCell() == -1) { // Validation in case of invalid cell
		pOut->PrintMessage("Invalid! Location outside valid boundaries!  Click to continue ...");
		int x, y;
		pIn->GetPointClicked(x, y);
	}
	pOut->ClearStatusBar();
}
void CopyAction::Execute() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	ReadActionParameters();
	Card* pCard = pGrid->GetCard(pos); //gets pointer on card from pGrid
	pGrid->SetClipboard(pCard); // sets the clipboard with the pointer
}