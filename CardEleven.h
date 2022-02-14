

#pragma once
#include "Card.h"
class CardEleven : public Card {
protected:
	static int fees;
	static int price;
	static bool owned;         // bool used to give info that the card has owner or no
	static Player* owner;      // used to get pointer of type player refers to owner
	int type;
public:
	CardEleven(const CellPosition& pos);
	static void setowner(Player* p = NULL);
	Player* getowner();
	bool setfees(int x);
	int getfees();
	bool setprice(int x);
	static int getprice();
	void setown(bool x = 0);   //set the bool which give info that the card has owner or not
	bool getown();        //get the bool which give info that the card has owner or not
	virtual void ReadCardParameters(Grid* pGrid);
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	CellPosition* getallcards();
	virtual void Save(ofstream& OutFile, Grid* pGrid, int typ);
	virtual Card* GetCopy();
	void Reset();
	CardEleven* Load(ifstream& InFile, Grid* pGrid, int typ);
	virtual ~CardEleven();
};