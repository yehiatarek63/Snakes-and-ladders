#pragma once

#include "Card.h"

// [ CardTwo ] Summary:
// Its Apply() Function: Finds the Next Ladder and Moves the player to this ladder.
// Its Parameters: N/A

class CardTwo : public Card
{
	// CardTwo Parameters:

public:
	CardTwo(const CellPosition& pos); // A Constructor takes card position

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardTwo on the passed Player
	virtual void Draw(Output* pOut);												  // by moving the player to the next ladder
	virtual void Save(ofstream& OutFile, Grid* pGrid, int typ);
	virtual CardTwo* Load(ifstream& InFile, Grid* pGrid, int typ);
	virtual Card* GetCopy();
	virtual ~CardTwo(); // A Virtual Destructor
};

