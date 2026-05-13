#pragma once
#include "appframe.h"

/// @brief メインのゲームモード
class ModeGame : public ModeBase
{
	typedef ModeBase base;
public:

	ModeGame();
	virtual ~ModeGame();

	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:

};

