#pragma once
#pragma once

#include "Card.h"


class CardSeven : public Card
{
	

public:
	CardSeven(const CellPosition& pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid* pGrid); 

	virtual void Apply(Grid* pGrid, Player* pPlayer); 

	virtual void Save(ofstream& OutFile, Grid* pGrid, int typ);

	virtual CardSeven* Load(ifstream& InFile, Grid* pGrid, int typ);

	virtual Card* GetCopy();

	virtual ~CardSeven(); // A Virtual Destructor
};