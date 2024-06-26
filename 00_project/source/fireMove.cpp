//============================================================
//
//	等速移動炎処理 [fireMove.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "fireMove.h"
#include "manager.h"
#include "renderer.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{

}

//************************************************************
//	子クラス [CFireMove] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CFireMove::CFireMove(const EType type) : CFire(type)
{

}

//============================================================
//	デストラクタ
//============================================================
CFireMove::~CFireMove()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CFireMove::Init(void)
{
	m_moveDef = VEC3_ZERO;	// 元の移動量

	// 炎の初期化
	if (FAILED(CFire::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CFireMove::Uninit(void)
{
	// 炎の終了
	CFire::Uninit();
}

//============================================================
//	挙動の更新処理
//============================================================
void CFireMove::UpdateMove(void)
{
	D3DXVECTOR3 pos = GetVec3Position();	// 位置

	CFire::SetMovePosition(m_moveDef);

	// 位置の更新
	UpdatePosition(&pos);

	// 位置を反映
	SetVec3Position(pos);
}
