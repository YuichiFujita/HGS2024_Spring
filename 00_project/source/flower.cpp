//============================================================
//
//	花処理 [flower.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "flower.h"
#include "manager.h"
#include "scene.h"
#include "sceneGame.h"
#include "renderer.h"
#include "sound.h"
#include "texture.h"

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
	const char *TEXTURE_FILE = "data\\TEXTURE\\flower000.png";	// 花テクスチャファイル

	const int		  PRIORITY		= 2;	// 花の優先順位
	const D3DXVECTOR3 SIZE_FLOWER	= D3DXVECTOR3(50.0f, 50.0f, 0.0f);	// 半径

	const float		  SHADOW_ALPHA	= 0.2f;	// 影のα値
	const D3DXVECTOR3 SHADOW_SIZE = D3DXVECTOR3(80.0f, 0.0f, 80.0f);	// 影の大きさ

	const float SPAWN_ALPHA	= 0.65f;	// 花の生成時透明度
	const float GLOW_SPEED	= 2.0f;		// 花の生える速度
}
//************************************************************
//	定数宣言
//************************************************************
CListManager<CFlower> *CFlower::m_pList = nullptr;	// オブジェクトリスト

//************************************************************
//	子クラス [CFlower] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CFlower::CFlower() : CObject3D(CObject::LABEL_FLOWER, CObject::DIM_3D, PRIORITY),
	m_state		(EState::NONE)	// 状態
{

}

//============================================================
//	デストラクタ
//============================================================
CFlower::~CFlower()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CFlower::Init(void)
{
	// メンバ変数を初期化
	m_state = EState::SPAWN;	// 状態

	// オブジェクト3Dの初期化
	if (FAILED(CObject3D::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// テクスチャを割当
	BindTexture(TEXTURE_FILE);

	// 原点を設定
	SetOrigin(ORIGIN_DOWN);

	// 大きさを設定
	SetVec3Sizing(SIZE_FLOWER);

	// 透明度を設定
	D3DXCOLOR col = GetColor();
	SetColor(D3DXCOLOR(col.r, col.g, col.b, SPAWN_ALPHA));

	// レンダーステートの情報を取得
	CRenderState *pRenderState = GetRenderState();

	// αテストを有効にする
	pRenderState->SetAlphaTest(true);			// αテストの有効 / 無効の設定
	pRenderState->SetAlphaFunc(D3DCMP_GREATER);	// αテストの設定
	pRenderState->SetAlphaNumRef(160);			// αテストの参照値設定

	// カリングを設定
	pRenderState->SetCulling(D3DCULL_NONE);

	// ライティングを設定
	pRenderState->SetLighting(false);

	// Zテストを設定
	pRenderState->SetZFunc(D3DCMP_LESSEQUAL);

	// Zバッファの使用状況を設定
	pRenderState->SetZUpdate(true);

	if (m_pList == nullptr)
	{ // リストマネージャーが存在しない場合

		// リストマネージャーの生成
		m_pList = CListManager<CFlower>::Create();
		if (m_pList == nullptr)
		{ // 生成に失敗した場合

			// 失敗を返す
			assert(false);
			return E_FAIL;
		}
	}

	// リストに自身のオブジェクトを追加・イテレーターを取得
	m_iterator = m_pList->AddList(this);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CFlower::Uninit(void)
{
	// リストから自身のオブジェクトを削除
	m_pList->DeleteList(m_iterator);

	if (m_pList->GetNumAll() == 0)
	{ // オブジェクトが一つもない場合

		// リストマネージャーの破棄
		m_pList->Release(m_pList);
	}

	// オブジェクト3Dの終了
	CObject3D::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CFlower::Update(void)
{
	// 変数を宣言
	D3DXVECTOR3 pos = GetVec3Position();	// 位置
	float fLand = CScene::GetStage()->GetFieldPositionHeight(pos);	// 着地点

	switch (m_state)
	{ // 状態ごとの処理
	case CFlower::NONE:
	{
		// 高さを地面に設定
		pos.y = fLand;

		break;
	}
	case CFlower::SPAWN:
	{
		// 地面からはやす
		pos.y += GLOW_SPEED;
		if (pos.y >= fLand)
		{ // 位置が着地点を超えた場合

			// 位置補正
			pos.y = fLand;

			// 透明度を設定
			D3DXCOLOR col = GetColor();
			SetColor(D3DXCOLOR(col.r, col.g, col.b, 1.0f));

			// 何もしない状態にする
			m_state = EState::NONE;
		}

		break;
	}
	case CFlower::BURN:
	{
		// 色を設定
		D3DXCOLOR col = GetColor();
		col -= D3DXCOLOR(0.05f, 0.05f, 0.05f, 0.0f);
		SetColor(col);

		if (col.r <= 0.2f)
		{ // 色が黒の場合

			SetColor(D3DXCOLOR(0.2f, 0.2f, 0.2f, GetColor().a));

			// フェードアウト状態にする
			m_state = EState::FADE;
		}

		break;
	}
	case CFlower::FADE:
	{
		// 地面からはやす
		pos.y -= 1.0f;

		// 色を設定
		D3DXCOLOR col = GetColor();
		col.a -= 0.05f;
		SetColor(col);

		if (col.a <= 0.0f)
		{ // 透明度が下がりきった場合

			// 自身を終了
			Uninit();
			return;
		}

		break;
	}
	default:
		assert(false);
		break;
	}

	// 位置を更新
	SetVec3Position(pos);

	// オブジェクト3Dの更新
	CObject3D::Update();
}

//============================================================
//	描画処理
//============================================================
void CFlower::Draw(CShader *pShader)
{
	// オブジェクト3Dの描画
	CObject3D::Draw(pShader);
}

//============================================================
//	状態取得処理
//============================================================
int CFlower::GetState(void) const
{
	return (int)m_state;
}

//============================================================
//	半径取得処理
//============================================================
float CFlower::GetRadius(void) const
{
	return SIZE_FLOWER.x;
}

//============================================================
//	生成処理
//============================================================
CFlower *CFlower::Create
(
	const D3DXVECTOR3& rPos,	// 位置
	const D3DXVECTOR3& rRot		// 向き
)
{
	// 変数を宣言
	D3DXVECTOR3 pos = rPos;	// 座標設定用

	// 花の生成
	CFlower *pFlower = new CFlower;
	if (pFlower == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// 花の初期化
		if (FAILED(pFlower->Init()))
		{ // 初期化に失敗した場合

			// 花の破棄
			SAFE_DELETE(pFlower);
			return nullptr;
		}

		// 位置を設定
		pos.y  = CScene::GetStage()->GetFieldPositionHeight(pos);	// 高さを地面に設定
		pos.y -= SIZE_FLOWER.y;	// 地面に埋める
		pFlower->SetVec3Position(pos);

		// 向きを設定
		pFlower->SetVec3Rotation(rRot);

		// 確保したアドレスを返す
		return pFlower;
	}
}

//============================================================
//	リスト取得処理
//============================================================
CListManager<CFlower> *CFlower::GetList(void)
{
	// オブジェクトリストを返す
	return m_pList;
}

//============================================================
//	ランダム生成処理
//============================================================
void CFlower::RandomSpawn(const int nNum)
{
	CStage *pStage = CScene::GetStage();					// ステージ情報
	CStage::SStageLimit limit = pStage->GetStageLimit();	// ステージ範囲
	int nLimit = (int)limit.fRadius;		// ステージ半径
	D3DXVECTOR3 posTarget = limit.center;	// 中心座標
	D3DXVECTOR3 posSet;	// 位置設定用
	D3DXVECTOR3 rotSet;	// 向き設定用

	for (int nCntGrow = 0; nCntGrow < nNum; nCntGrow++)
	{ // 生成数分繰り返す

		// 生成位置を設定
		posSet.x = (float)(rand() % (nLimit * 2) - nLimit + 1);
		posSet.y = 0.0f;
		posSet.z = (float)(rand() % (nLimit * 2) - nLimit + 1);

		// 生成位置を補正
		collision::CirclePillar(posSet, posTarget, SIZE_FLOWER.x, 10.0f);	// ターゲット内部の生成防止
		CScene::GetStage()->LimitPosition(posSet, SIZE_FLOWER.x);	// ステージ範囲外の生成防止

		// 生成向きを設定
		rotSet = D3DXVECTOR3(0.0f, atan2f(posSet.x - posTarget.x, posSet.z - posTarget.z), 0.0f);

		// 花オブジェクトの生成
		CFlower::Create(posSet, rotSet);
	}
}
