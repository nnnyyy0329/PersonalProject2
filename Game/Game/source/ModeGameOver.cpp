#include "ModeGameOver.h"
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "ModeGameTitle.h"
#include "Input/InputManager.h"

bool ModeGameOver::Initialize()
{
	if (!base::Initialize()) { return false; }
	return true;
}

bool ModeGameOver::Terminate()
{
	base::Terminate();
	return true;
}

bool ModeGameOver::Process()
{
	base::Process();

	// このモード中はプロセススキップ
	ModeServer::GetInstance()->SkipProcessUnderLayer();
	ModeServer::GetInstance()->SkipRenderUnderLayer();

	// 1Pのパッド情報取得
	const auto& pad_1 = InputManager::GetInstance().GetPad(0);
	if(!pad_1.IsConnected()) { return false; }

	if(pad_1.isTrigger(PadButton::B))
	{
		// このモードを削除予約
		ModeServer::GetInstance()->Del(this);

		// タイトルモードを追加
		ModeServer::GetInstance()->Add(new ModeGameTitle(), 50, "title");

		//ModeServer::GetInstance()->Add(new ModeGame(), 1, "game");

	}
	return true;
}

bool ModeGameOver::Render()
{
	base::Render();
	// タイトルモード中はバッファーをしない
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);
	SetUseBackCulling(FALSE);

	SetFontSize(48);

	const char* text = "GAME OVER";
	const char* text2 = "Press B to Title";

	// ゲームオーバー画面描画
	DrawString((1920 - GetDrawStringWidth(text, strlen(text))) / 2, 200, text, GetColor(255, 0, 0));

	// 画面下部に再開テキストを描画
	DrawString((1920 - GetDrawStringWidth(text2, strlen(text2))) / 2, 800, text2, GetColor(255, 255, 0));

	SetFontSize(24);

	return true;
}