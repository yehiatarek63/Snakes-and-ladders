#include "Grid.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
#include "CardEight.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
#include "CardTwelve.h"
#include "Cell.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Snake.h"
#include "Card.h"
#include "Player.h"

Card* Grid::Clipboard = NULL;

Grid::Grid(Input * pIn, Output * pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells-1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}


// ========= Adding or Removing GameObjects to Cells =========


bool Grid::AddObjectToCell(GameObject * pNewObject)  // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject * pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if( pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}


// Note: You may need to change the return type of this function (Think)
bool Grid::RemoveObjectFromCell(const CellPosition & pos)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed

		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
		return true;
	}
	return false;
}

void Grid::UpdatePlayerCell(Player * player, const CellPosition & newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);
	// Set the player's CELL with the new position
	Cell * newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);	

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
	player->SetstepCount(newPosition.GetCellNum());
}


// ========= Setters and Getters Functions =========

GameObject** Grid::GetGameObjectList() const{
	GameObject* arrofObjs[99];
	int c = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 11; j++) {
			if (CellList[i][j]->HasLadder()) {
				arrofObjs[c] = CellList[i][j]->HasLadder();
				c++;
			}
			else if (CellList[i][j]->HasSnake()) {
				arrofObjs[c] = CellList[i][j]->HasSnake();
				c++;
			}
		}
	}
	return arrofObjs;
}

Card* Grid::GetCard(CellPosition pos) { // gets a pointer on the card in the passed cell position
	int v = pos.VCell();
	int h = pos.HCell();
	if (CellList[v][h]->HasCard() != NULL) {
		return CellList[v][h]->HasCard();
	}
	else {
		return NULL;
	}
}

Input * Grid::GetInput() const
{
	return pIn;
}

Output * Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card * pCard) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}

Card * Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}


void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}

// ========= Other Getters =========


Player* Grid::GetClosestPlayer() { // gets a pointer on the player closest to current player
	int min = 101;
	Player* pPlayertemp = NULL;
	for (int i = 0; i < 4; i++) {
		int mintemp = PlayerList[currPlayerNumber]->getdiffClosestPlayer(PlayerList[(currPlayerNumber + i) % MaxPlayerCount]);
		if ((mintemp < min) && (mintemp != -1)) {
			min = mintemp;
			pPlayertemp = PlayerList[(currPlayerNumber + i) % MaxPlayerCount];
		}
	}
	return pPlayertemp;
}

Player * Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

Player* Grid::GetNextPlayer()const {
	return PlayerList[currPlayerNumber+1];
}

int Grid::GetCountofObj(int type) const{
	int num = 0;
	if (type == 1) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 11; j++) {
				if (CellList[i][j]->HasLadder()) {
					num++;
				}
			}
		}
	}
	else if (type == 2) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 11; j++) {
				if (CellList[i][j]->HasSnake()) {
					num++;
				}
			}
		}
	}
	else if (type == 3) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 11; j++) {
				if (CellList[i][j]->HasCard()) {
					num++;
				}
			}
		}
	}
	return num;
}

Ladder * Grid::GetNextLadder(const CellPosition & position)
{
	
	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{


			///TODO: Check if CellList[i][j] has a ladder, if yes return it
			if (CellList[i][j]->HasLadder()) {
				return CellList[i][j]->HasLadder();
			}
			

		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}


// ========= User Interface Functions =========


void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount-1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}

void Grid::SaveAll(ofstream& OutFile, Grid* pGrid, int typ) {

	if (!OutFile.is_open()) {
		pOut->PrintMessage("Error!");
	}
	
	int numofobj = GetCountofObj(typ);
	OutFile << numofobj << endl;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 11; j++) {
			if (CellList[i][j]->HasLadder() && typ == 1) {
				Ladder* pLadder = CellList[i][j]->HasLadder(); 
				pLadder->Save(OutFile, pGrid, 1);

			}
			else if (CellList[i][j]->HasSnake() && typ == 2){
				Snake* pSnake = CellList[i][j]->HasSnake();
				pSnake->Save(OutFile, pGrid, 2);
			}
			else if (CellList[i][j]->HasCard() && typ == 3) {
				int CardNumber = CellList[i][j]->HasCard()->GetCardNumber();
				Card* pCard = CellList[i][j]->HasCard();
				pCard->Save(OutFile, pGrid, 3);
			}
		}
	}
}

bool Grid::IsOverlapping(GameObject* newObj) {
	bool checkOverlap = false;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 11; j++) {
			if (CellList[i][j]->HasLadder()) {
				checkOverlap = CellList[i][j]->HasLadder()->IsOverlapping(newObj); //Loop through the CellList and check if there is a ladder 
																				  //and check if this ladder overlaps with new object being added
				return checkOverlap;
			}
			else if (CellList[i][j]->HasSnake()) {
				checkOverlap = CellList[i][j]->HasSnake()->IsOverlapping(newObj);  //Loop through the CellList and check if there is a ladder 
																				  //and check if this ladder overlaps with new object being added
				return checkOverlap;
			}
		}
	}
	return false;
}

int Grid::getCurrentPlayerNum() const {
	return currPlayerNumber;
}

Player* Grid::GetPlayerByNum(int x) {
	if (x < 4) {
		return PlayerList[x];
	};
	return false;
}

void Grid::GetLightingPlayerExpect(int x) {
	for (int i = 0; i < 4; i++) {
		if (i != x) {
			PlayerList[i]->Lighting(PlayerList[i]);
		}
	}
}

void Grid::LoadAll(ifstream& InFile, Grid* pGrid, int typ) {
	int CountLadder;
	InFile >> CountLadder; //Read The Count of Ladders
	Ladder* pLadder;
	Snake* pSnake;
	Card* pCard;
	for (int i = 0; i < CountLadder; i++) { //Loop Throuh Each Saved Ladder
		Ladder ladder(0, 0);
		pLadder = ladder.Load(InFile, pGrid, 1); //Call the Load function of Each ladder
	}
	int CountSnake; 
	InFile >> CountSnake; //Read the count of Snakes
	for (int i = 0; i < CountSnake; i++) {
		Snake snake(0, 0);
		pSnake = snake.Load(InFile, pGrid, 2); //Call the Load Function of Each Snake
	}
	int CountCards;
	InFile >> CountCards; //Read the count of Cards
	for (int i = 0; i < CountCards+1; i++) {
		int CardNum;
		InFile >> CardNum; //Read The Card Number and Call the corresponding Load Function
		if (CardNum == 1) {
			CardOne card(0);
			pCard = card.Load(InFile, pGrid, 1);
		}
		else if (CardNum == 2) {
			CardTwo card(0);
			pCard = card.Load(InFile, pGrid, 1);
		}
		else if (CardNum == 3) {
			CardThree card(0);
			pCard = card.Load(InFile, pGrid, 1);
		}
		else if (CardNum == 4) {
			CardFour card(0);
			pCard = card.Load(InFile, pGrid, 1);
		}
		else if (CardNum == 5) {
			CardFive card(0);
			pCard = card.Load(InFile, pGrid, 1);
		}
		else if (CardNum == 6) {
			CardSix card(0);
			pCard = card.Load(InFile, pGrid, 1);
		}
		else if (CardNum == 7) {
			CardSeven card(0);
			pCard = card.Load(InFile, pGrid, 1);
		}
		else if (CardNum == 8) {
			CardEight card(0);
			pCard = card.Load(InFile, pGrid, 1);
		}
		else if (CardNum == 9) {
			CardNine card(0);
			pCard = card.Load(InFile, pGrid, 1);
		}
		else if (CardNum == 10) {
			CardTen card(0);
			pCard = card.Load(InFile, pGrid, 1);
		}
		else if (CardNum == 11) {
			CardEleven card(0);
			pCard = card.Load(InFile, pGrid, 1);
		}
		else if (CardNum == 12) {
			CardTwelve card(0);
			pCard = card.Load(InFile, pGrid, 1);
		}
	}
}

void Grid::ClearGrid() { //clears the grid by removing all gameobjects
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 11; j++) {
			if (CellList[i][j]->GetGameObject()) {
				delete CellList[i][j]->GetGameObject();
				CellList[i][j]->SetGameObject(NULL);
			}
		}
	}
}

bool Grid::HasLadderSnake(CellPosition pos) { //checks if cell position has snakes or ladders
	int v = pos.VCell();
	int h = pos.HCell();
	if (CellList[v][h]->HasLadder() == NULL && CellList[v][h]->HasSnake() == NULL) {
		return false;
	}
	return true;
}

void Grid::ResetAll9to11() { //loops and resets card 9 to 11
	CardNine* pCardNine;
	CardTen* pCardTen;
	CardEleven* pCardEleven;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 11; j++) {
			if (CellList[i][j]->HasCard() == NULL) {
				continue;
			}
			else if (CellList[i][j]->HasCard()->GetCardNumber() == 9) {
				pCardNine = dynamic_cast<CardNine*>(CellList[i][j]->HasCard());
				pCardNine->Reset();
			}
			else if (CellList[i][j]->HasCard()->GetCardNumber() == 10) {
				pCardTen = dynamic_cast<CardTen*>(CellList[i][j]->HasCard());
				pCardTen->Reset();
			}
			else if (CellList[i][j]->HasCard()->GetCardNumber() == 11) {
				pCardEleven = dynamic_cast<CardEleven*>(CellList[i][j]->HasCard());
				pCardEleven->Reset();
			}
		}
	}
}

Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		delete PlayerList[i];
	}
}