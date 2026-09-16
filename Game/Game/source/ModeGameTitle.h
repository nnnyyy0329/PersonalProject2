
#include "appframe.h"


class ModeGameTitle : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	void DrawTitleScreen(); // ƒ^ƒCƒgƒ‹‰æ–Ê•`‰æ

protected:

	int _cg;

}; 
