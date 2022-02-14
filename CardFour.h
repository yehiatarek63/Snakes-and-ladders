#pragma once

#include "Card.h"

class CardFour : public Card
{

public:
	CardFour(const CellPosition& pos);
	virtual void ReadCardParameters(Grid* pGrid);
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	virtual ~CardFour();
	virtual void Save(ofstream& OutFile, Grid* pGrid, int typ);
	virtual Card* GetCopy();
	virtual CardFour* Load(ifstream& InFile, Grid* pGrid, int typ);
};