#include "AddLadderAction.h"

#include "Input.h"
#include "Output.h"
#include "Ladder.h"
#include "Snake.h"

AddLadderAction::AddLadderAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
	pGrid = pManager->GetGrid();
	pOut = pGrid->GetOutput();
	pIn = pGrid->GetInput();
}

AddLadderAction::~AddLadderAction()
{
}

void AddLadderAction::ReadActionParameters() 
{	
	// Get a Pointer to the Input / Output Interfaces
	
	// Read the startPos parameter
	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New Ladder: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();
	checkifadded = true;
	///TODO: Make the needed validations on the read parameters
	if (endPos.GetCellNum() < startPos.GetCellNum()) {
		pOut->PrintMessage("Invalid! End Cell cannot be smaller that Start Cell");
		checkifadded = false;
	}
	else if (endPos.VCell() == startPos.VCell()) {
		pOut->PrintMessage("Invalid! End Cell and Start Cell CANNOT be in the same Column! Click to continue ...");
		checkifadded = false;
	}
	else if (endPos.HCell() != startPos.HCell()) {
		pOut->PrintMessage("Invalid! End Cell and Start MUST be on the same Row! Click to continue ...");
		checkifadded = false;
	}
	else if (startPos.VCell() == 1) {
		pOut->PrintMessage("Invalid! Start Cell Cannot be Cell 1! Click to continue ...");
		checkifadded = false;
	}
	else if (endPos.GetCellNum() == 99) {
		pOut->PrintMessage("Invalid! End Cell Cannot be Cell 99! Click to continue ...");
		checkifadded = false;
	}
	else if (pGrid->HasLadderSnake(endPos)) {
		pOut->PrintMessage("End Cell Cannot Be Start Cell of Another Snake/Ladder! Click to continue...");
		checkifadded = false;
	}
	// Clear messages
	if (!checkifadded) {
		int x, y;
		pIn->GetPointClicked(x, y);
	}
	pOut->ClearStatusBar();
}


// Execute the action
void AddLadderAction::Execute() 
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	
	// Create a Ladder object with the parameters read from the user
	if (checkifadded) {
		Ladder* pLadder = new Ladder(startPos, endPos);

		Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

		// Add the card object to the GameObject of its Cell:
		bool added = true;
		if (pGrid->IsOverlapping(pLadder)) { //Checking if the new Ladder overplaps with a previously existing ladder
			pOut->PrintMessage("Invalid Ladders Overlap! Click to continue...");
			pGrid->RemoveObjectFromCell(startPos);
			delete pLadder;
			int x, y;
			pIn->GetPointClicked(x, y);
		}
		else {
			added = pGrid->AddObjectToCell(pLadder);
		}
		// if the GameObject cannot be added
		if (!added)
		{
			// Print an appropriate message
			pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
			int x, y;
			pIn->GetPointClicked(x, y);
		}
	}
	pOut->ClearStatusBar();
	// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction
}
