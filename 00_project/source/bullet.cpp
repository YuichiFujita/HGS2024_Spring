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
	const int	LIFE = 5;					// 寿命
	const D3DXCOLOR CLO = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//色
}

//============================================================
//	コンストラクタ
//============================================================
CBullet::CBullet() : CObject(CObject::LABEL_BULLET, CObject::DIM_3D, PRIORITY),
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
	m_move.y -= 0.98f;

	m_pos += m_move;

	CEffect3D::Create
	(
		m_pos,
		m_Radius,
		m_type,
		LIFE,
		VEC3_ZERO,
		m_rot,
		CLO
	);

	CollisionFire();
}

//============================================================
//	炎との当たり判定
//============================================================
void CBullet::CollisionFire(void)
{
	for (int nCntPri = 0; nCntPri < object::MAX_PRIO; nCntPri++)
	{ // 優先順位の総数分繰り返す
		// ポインタを宣言
		CObject* pObjectTop = CObject::GetTop(DIM_3D, nCntPri);	// 先頭オブジェクト
		if (pObjectTop != NULL)
		{ // 先頭が存在する場合

			// ポインタを宣言
			CObject* pObjCheck = pObjectTop;	// オブジェクト確認用

			while (pObjCheck != NULL)
			{ // オブジェクトが使用されている場合繰り返す

				// ポインタを宣言
				CObject* pObjectNext = pObjCheck->GetNext();	// 次オブジェクト

				if (pObjCheck->GetLabel() == CObject::LABEL_FIRE)
				{ // オブジェクトラベルが地盤ではない場合

					D3DXVECTOR3 posFire = pObjCheck->GetVec3Position();	// 敵位置

					if (collision::Circle3D(m_pos, posFire, 25.0f, 25.0f) == true)
					{
						pObjCheck->Uninit();
					}
				}

				// 次のオブジェクトへのポインタを代入
				pObjCheck = pObjectNext;
			}
		}
	}
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
	const D3DXVECTOR3& rPos,		// 位置
	const float			fRadius,	// 半径
	const CEffect3D::EType	type,	// テクスチャ
	const int			nLife,			// 寿命
	const D3DXVECTOR3& rMove	// 移動量
)	// 生成
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

		//// 位置を設定
		//pBullet->SetVec3Position(rPos);

		//pBullet->SetVec3Rotation(VEC3_ZERO);

		pBullet->m_pos = rPos;
		pBullet->m_Radius = fRadius;
		pBullet->m_type = type;
		pBullet->m_nLife = nLife;
		pBullet->m_move = rMove;

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