#include "Action.h"
#include "Grid.h"
#include <fstream>
class SaveGridAction : public Action
{
	Grid* pGrid;
	Output* pOut;
	Input* pIn;
	ofstream OutFile;
	string file_name;
	bool check;
public:
	SaveGridAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
};