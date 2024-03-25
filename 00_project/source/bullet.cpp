//============================================================
//
//	弾処理 [bullet.cpp]
//	Author：佐久間優香
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "bullet.h"
#include "manager.h"
#include "scene.h"
#include "sceneGame.h"
#include "renderer.h"
#include "sound.h"
#include "texture.h"
#include "effect3D.h"

#include "collision.h"
#include "player.h"
#include "shadow.h"
#include "field.h"
#include "stage.h"
#include "particle3D.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int	PRIORITY		= 2;	// 弾の優先順位
	const float SIZE_BULLET	= 50.0f;		// 半径
	const int	LIFE = 10;					// 寿命
	const D3DXCOLOR CLO = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//色
	
}

//============================================================
//	コンストラクタ
//============================================================
CBullet::CBullet() : CObject(CObject::LABEL_EFFECT, CObject::DIM_3D, PRIORITY),
	m_pos(VEC3_ZERO),	// 位置
	m_move(VEC3_ZERO),	// 移動量
	m_rot(VEC3_ZERO)	// 向き
{

}

//============================================================
//	デストラクタ
//============================================================
CBullet::~CBullet()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CBullet::Init(void)
{
	m_pos = VEC3_ZERO;	// 位置
	m_move = VEC3_ZERO;	// 移動量

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CBullet::Uninit(void)
{
	Release();
}

//============================================================
//	更新処理
//============================================================
void CBullet::Update(void)
{
	CEffect3D::Create(m_pos,
		SIZE_BULLET,
		CEffect3D::TYPE_BUBBLE,
		LIFE, m_move,
		m_rot,
		CLO,
		0.0f,
		CRenderState::BLEND_ADD);
}

//============================================================
//	描画処理
//============================================================
void CBullet::Draw(CShader */*pShader*/)
{
	
}

//============================================================
//	生成処理
//============================================================
CBullet* CBullet::Create
(
	const D3DXVECTOR3& rPos,	// 位置
	const D3DXVECTOR3& rRot		// 向き
)
{
	// ポインタを宣言
	CBullet* pBullet = new CBullet;	// 弾情報

	if (pBullet == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// 炎の初期化
		if (FAILED(pBullet->Init()))
		{ // 初期化に失敗した場合

			// 炎の破棄
			SAFE_DELETE(pBullet);
			return nullptr;
		}

		// 位置を設定
		pBullet->SetVec3Position(rPos);

		pBullet->SetVec3Rotation(rRot);

		// 確保したアドレスを返す
		return pBullet;
	}
}

//============================================================
//	破棄処理
//============================================================
void CBullet::Release(void)
{
	// オブジェクトの破棄
	CObject::Release();
}