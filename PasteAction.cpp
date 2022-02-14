#include "PasteAction.h"
#include "Input.h"
#include "Output.h"
#include "GameObject.h"
#include "Cell.h"
#include "Card.h"
#include "Snake.h"
#include "Ladder.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
#include "CardEight.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"



PasteAction::PasteAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
	pManager = pApp;
}

PasteAction::~PasteAction()
{
}
void PasteAction::ReadActionParameters() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Paste Card: Click on Cell where you want to Paste: ");
	pos = pIn->GetCellClicked();
	if (pos.VCell() == -1 || pos.HCell() == -1) {
		pOut->PrintMessage("Invalid! Location outside valid boundaries!  Click to continue ...");
		int x, y;
		pIn->GetPointClicked(x, y);
	}
	pOut->ClearStatusBar();
}
void PasteAction::Execute() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	ReadActionParameters();
	if (pGrid->GetClipboard() == NULL) { //Validation in case there is no card in clipboard
		pOut->PrintMessage("Clipboard is Empty! Click to Continue...");
		int x, y;
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		return;
	}
	Card* pCard = pGrid->GetClipboard()->GetCopy();//gets copy of the cardto be used in save and load
	pCard->SetPosition(pos); //sets the position of card using pos from gameobject
	pCard->SetCardCell(pos);
	pGrid->AddObjectToCell(pCard);
}
