#pragma once
#include "Card.h"
#include "ApplicationManager.h"

// [ CardThree ] Summary:
// Its Apply() Function: Gives player an extra dice roll.
// Its Parameters: N/A
class CardThree : public Card
{
	// CardThree Parameters:
	ApplicationManager* pManager;
public:
	CardThree(const CellPosition& pos); // A Constructor takes card position

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardThree on the passed Player
													  // by Giving the player an extra dice roll
	virtual void Save(ofstream& OutFile, Grid* pGrid, int typ);
	virtual CardThree* Load(ifstream& InFile, Grid* pGrid, int typ);
	virtual Card* GetCopy();
	virtual ~CardThree(); // A Virtual Destructor
};

