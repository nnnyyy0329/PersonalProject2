#include "ModeGameClear.h"
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGameTitle.h"
#include "Input/InputManager.h"

bool ModeGameClear::Initialize()
{
	if (!base::Initialize()) { return false; }

	return true;
}

bool ModeGameClear::Terminate()
{
	base::Terminate();

	return true;
}

bool ModeGameClear::Process()
{
	base::Process();

	// このモード中はプロセススキップ
	ModeServer::GetInstance()->SkipProcessUnderLayer();
	ModeServer::GetInstance()->SkipRenderUnderLayer();

	// 1Pのパッド情報取得
	const auto& pad_1 = InputManager::GetInstance().GetPad(0);
	if(!pad_1.IsConnected()) { return false; }

	// Aボタンが押された場合
	if(pad_1.isTrigger(PadButton::B))
	{
		// このモードを削除予約
		ModeServer::GetInstance()->Del(this);

		// タイトルモードを追加
		ModeServer::GetInstance()->Add(new ModeGameTitle(), 5, "title");

	}
	return true;
}

bool ModeGameClear::Render()
{
	base::Render();

	// タイトルモード中はバッファーをしない
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);
	SetUseBackCulling(FALSE);

	SetFontSize(48);

	const char* text = "GAME CLEAR";
	const char* text2 = "Press B to Title";

	// ゲームクリア画面描画
	DrawString((1920 - GetDrawStringWidth(text, strlen(text))) / 2, 200, text, GetColor(0, 255, 0));

	// 画面下部に再開テキストを描画
	DrawString((1920 - GetDrawStringWidth(text2, strlen(text2))) / 2, 300, text2, GetColor(255, 255, 255));

	SetFontSize(24);

	return true;
}