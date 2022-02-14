#pragma once
#include "Card.h"



class CardSix : public Card
{
	// CardSix Parameters:
	int cellNum; // the cell to move to

public:
	CardSix(const CellPosition& pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid* pGrid); 

	virtual void Apply(Grid* pGrid, Player* pPlayer); 

	virtual void Save(ofstream& OutFile, Grid* pGrid, int typ);

	virtual CardSix* Load(ifstream& InFile, Grid* pGrid, int typ);

	virtual Card* GetCopy();

	void SetcellNum(int c);

	int getcellNum() const;

	virtual ~CardSix(); // A Virtual Destructor
};
