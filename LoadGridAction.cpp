#include "LoadGridAction.h"
LoadGridAction::LoadGridAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
	pGrid = pManager->GetGrid();
	pOut = pGrid->GetOutput();
	pIn = pGrid->GetInput();
}
void LoadGridAction::ReadActionParameters() {
	check = true;
	pOut->PrintMessage("Enter Name of the File You Want to Load : ");
	file_name = pIn->GetSrting(pOut);
	file_name += ".txt";
	InFile.open(file_name);
	if (!InFile.is_open()) {
		pOut->PrintMessage("File does not Exist!");
		check = false;
	}
	if (!check) {
		int x, y;
		pIn->GetPointClicked(x, y);
	}
	pOut->ClearStatusBar();
}
void LoadGridAction::Execute() {
	ReadActionParameters();
	pGrid->ClearGrid();
	int x, y;
	if (check) {
		pGrid->LoadAll(InFile, pGrid, 1); // Loading All Saved Objects
		pOut->PrintMessage("File Loaded Successfully! Click to View Grid...");
		pIn->GetPointClicked(x, y);
	}

	pOut->ClearStatusBar();
}