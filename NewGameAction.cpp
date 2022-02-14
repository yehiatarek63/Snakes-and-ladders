#include "NewGameAction.h"
#include "Card.h"
#include "CardEleven.h"
#include "CardTen.h"
#include "CardNine.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
#include "Player.h"


NewGameAction::NewGameAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

NewGameAction::~NewGameAction()
{
}

void NewGameAction::ReadActionParameters()
{
	
}


// Execute the action
void NewGameAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	CellPosition pos(8, 0);
	Card* pCard;
	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager
	pGrid->ResetAll9to11(); //reset ownership of cards

	for (int i = 0; i < 4; i++) {
		pGrid->UpdatePlayerCell(pGrid->GetCurrentPlayer(), pos);
		pGrid->GetCurrentPlayer()->SetWallet(100);
		pGrid->GetCurrentPlayer()->SetTurnCount(0);
		pGrid->GetCurrentPlayer()->SetstepCount(1);
		pGrid->AdvanceCurrentPlayer();
	}
	while (pGrid->getCurrentPlayerNum()!=0) {
		pGrid->AdvanceCurrentPlayer();
	}	
} //resets turn count,step count, wallet and gives the turn back to player 0