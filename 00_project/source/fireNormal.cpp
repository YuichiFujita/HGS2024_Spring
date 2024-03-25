//============================================================
//
//	真っ直ぐ炎処理 [fireNormal.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "fireNormal.h"
#include "manager.h"
#include "renderer.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{

}

//************************************************************
//	子クラス [CFireNormal] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CFireNormal::CFireNormal(const EType type) : CFire(type)
{

}

//============================================================
//	デストラクタ
//============================================================
CFireNormal::~CFireNormal()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CFireNormal::Init(void)
{
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
void CFireNormal::Uninit(void)
{
	// 炎の終了
	CFire::Uninit();
}

//============================================================
//	挙動の更新処理
//============================================================
void CFireNormal::UpdateMove(void)
{
	D3DXVECTOR3 pos = GetVec3Position();	// 位置

	// 位置の更新
	UpdatePosition(&pos);

	// 位置を反映
	SetVec3Position(pos);
}
