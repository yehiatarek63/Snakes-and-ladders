#include "SwitchToPlay.h"
SwitchToPlay::SwitchToPlay(ApplicationManager* pApp):Action(pApp) {};
SwitchToPlay::~SwitchToPlay() {};
void SwitchToPlay::ReadActionParameters() {};
void SwitchToPlay::Execute(){
	Grid* pGrid = pManager->GetGrid();
	Input* pin = pGrid->GetInput();
	Output* pout = pGrid->GetOutput();
	pout->CreatePlayModeToolBar();
}