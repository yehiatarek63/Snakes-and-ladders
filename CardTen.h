
#pragma once
#include "Card.h"
class CardTen : public Card {
protected:
	static int fees;
	static int price;
	static bool owned;
	static Player* owner;
	int type;
public:
	CardTen(const CellPosition& pos);
	static void setowner(Player* p = NULL);
	Player* getowner();
	bool setfees(int x);
	int getfees();
	bool setprice(int x);
	static int getprice();
	void setown(bool x = 0);
	bool getown();
	virtual void ReadCardParameters(Grid* pGrid);
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	CellPosition* getallcards();
	virtual Card* GetCopy();
	void Reset();
	virtual ~CardTen();
	virtual void Save(ofstream& OutFile, Grid* pGrid, int typ);
	virtual CardTen* Load(ifstream& InFile, Grid* pGrid, int typ);
};