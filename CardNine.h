#pragma once
#include "Card.h"
class CardNine : public Card {
protected:
	static int fees;
	static int price;
	static bool owned;					// bool used to give info that the card has owner or no
	static Player* owner;				// used to get pointer of type player refers to owner
	int type;
public:
	CardNine(const CellPosition& pos);
	static void setowner(Player* p=NULL);			//set the owner
	Player* getowner();						//get the  owner pointer
	bool setfees(int x);
	int getfees();
	bool setprice(int x);
	static int getprice();
	void setown(bool x=0);				//set the bool which give info that the card has owner or not
	bool getowned();					//get the bool which give info that the card has owner or not
	virtual void ReadCardParameters(Grid* pGrid);
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	virtual ~CardNine();
	virtual CardNine* Load(ifstream& InFile, Grid* pGrid, int typ);
	virtual Card* GetCopy();
	void Reset();
	virtual void Save(ofstream& OutFile, Grid* pGrid, int typ);
};