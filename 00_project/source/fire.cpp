//============================================================
//
//	炎処理 [fire.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "fire.h"
#include "fireNormal.h"
#include "fireFast.h"
#include "fireFluffy.h"
#include "fireMove.h"
#include "manager.h"
#include "renderer.h"
#include "stage.h"
#include "particle3D.h"
#include "sceneGame.h"
#include "gameManager.h"
#include "sound.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int	PRIORITY = 3;		// 炎の優先順位
	const float	MOVE_REV = 0.25f;	// 移動量の減衰係数
	const float	RADIUS	 = 20.0f;	// 半径
}

//************************************************************
//	子クラス [CFire] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CFire::CFire(const EType type) : CObject(CObject::LABEL_FIRE, CObject::DIM_3D, PRIORITY),
	m_type		(type),			// 種類定数
	m_pos		(VEC3_ZERO),	// 位置
	m_move		(VEC3_ZERO),	// 移動量
	m_fSpeed	(0.0f)			// 重力
{

}

//============================================================
//	デストラクタ
//============================================================
CFire::~CFire()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CFire::Init(void)
{
	// メンバ変数を初期化
	m_pos = VEC3_ZERO;	// 位置
	m_move = VEC3_ZERO;	// 移動量
	m_fSpeed = 0.0f;	// 重力

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CFire::Uninit(void)
{
	// 炎を破棄
	Release();
}

//============================================================
//	更新処理
//============================================================
void CFire::Update(void)
{
	//落下の更新
	UpdateFall();

	// 各子クラスごとの更新
	UpdateMove();

	// パーティクルの生成
	CParticle3D::Create(CParticle3D::TYPE_FIRE, m_pos);

	// 削除判定
	if (UpdateDelete())
	{ // 削除された場合

		// 関数抜ける
		return;
	}
}

//============================================================
//	描画処理
//============================================================
void CFire::Draw(CShader * /*pShader*/)
{

}

//============================================================
//	位置の設定処理
//============================================================
void CFire::SetVec3Position(const D3DXVECTOR3& rPos)
{
	m_pos = rPos;
}

//============================================================
//	位置取得処理
//============================================================
D3DXVECTOR3 CFire::GetVec3Position(void) const
{
	return m_pos;
}

//============================================================
//	種類取得処理
//============================================================
int CFire::GetType(void) const
{
	// 種類を返す
	return m_type;
}

//============================================================
//	半径取得処理
//============================================================
float CFire::GetRadius(void) const
{
	// 半径を返す
	return RADIUS;
}

//============================================================
//	生成処理
//============================================================
CFire *CFire::Create
( // 引数
	const EType type,		// 種類
	const float fSpeed,		// 速度
	const D3DXVECTOR3& rPos	// 位置
)
{
	// ポインタを宣言
	CFire *pFire = nullptr;	// 炎情報

	// 炎の生成
	switch (type)
	{ // 種類ごとの処理
	case TYPE_NORMAL:

		// 真っ直ぐ炎を生成
		pFire = new CFireNormal(type);

		break;

	case TYPE_FLUFFY:

		// 真っ直ぐ炎を生成
		pFire = new CFireFluffy(type);

		break;

	case TYPE_FAST:

		// 真っ直ぐ炎を生成
		pFire = new CFireFast(type);

		break;

	case TYPE_MOVE:

		// 真っ直ぐ炎を生成
		pFire = new CFireMove(type);

		break;

	default:	// 例外処理
		assert(false);
		break;
	}

	if (pFire == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// 炎の初期化
		if (FAILED(pFire->Init()))
		{ // 初期化に失敗した場合

			// 炎の破棄
			SAFE_DELETE(pFire);
			return nullptr;
		}

		// 位置を設定
		pFire->SetVec3Position(rPos);

		// 重力を設定
		pFire->m_fSpeed = -fSpeed;

		// 確保したアドレスを返す
		return pFire;
	}
}

//============================================================
//	移動量の設定処理
//============================================================
void CFire::SetMovePosition(const D3DXVECTOR3 &rMove)
{
	// 引数の移動量を設定
	m_move = rMove;
}

//============================================================
//	移動量取得処理
//============================================================
D3DXVECTOR3 CFire::GetMovePosition(void) const
{
	// 移動量を返す
	return m_move;
}

//============================================================
//	位置の更新処理
//============================================================
void CFire::UpdatePosition(D3DXVECTOR3 *pPos)
{
	// 位置を移動
	*pPos += m_move;

	// 移動量を減衰
	m_move.x += (0.0f - m_move.x) * MOVE_REV;
	m_move.z += (0.0f - m_move.z) * MOVE_REV;
}

//============================================================
//	破棄処理
//============================================================
void CFire::Release(void)
{
	// オブジェクトの破棄
	CObject::Release();
}

//============================================================
//	重力の更新処理
//============================================================
void CFire::UpdateFall(void)
{
	// 重力を加算
	m_move.y = m_fSpeed;
}

//============================================================
//	削除の更新処理
//============================================================
bool CFire::UpdateDelete(void)
{
	if (m_pos.y <= CScene::GetStage()->GetFieldPositionHeight(m_pos))
	{ // 着地面より下にいた設定

		// SEの再生
		PLAY_SOUND(CSound::LABEL_SE_END);

		// 炎消す
		Uninit();

		// 全焼状態にする
		CSceneGame::GetGameManager()->SetBurn();

		return true;
	}

	return false;
}
