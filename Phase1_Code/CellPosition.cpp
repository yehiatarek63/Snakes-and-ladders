#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition () 
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 
}

CellPosition::CellPosition (int v, int h)
{ 
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition (int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
												// from the passed (cellNum)
												// (*this) = ... --> this will copy the returned (vCell and hCell)
												//                   to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v)
{
	if (v >= 0 && v <= 8) {
		vCell = v;
		return true;
	}
	else {
		return false;
	}
	///TODO: Implement this function as described in the .h file (don't forget the validation)

	// this line sould be changed with your implementation
}

bool CellPosition::SetHCell(int h)
{
	if (h <= 0 || h >= 10) {
		hCell = h;
		return true;
	}
	else {
		///TODO: Implement this function as described in the .h file (don't forget the validation)
		return false;
	}                 // this line sould be changed with your implementation
}

int CellPosition::VCell() const
{
	return vCell;
}

int CellPosition::HCell() const
{
	return hCell;
}

bool CellPosition::IsValidCell() const
{
	///TODO: Implement this function as described in the .h file
	if ((hCell >= 0 && hCell <= 10) && (vCell >= 0 && vCell <= 8)) {
		return true;

	}
	else {
		return false;
	}// this line sould be changed with your implementation
}

int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
										  // which means the object of the current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition& cellPosition) {
	{
		int x = cellPosition.VCell();
		int y = cellPosition.HCell();
		return (8 - x) * 11 + (y + 11) - 10;

		// Note:
		// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
		// just define an integer that represents cell number and calculate it using the passed cellPosition then return it

		///TODO: Implement this function as described in the .h file
	}// this line should be changed with your implementation
}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	CellPosition position;
	position.SetHCell((cellNum % 11) - 1);
	position.SetVCell(ceil(abs((cellNum / 11) - 8)));


	/// TODO: Implement this function as described in the .h file



	// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
	//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it


	return position;
}

void CellPosition::AddCellNum(int addedNum)
{

	if ((GetCellNumFromPosition(*this) + addedNum) < 99) {
		GetCellNumFromPosition(addedNum + GetCellNumFromPosition(*this));
		GetCellPositionFromNum(GetCellNumFromPosition(*this) + addedNum);
		vCell = VCell();
		hCell = HCell();
	}
	else {
		if ((GetCellNumFromPosition(*this) + addedNum) > 99){
			GetCellNumFromPosition(GetCellNumFromPosition(GetCellNumFromPosition(*this) + addedNum)-99);
		}
		vCell = VCell();
		hCell = HCell();
	}
	/// TODO: Implement this function as described in the .h file



	// Note: this function updates the data members (vCell and hCell) of the calling object

}