#include "CutAction.h"

#include "Input.h"
#include "Output.h"
#include "GameObject.h"
#include "Cell.h"
#include "Card.h"
#include "Snake.h"
#include "Ladder.h"
CutAction::CutAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
	pManager = pApp;
}

CutAction::~CutAction()
{
}
void CutAction::ReadActionParameters() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Cut card: Click on card you want to cut: ");
	pos = pIn->GetCellClicked();
	if (pos.VCell() == -1 || pos.HCell() == -1) {
		pOut->PrintMessage("Invalid! Location outside valid boundaries!  Click to continue ...");
		int x, y;
		pIn->GetPointClicked(x, y);
	}
	Card* pCard = pGrid->GetCard(pos);
	pOut->ClearStatusBar();
}
void CutAction::Execute() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	ReadActionParameters();
	Card*pCard = pGrid->GetCard(pos);
	pGrid->SetClipboard(pCard);
	bool deleted = pGrid->RemoveObjectFromCell(pos);
}