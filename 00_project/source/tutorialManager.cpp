//============================================================
//
//	チュートリアルマネージャー処理 [tutorialManager.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "tutorialManager.h"
#include "manager.h"
#include "sound.h"
#include "camera.h"
#include "texture.h"
#include "object2D.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char *TEXTURE_FILE[] =	// テクスチャファイル
	{
		"data\\TEXTURE\\tutorial.png",	// 操作説明テクスチャ
		"data\\TEXTURE\\tutorial001.png",	// 終了説明テクスチャ
	};

	const int PRIORITY = 5;	// チュートリアルの優先順位

	namespace lesson
	{
		const D3DXVECTOR3 POS	= SCREEN_CENT;	// レッスン表示の位置
		const D3DXVECTOR3 SIZE	= SCREEN_SIZE;	// レッスン表示の位置
	}

	namespace control
	{
		const D3DXVECTOR3 POS	= D3DXVECTOR3(1140.0f, 85.0f, 0.0f);	// 操作方法の位置
		const D3DXVECTOR3 SIZE	= D3DXVECTOR3(264.0f, 150.0f, 0.0f);	// 操作方法の位置
	}
}

//************************************************************
//	スタティックアサート
//************************************************************
static_assert(NUM_ARRAY(TEXTURE_FILE) == CTutorialManager::TEXTURE_MAX, "ERROR : Texture Count Mismatch");

//************************************************************
//	親クラス [CTutorialManager] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CTutorialManager::CTutorialManager()
{
	// メンバ変数をクリア
	m_pExplain = nullptr;	// 説明表示の情報
	m_pControl = nullptr;	// 操作説明の情報
}

//============================================================
//	デストラクタ
//============================================================
CTutorialManager::~CTutorialManager()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CTutorialManager::Init(void)
{
	// メンバ変数を初期化
	m_pExplain = nullptr;	// 説明表示の情報
	m_pControl = nullptr;	// 操作説明の情報

	// 説明表示の生成
	m_pExplain = CObject2D::Create
	( // 引数
		lesson::POS,	// 位置
		lesson::SIZE	// 大きさ
	);
	if (m_pExplain == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// テクスチャを登録・割当
	m_pExplain->BindTexture(TEXTURE_FILE[TEXTURE_CONTROL]);

	// 優先順位を設定
	m_pExplain->SetPriority(PRIORITY);

	// 操作説明の生成
	m_pControl = CObject2D::Create
	( // 引数
		control::POS,	// 位置
		control::SIZE	// 大きさ
	);
	if (m_pControl == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// テクスチャを登録・割当
	m_pControl->BindTexture(TEXTURE_FILE[TEXTURE_END]);

	// 優先順位を設定
	m_pControl->SetPriority(PRIORITY);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CTutorialManager::Uninit(void)
{
	// 説明表示の終了
	SAFE_UNINIT(m_pExplain);

	// 操作説明の終了
	SAFE_UNINIT(m_pControl);
}

//============================================================
//	更新処理
//============================================================
void CTutorialManager::Update(void)
{
	// ポインタを宣言
	CInputKeyboard	*pKeyboard	= GET_INPUTKEY;	// キーボード
	CInputPad		*pPad		= GET_INPUTPAD;	// パッド

	if (pKeyboard->IsTrigger(DIK_RETURN)
	||  pPad->IsTrigger(CInputPad::KEY_START)
	||	pPad->IsTrigger(CInputPad::KEY_A))
	{
		// シーンの設定
		GET_MANAGER->SetScene(CScene::MODE_TITLE);	// タイトル画面
	}

	// 説明表示の更新
	m_pExplain->Update();

	// 操作説明の更新
	m_pControl->Update();
}

//============================================================
//	生成処理
//============================================================
CTutorialManager *CTutorialManager::Create(void)
{
	// チュートリアルマネージャーの生成
	CTutorialManager *pTutorialManager = new CTutorialManager;
	if (pTutorialManager == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// チュートリアルマネージャーの初期化
		if (FAILED(pTutorialManager->Init()))
		{ // 初期化に失敗した場合

			// チュートリアルマネージャーの破棄
			SAFE_DELETE(pTutorialManager);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pTutorialManager;
	}
}

//============================================================
//	破棄処理
//============================================================
void CTutorialManager::Release(CTutorialManager *&prTutorialManager)
{
	// チュートリアルマネージャーの終了
	assert(prTutorialManager != nullptr);
	prTutorialManager->Uninit();

	// メモリ開放
	SAFE_DELETE(prTutorialManager);
}
