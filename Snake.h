#pragma once

#include "GameObject.h"

class Snake : public GameObject // inherited from GameObject
{
	// Note: the "position" data member inherited from the GameObject class is used as the ladder's "Start Cell Position"

	CellPosition endCellPos; // here is the snake's End Cell Position
	CellPosition startCellPos;
	int type;

public:

	Snake(const CellPosition& startCellPos, const CellPosition& endCellPos); // A constructor for initialization

	virtual void Draw(Output* pOut) const; // Draws a snake from its start cell to its end cell

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the snake by moving player to snake's end cell

	CellPosition GetEndPosition() const; // A getter for the endCellPos data member

	CellPosition GetStartPosition() const;

	virtual bool IsOverlapping(GameObject* newObj);

	virtual int GetStartNum() const;

	virtual int GetEndNum() const;

	virtual void Save(ofstream& OutFile, Grid* pGrid, int typ);

	virtual Snake* Load(ifstream& InFile, Grid* pGrid, int typ);

	virtual ~Snake(); // Virtual destructor
};

