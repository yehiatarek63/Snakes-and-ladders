#include "GameObject.h"
#include "Ladder.h"
#include "Snake.h"
#include "Card.h"

GameObject::GameObject(const CellPosition & pos)
{
	position = pos; // Sets Position
}

CellPosition GameObject::GetPosition() const
{
	return position;
}

void GameObject::SetPosition(CellPosition pos) {
	position = pos;
}

CellPosition GameObject::GetEndPosition() const{
	return position;
}

CellPosition GameObject::GetStartPosition() const{
	return position;
}

int GameObject::GetStartNum() const{
	return position.GetCellNum();
}

int GameObject::GetEndNum() const{
	return position.GetCellNum();
}

GameObject::~GameObject()
{
}

GameObject* GameObject::Load(ifstream& InFile, Grid* pGrid, int typ) {
	GameObject* g = NULL;
	return g;
}