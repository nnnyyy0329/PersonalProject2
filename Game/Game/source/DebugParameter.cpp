#include "DebugParameter.h"
#include "DxLib.h"

void DebugParameter::AddParamItem(const std::string& name, std::function<std::string()> getter)
{
	m_items.emplace_back(name, getter);
}

void DebugParameter::Render(int x, int y)
{
	for(size_t i = 0; i < m_items.size(); ++i)
	{
		const int lineHeight = 20;
		const unsigned int color = GetColor(255, 255, 255);

		// 値取得関数を実行して最新の値を取得
		std::string value = m_items[i].second();

		// 名前: 値 の形で文字列を描画
		DrawString(x, y + static_cast<int>(i) * lineHeight, (m_items[i].first + ": " + value).c_str(), color);
	}
}