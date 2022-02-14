#pragma once

#include "GameObject.h"

class Ladder :	public GameObject // inherited from GameObject
{
	// Note: the "position" data member inherited from the GameObject class is used as the ladder's "Start Cell Position"
	CellPosition startCellPos;
	CellPosition endCellPos; // here is the ladder's End Cell Position
	int type;

public:

	Ladder(const CellPosition & startCellPos, const CellPosition & endCellPos); // A constructor for initialization

	virtual void Draw(Output* pOut) const; // Draws a ladder from its start cell to its end cell

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the ladder by moving player to ladder's end cell

	CellPosition GetEndPosition() const; // A getter for the endCellPos data member
	
	CellPosition GetStartPosition() const;

	virtual int GetStartNum() const;

	virtual int GetEndNum() const;

	virtual bool IsOverlapping(GameObject* newObj);

	virtual void Save(ofstream& OutFile, Grid* pGrid, int type);

	virtual Ladder* Load(ifstream& Infile, Grid* pGrid, int typ);

	virtual ~Ladder(); // Virtual destructor
};

