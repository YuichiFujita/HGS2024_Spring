//============================================================
//
//	リザルト画面処理 [sceneResult.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "sceneResult.h"
#include "manager.h"
#include "texture.h"
#include "sound.h"
#include "camera.h"
#include "resultManager.h"

//************************************************************
//	静的メンバ変数宣言
//************************************************************
CResultManager *CSceneResult::m_pResultManager = nullptr;	// リザルトマネージャー

//************************************************************
//	子クラス [CSceneResult] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CSceneResult::CSceneResult(const EMode mode) : CScene(mode)
{

}

//============================================================
//	デストラクタ
//============================================================
CSceneResult::~CSceneResult()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CSceneResult::Init(void)
{
	//--------------------------------------------------------
	//	リザルトの初期化
	//--------------------------------------------------------
	// リザルトマネージャーの生成
	m_pResultManager = CResultManager::Create();
	if (m_pResultManager == nullptr)
	{ // 非使用中の場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// シーンの初期化
	CScene::Init();

	//--------------------------------------------------------
	//	初期設定
	//--------------------------------------------------------
	// カメラを設定
	GET_MANAGER->GetCamera()->SetState(CCamera::STATE_ROTATE);	// カメラを回転状態に設定
	GET_MANAGER->GetCamera()->SetDestRotate();					// 目標位置を設定

	// BGMの再生
	PLAY_SOUND(CSound::LABEL_BGM_GENERAL);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CSceneResult::Uninit(void)
{
	// リザルトマネージャーの破棄
	SAFE_REF_RELEASE(m_pResultManager);

	// シーンの終了
	CScene::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CSceneResult::Update(void)
{
	// リザルトマネージャーの更新
	assert(m_pResultManager != nullptr);
	m_pResultManager->Update();

	// シーンの更新
	CScene::Update();
}

//============================================================
//	描画処理
//============================================================
void CSceneResult::Draw(void)
{

}

//============================================================
//	リザルトマネージャー取得処理
//============================================================
CResultManager *CSceneResult::GetResultManager(void)
{
	// インスタンス未使用
	assert(m_pResultManager != nullptr);

	// リザルトマネージャーを返す
	return m_pResultManager;
}
