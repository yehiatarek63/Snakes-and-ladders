#pragma once
#include "Card.h"
#include "CardNine.h"
#include "CardEleven.h"
#include "CardTen.h"
class CardTwelve : public Card
{

public:
	CardTwelve(const CellPosition& pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid* pGrid);
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	void Save(ofstream& OutFile, Grid* pGrid, int typ);
	CardTwelve* Load(ifstream& InFile, Grid* pGrid, int typ);
	virtual Card* GetCopy();
	virtual ~CardTwelve(); // A Virtual Destructor
};