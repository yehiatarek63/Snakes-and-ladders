#pragma once

#include "Card.h"

class CardEight : public Card
{
	int coinsneedtedogo;     //fees that the player pay to go out of prison
public:
	CardEight(const CellPosition& pos);
	virtual void ReadCardParameters(Grid* pGrid);
	void setcoinsneededtogo(int x);    //set fees that the player pay to go out of prison
	int getcoinsneededtogo();       //get fees that the player pay to go out of prison
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	virtual void Save(ofstream& OutFile, Grid* pGrid, int typ);
	virtual CardEight* Load(ifstream& InFile, Grid* pGrid, int typ);
	virtual Card* GetCopy();
	virtual ~CardEight();
};