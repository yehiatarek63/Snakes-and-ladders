#pragma once

#include "Grid.h"
#include "Cell.h"

class Player
{
	Cell* pCell;		   // pointer to the current Cell of the player

	const int playerNum;   // the player number (from 0 to MaxPlayerCount-1)
						   // player number does NOT change after construction (const.)

	int stepCount;		   // step count which is the same as his cellNum: from 1 to NumVerticalCells*NumHorizontalCells
	int wallet;		       // player's wallet (how many coins he has -- integer)
	int justRolledDiceNum; // the current dice number which is just rolled by the player
	int turnCount;         // a counter that starts with 0, is incremented with each dice roll
						   // and reset again when reached 3
						   // it is used to indicate when to move and when to add to your wallet
	bool hascard9 = 0;      //bool used to know if the player has card 9 or not
	bool hascard10 = 0;   //bool used to know if the player has card 10 or not
	bool hascard11 = 0;   //bool used to know if the player has card 11 or not
	bool HasMoveAbility = 1;    //bool used to give the player ability to move
	int freezingcount = 0;    //count used to in card8 (prison)  to which help to make plauer stay in card without move for 3 rounds
	bool card4affect = 0;     //bool used to know if player have card 4 affect
	static Player* lowPlayer;    //pointer of player type used to refers to player whose has the most lowest wallet
	static int MinWallet;   //int used to get the most lowest amount of wallet
	static bool end;

	//Bonus::
	bool hasFire = 0;
	int FireCount = 0;
	bool IceAbility = 0;
	bool FireAbility = 0;
	bool LightAbility = 0;
	bool PoisonAbility = 0;
	int NumberOfUsedAbility = 0;
	bool poisoned = 0;
	int poisonCount = 0;

public:

	Player(Cell* pCell, int playerNum); // Constructor making any needed initializations

	// ====== Setters and Getters ======

	void SetCell(Cell* cell);		// A setter for the pCell
	Cell* GetCell() const;			// A getter for the pCell
	int getjustrolleddicenumber() const;
	void SetWallet(int wallet);		// A setter for the wallet
	int GetWallet() const;			// a getter for the wallet
	void SetTurnCount(int turn);
	int GetTurnCount() const;		// A getter for the turnCount

	///TODO: You can add setters and getters for data members here (if needed)
	void setcard4affect(bool x);       //set card 4 affect
	bool getcard4affect() const;       //get card 4 affect
	void setmoveability(bool x);    //set the move ability of player
	bool getmoveability();
	void increasecountby1();      //increase the count by one which used in card 8
	void resetcount();          //reset the   count which used in card 8
	int getcount() const;
	void setownership(int x, bool c12 = 1);   //used to set the ownership of cards(9/10/11)  for player
	bool gettheownership(int x);                  //used to check has the card or no
	int getdiffClosestPlayer(Player* pPlayer);    //gets the difference between the cell num of the passed player and the calling player
	int getstepCount() const;      //gets the step count
	void SetstepCount(int s);    //set the step count
	static Player* GetPlayerThatHasLowWallet();   //gets the pointer of the player that has the most lowest wallet
	// ====== Drawing Functions ======

	void Draw(Output* pOut) const;			// Draws the Player's Circle on its current cell

	void ClearDrawing(Output* pOut) const;	// Clears the Player's Circle from its current cell

	// ====== Game Functions ======

	void Move(Grid* pGrid, int diceNumber);	// Moves the Player with the passed diceNumber 
												// and Applies the Game Object's effect (if any) of the end reached cell 
												// for example, if the end cell contains a ladder, take it

	void AppendPlayerInfo(string& playersInfo) const; // Appends player's info to the input string, 
													   // for example: P0(wallet, turnCount)

	// ====== Bonus Functions ======
	bool IceAbilityF(Grid* pGrid);
	bool FireAbilityF(Grid* pGrid);
	bool PoisonAbilityF(Grid* pGrid);
	bool Lighting(Player* pPlayer);
	void sethasfire(bool x);
	void sethaspoison(bool x);
	bool gethasfire();
};