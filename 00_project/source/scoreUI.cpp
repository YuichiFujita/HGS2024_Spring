//============================================================
//
//	タイマーUI処理 [timerUI.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "scoreUI.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "object2D.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char *TEXTURE_FILE[] =	// テクスチャファイル
	{
		"data\\TEXTURE\\timer001.png",	// 背景テクスチャ
	};

	const int PRIORITY = 5;	// タイマーUIの優先順位
}

//************************************************************
//	スタティックアサート
//************************************************************
static_assert(NUM_ARRAY(TEXTURE_FILE) == CScoreUI::TEXTURE_MAX, "ERROR : Texture Count Mismatch");

//************************************************************
//	子クラス [CScoreUI] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CScoreUI::CScoreUI() :
	m_pBG		(nullptr),	// 背景の情報
	m_offsetBG	(VEC3_ZERO)	// 背景のオフセット
{

}

//============================================================
//	デストラクタ
//============================================================
CScoreUI::~CScoreUI()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CScoreUI::Init(void)
{
	// メンバ変数を初期化
	m_pBG = nullptr;		// 背景の情報
	m_offsetBG = VEC3_ZERO;	// 背景のオフセット

	// 背景の生成
	m_pBG = CObject2D::Create(VEC3_ZERO);
	if (m_pBG == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// テクスチャを登録・割当
	m_pBG->BindTexture(TEXTURE_FILE[TEXTURE_BG]);

	// タイマーマネージャーの初期化
	if (FAILED(CMultiValue::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	SetLabel(LABEL_UI);

	// 優先順位を設定
	SetPriority(PRIORITY);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CScoreUI::Uninit(void)
{
	// 背景の終了
	SAFE_UNINIT(m_pBG);

	// タイマーマネージャーの終了
	CMultiValue::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CScoreUI::Update(void)
{
	// 背景の更新
	m_pBG->Update();

	// タイマーマネージャーの更新
	CMultiValue::Update();
}

//============================================================
//	更新状況の設定処理
//============================================================
void CScoreUI::SetEnableUpdate(const bool bUpdate)
{
	// 背景の更新状況を設定
	m_pBG->SetEnableUpdate(bUpdate);

	// 更新状況の設定
	CMultiValue::SetEnableUpdate(bUpdate);
}

//============================================================
//	描画状況の設定処理
//============================================================
void CScoreUI::SetEnableDraw(const bool bDraw)
{
	// 背景の更新状況を設定
	m_pBG->SetEnableDraw(bDraw);

	// 描画状況の設定
	CMultiValue::SetEnableDraw(bDraw);
}

//============================================================
//	生成処理
//============================================================
CScoreUI *CScoreUI::Create
(
	const int nNum,					// 数字
	const int nDigit,				// 桁数
	const D3DXVECTOR3& rPos,		// 位置
	const D3DXVECTOR3& rSize,		// 大きさ
	const D3DXVECTOR3& rSpace,		// 行間
	const D3DXVECTOR3& rRot,	// 向き
	const D3DXCOLOR& rCol		// 色
)
{
	// タイマーUIの生成
	CScoreUI *pTimerUI = new CScoreUI;
	if (pTimerUI == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// タイマーUIの初期化
		if (FAILED(pTimerUI->Init()))
		{ // 初期化に失敗した場合

			// タイマーUIの破棄
			SAFE_DELETE(pTimerUI);
			return nullptr;
		}

		// 桁数を設定
		pTimerUI->SetDigit(nDigit);

		// 数字を設定
		pTimerUI->SetNum(nNum);

		// テクスチャを設定
		pTimerUI->SetTexture(CValue::ETexture::TEXTURE_NORMAL);

		// 向きを設定
		pTimerUI->SetVec3Rotation(rRot);

		// 大きさを設定
		pTimerUI->SetVec3Sizing(rSize);

		// 色を設定
		pTimerUI->SetColor(rCol);

		// 行間を設定
		pTimerUI->SetSpace(rSpace);

		// 位置を設定
		pTimerUI->SetVec3Position(rPos);

		// 確保したアドレスを返す
		return pTimerUI;
	}
}

//============================================================
//	破棄処理
//============================================================
void CScoreUI::Release(CScoreUI *&prTimerUI)
{
	// タイマーUIの終了
	assert(prTimerUI != nullptr);
	prTimerUI->Uninit();

	// メモリ開放
	SAFE_DELETE(prTimerUI);
}

//============================================================
//	オフセットの設定処理
//============================================================
void CScoreUI::SetOffset(const D3DXVECTOR3& rOffset)
{
	// オフセットの設定
	m_offsetBG = rOffset;
}

//============================================================
//	背景の大きさ設定処理
//============================================================
void CScoreUI::SetSizingBG(const D3DXVECTOR3& rSize)
{
	// 背景の大きさを設定
	assert(m_pBG != nullptr);
	m_pBG->SetVec3Sizing(rSize);
}
