#include "ShadowMapRenderer.h"

bool ShadowMapRenderer::Initialize()
{
	// シャドウマップの作成
	m_shadowMapHandle = MakeShadowMap(2048, 2048);
	if(m_shadowMapHandle == -1){ return false; }

	return true;
}

bool ShadowMapRenderer::Terminate()
{
	// シャドウマップの解放
	if(m_shadowMapHandle != -1)
	{
		DeleteShadowMap(m_shadowMapHandle);
		m_shadowMapHandle = -1;
	}

	return true;
}

void ShadowMapRenderer::BeginRender(const VECTOR& lightDirection)
{
	// シャドウマップ描画開始
	SetShadowMapLightDirection(m_shadowMapHandle, lightDirection);

	// シャドウマップ描画範囲の設定
	SetShadowMapDrawArea(
		m_shadowMapHandle,
		VGet(-500.0f, -1.0f, -500.0f), 
		VGet(500.0f, 500.0f, 500.0f));

	// シャドウマップ描画の準備
	ShadowMap_DrawSetup(m_shadowMapHandle);
}

void ShadowMapRenderer::EndRender()
{
	// シャドウマップ描画終了
	ShadowMap_DrawEnd();

	// シャドウマップの使用を解除
	SetUseShadowMap(0, m_shadowMapHandle);
}

void ShadowMapRenderer::SetShadowMap()
{
	// シャドウマップをセット
	SetUseShadowMap(0, m_shadowMapHandle);
}