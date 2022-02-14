#include "Action.h"
#include "Grid.h"
#include <fstream>
class LoadGridAction : public Action
{
	string file_name;
	ifstream InFile;
	Grid* pGrid;
	Output* pOut;
	Input* pIn;
	bool check;
public:
	LoadGridAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
};