#include "SaveGridAction.h"
SaveGridAction::SaveGridAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
	pGrid = pManager->GetGrid();
	pOut = pGrid->GetOutput();
	pIn = pGrid->GetInput();
}
void SaveGridAction::ReadActionParameters() {
	string file_name;
	pOut->PrintMessage("Enter File Name: ex(filename)");
	file_name = pIn->GetSrting(pOut);
	file_name += ".txt"; //adding .txt to the file name to sae it in this format
	OutFile.open(file_name); //Opening File with the "file_name" if it doesn't exist this will create the file, if it did exist it will overwrite the file
	OutFile.close();
	OutFile.open(file_name, ios::app); //opening the file in append mode
	if (!OutFile.is_open()) {
		pOut->PrintMessage("Error Opening File!"); //Checking if File failed to open
		check = false;
	}
	else { check = true; }

}
void SaveGridAction::Execute() {
	ReadActionParameters();
	if (check) {
		int x, y;
		pGrid->SaveAll(OutFile, pGrid, 1); //Saving All Ladders
		pGrid->SaveAll(OutFile, pGrid, 2); //Saving All Snakes
		pGrid->SaveAll(OutFile, pGrid, 3); //Saving All Cards
		pOut->PrintMessage("File Saved Successfully! Click to Continue...");
		pIn->GetPointClicked(x, y);
	}

	pOut->ClearStatusBar();
}