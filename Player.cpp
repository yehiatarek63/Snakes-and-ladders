#include "Player.h"
#include "Cell.h"
#include "Card.h"
#include "Ladder.h"
#include "Snake.h"
#include "GameObject.h"

Player* Player::lowPlayer = NULL;
int Player::MinWallet = 1000;
bool Player::end = false;
Player::Player(Cell* pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum)
{
	this->pCell = pCell;
	this->turnCount = 0;

	// Make all the needed initialization or validations
}

// ====== Setters and Getters ======

int Player::getdiffClosestPlayer(Player* pPlayer) {        
	int diff = -1;
	if (getstepCount() < pPlayer->getstepCount()) {
		diff = (pPlayer->getstepCount()) - (getstepCount());
	}
	return diff;
}

void Player::SetstepCount(int s) {
	stepCount = s;
}
int Player::getstepCount() const {
	return stepCount;
}

int Player::getjustrolleddicenumber() const {
	return justRolledDiceNum;
}

void Player::increasecountby1() {
	freezingcount = freezingcount + 1;
}
void Player::resetcount() {
	freezingcount = 0;
}
int Player::getcount() const{
	return freezingcount;
}
void Player::setownership(int x, bool c12) {
	if (this == NULL)
		return;
	else if (x == 9)
		hascard9 = c12;
	else if (x == 10)
		hascard10 = c12;
	else if (x == 11)
		hascard11 = c12;
}
bool Player::gettheownership(int x) {
	if (x == 9)
		return hascard9;
	else if (x == 10)
		return hascard10;
	else if (x == 11)
		return hascard11;
}

void Player::SetCell(Cell* cell)
{
	pCell = cell;
}

void Player::setcard4affect(bool x) {
	card4affect = x;
}

bool Player::getcard4affect() const{
	return card4affect;
}

Cell* Player::GetCell() const
{
	return pCell;
}
void Player::SetTurnCount(int turn) {
	turnCount = turn > 0 ? turn : 0;
}
void Player::SetWallet(int wallet)
{
	this->wallet = wallet >= 0 ? wallet : 0;
	// Make any needed validations
	if (wallet < MinWallet) {
		MinWallet = wallet;
		lowPlayer = this;
	}
}

Player* Player::GetPlayerThatHasLowWallet() {
	return lowPlayer;
}

int Player::GetWallet() const
{
	return wallet;
}
void Player::setmoveability(bool x) {
	HasMoveAbility = x;
}
bool Player::getmoveability() {
	return HasMoveAbility;
}
int Player::GetTurnCount() const
{
	return turnCount;
}

// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];


	///TODO: use the appropriate output function to draw the player with "playerColor"
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor);
}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;


	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor);
}

// ====== Game Functions ======

void Player::Move(Grid* pGrid, int diceNumber)
{
	Output* pOut = pGrid->GetOutput();       //used the grid pointer to get input and output pointer
	Input* pin = pGrid->GetInput();
	Output* pout = pGrid->GetOutput();
	if (!end) {
		
		if (poisoned == 1) {
			pOut->PrintMessage("P" + to_string(playerNum) + "You Will Be Hit By a Poison Attack!  Click to Continue...");
			int x, y;
			pin->GetPointClicked(x, y);
			pOut->ClearStatusBar();
			diceNumber = diceNumber - 1;
			if (poisonCount == 4)
			{
				poisoned = 0;
				poisonCount = 0;
			}
			poisonCount++;
		}
		if (hasFire == 1) {
			pOut->PrintMessage("P" + to_string(playerNum) + "You Will Be Hit By a Fire Attack!  Click to Continue...");
			SetWallet(GetWallet() - 25);
			int x, y;
			pin->GetPointClicked(x, y);
			pOut->ClearStatusBar();
			if (FireCount == 2) {
				FireCount = 0;
				hasFire = 0;
			}
			FireCount++;
		}
		if (pGrid->GetEndGame()) {
			pOut->PrintMessage("Congratulations P" + to_string(playerNum) + " You Win!");
			int x, y;
			pin->GetPointClicked(x, y);
			pOut->ClearStatusBar();
			end = true;
			return;
		}
		if (getcard4affect() == 1) {
			pOut->PrintMessage("P" + to_string(playerNum) + "You Will Be Prevented from Moving this Round!  Click to Continue...");
			int x, y;
			pin->GetPointClicked(x, y);
			pOut->ClearStatusBar();
			setcard4affect(0);
			return;
		}
		if (getmoveability() == 1) {
			///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


			// == Here are some guideline steps (numbered below) to implement this function ==


			// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once
			turnCount++;
			// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
			//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)
			if (turnCount == 4) {
				pout->PrintMessage("P" + to_string(playerNum) + " “Do you wish to launch a special attack instead of recharging? (Number Attacks Used " + to_string(NumberOfUsedAbility) + "/2) yes(1) / no(2)”");
				int x;
				x = pin->GetInteger(pout);
				pOut->ClearStatusBar();
				if (x == 2) {
					SetWallet(GetWallet() + (diceNumber * 10));
					turnCount = 0;
					return;
				}
				else if (NumberOfUsedAbility < 2)
				{
					pout->PrintMessage("“1-Ice  2-Fire 3-Prison 4-lighting”");
					int y = pin->GetInteger(pout);
					pOut->ClearStatusBar();
					if (y == 1 && IceAbility == 0) {
						if (IceAbilityF(pGrid)) {
							IceAbility = 1;
							NumberOfUsedAbility++;
						};
					}
					else if (y == 2 && FireAbility == 0) {
						if (FireAbilityF(pGrid)) {
							FireAbility = 1;
							NumberOfUsedAbility++;
						}
					}
					else if (y == 3 && PoisonAbility == 0) {
						if (PoisonAbilityF(pGrid)) {
							PoisonAbility = 1;
							NumberOfUsedAbility++;
						}
					}
					else if (y == 4 && LightAbility == 0) {
						pOut->PrintMessage("P" + to_string(playerNum) + " Has Called a Lightning Attack, You will All be deducted 20 coins! Click to Continue...");
						int x, y;
						pin->GetPointClicked(x, y);
						pOut->ClearStatusBar();
						pGrid->GetLightingPlayerExpect(playerNum);
						LightAbility = 1;
						NumberOfUsedAbility++;
						
					}
					else if (LightAbility == 1 || PoisonAbility == 1 || IceAbility == 1 || FireAbility == 1) {
						pOut->PrintMessage("You Have Already used this Ability Before!");
						int x, y;
						pin->GetPointClicked(x, y);
						pOut->ClearStatusBar();
						SetWallet(GetWallet() + (diceNumber * 10));
						turnCount = 0;
						return;
					}
					turnCount = 0;
					return;
				}
				else if (NumberOfUsedAbility == 2) {
					pOut->PrintMessage("You Have Already used Maximum Number of Abilities!");
					int x, y;
					pin->GetPointClicked(x, y);
					pOut->ClearStatusBar();
					SetWallet(GetWallet() + (diceNumber * 10));
					turnCount = 0;
					return;
				}

			}
			// 3- Set the justRolledDiceNum with the passed diceNumber
			justRolledDiceNum = diceNumber;
			// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
			//    Using the appropriate function of CellPosition class to update "pos"
			CellPosition currentPos = pCell->GetCellPosition();
			currentPos.AddCellNum(justRolledDiceNum);
			// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
			//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position
			pGrid->UpdatePlayerCell(this, currentPos);
			// 6- Apply() the game object of the reached cell (if any)

			if (this->GetCell()->HasCard()) {
				Card* card = this->GetCell()->HasCard();
				card->Apply(pGrid, this);
			}
			else if (this->GetCell()->HasLadder()) {
				Ladder* ladder = this->GetCell()->HasLadder();
				ladder->Apply(pGrid, this);
			}
			else if (this->GetCell()->HasSnake()) {
				Snake* snake = this->GetCell()->HasSnake();
				snake->Apply(pGrid, this);
			}
			// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)
			int currenCellNum = currentPos.GetCellNum();
			if (currenCellNum == 99) {

				pGrid->SetEndGame(true);

			}
		}
		else {
			increasecountby1();
			if (getcount() == 3) {
				setmoveability(1);
				resetcount();
			}

		}
	}
}


void Player::AppendPlayerInfo(string& playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(";
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}

void Player::sethasfire(bool x) {
	hasFire = x;
}
bool Player::gethasfire() {
	return hasFire;
}
void Player::sethaspoison(bool x) {
	poisoned = x;
}
bool Player::IceAbilityF(Grid* pGrid) {
	Input* pin = pGrid->GetInput();
	Output* pout = pGrid->GetOutput();
	pout->PrintMessage("Enter number of the player used ice ability against");
	int x = pin->GetInteger(pout);
	if (x <= 3 && x > 0) {
		Player* pPlayer = pGrid->GetPlayerByNum(x);
		pPlayer->setcard4affect(1);
		return true;
	}
	return false;
}
bool Player::FireAbilityF(Grid* pGrid) {
	Input* pin = pGrid->GetInput();
	Output* pout = pGrid->GetOutput();
	pout->PrintMessage("Enter number of the player used Fire ability against");
	int x = pin->GetInteger(pout);
	if (x <= 3 && x > 0) {
		Player* pPlayer = pGrid->GetPlayerByNum(x);
		pPlayer->sethasfire(1);
		return true;
	}
	return false;
}

bool Player::PoisonAbilityF(Grid* pGrid) {
	Input* pin = pGrid->GetInput();
	Output* pout = pGrid->GetOutput();
	pout->PrintMessage("Enter number of the player used poison ability against");
	int x = pin->GetInteger(pout);
	if (x <= 3 && x > 0) {
		Player* pPlayer = pGrid->GetPlayerByNum(x);
		pPlayer->sethaspoison(1);
		return true;
	}
	return false;
};
bool Player::Lighting(Player* pPlayer) {
	pPlayer->SetWallet(pPlayer->GetWallet() - 20);
	return true;
}