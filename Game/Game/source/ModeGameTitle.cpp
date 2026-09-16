
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGameTitle.h"
#include "ModeGame.h"
#include "ModeLoading.h"
#include "Input/InputManager.h"

bool ModeGameTitle::Initialize()
{
	if (!base::Initialize()) { return false; }

	_cg = LoadGraph("res/title.png");

	return true;
}

bool ModeGameTitle::Terminate() 
{
	DeleteGraph(_cg);

	base::Terminate();
	return true;
}

bool ModeGameTitle::Process()
{
	base::Process();

	// このモード中はプロセスキップ
	ModeServer::GetInstance()->SkipProcessUnderLayer();
	ModeServer::GetInstance()->SkipRenderUnderLayer();

	// 1Pのパッド情報取得
	const auto& pad_1 = InputManager::GetInstance().GetPad(0);
	if(!pad_1.IsConnected()) { return false; }

	if(pad_1.isTrigger(PadButton::A))
	{
		// このモードを削除予約
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeLoading(), 25, "game");
	}

	return true;
}

bool ModeGameTitle::Render() 
{
	base::Render();



	 //タイトルモード中はバッファーをしない
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);
	SetUseBackCulling(FALSE);

	 //タイトル画面描画
	DrawTitleScreen();

	return true;
}

// タイトル画面描画
void ModeGameTitle::DrawTitleScreen()
{	

	const char* title = "Title";
	const char* titleText = "Game Start";
	const char* text = "Press A to Start";

	SetFontSize(74);
	// 画面中央にタイトルテキストを描画
	DrawString((1920 - GetDrawStringWidth(title, strlen(title))) / 2, 200, title, GetColor(128, 128, 255));

	SetFontSize(48);

	// 画面中央にタイトルテキストを描画
	DrawString((1920 - GetDrawStringWidth(titleText, strlen(titleText))) / 2, 1080 / 2, titleText, GetColor(0, 255, 255));

	// 画面下部に開始テキストを描画
	DrawString((1920 - GetDrawStringWidth(text, strlen(text))) / 2, 800, text, GetColor(255, 255, 0));

	SetFontSize(24);
}

