#include "SwitchToDesign.h"

SwitchToDesign::SwitchToDesign(ApplicationManager* pApp) :Action(pApp) {};
SwitchToDesign::~SwitchToDesign() {};
void SwitchToDesign::ReadActionParameters() {};
void SwitchToDesign::Execute() {
	Grid* pGrid = pManager->GetGrid();
	Input* pin = pGrid->GetInput();
	Output* pout = pGrid->GetOutput();
	pout->CreateDesignModeToolBar();
};