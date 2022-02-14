#include "AddSnakeAction.h"
#include "Snake.h"
#include "Input.h"
#include "Output.h"
#include "Ladder.h"

AddSnakeAction::AddSnakeAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddSnakeAction::~AddSnakeAction()
{
}

void AddSnakeAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	checkifadded = true;
	// Read the startPos parameter
	pOut->PrintMessage("New Snake: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New Snake: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();

	///TODO: Make the needed validations on the read parameters
	if (endPos.GetCellNum() > startPos.GetCellNum()) {
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
	else if (startPos.GetCellNum() == 99) {
		pOut->PrintMessage("Invalid! Snake Cannot Start in Cell 99! Click to continue ...");
		checkifadded = false;
	}
	else if (startPos.VCell() == 8) {
		pOut->PrintMessage("Invalid! Snake Cannot Start in the First Row! Click to continue ...");
		checkifadded = false;
	}
	else if (pGrid->HasLadderSnake(startPos)) {
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


void AddSnakeAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// Create a Snake object with the parameters read from the user
	if (checkifadded) {
		Snake* pSnake = new Snake(startPos, endPos);

		Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

		// Add the Snake object to the GameObject of its Cell:
		bool added = true;
		if (pGrid->IsOverlapping(pSnake)) { //Check if new Snake overlaps with a previously existing snake
			pOut->PrintMessage("Invalid Snakes Overlap! Click to continue...");
			pGrid->RemoveObjectFromCell(startPos);
			delete pSnake;
			int x, y;
			pIn->GetPointClicked(x, y);
		}
		else {
			added = pGrid->AddObjectToCell(pSnake);
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
