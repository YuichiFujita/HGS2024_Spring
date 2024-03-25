//============================================================
//
//	ゲームマネージャー処理 [gameManager.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "gameManager.h"
#include "manager.h"
#include "fade.h"
#include "scene.h"
#include "sceneGame.h"
#include "cinemaScope.h"
#include "timerUI.h"
#include "retentionManager.h"
#include "camera.h"
#include "player.h"
#include "multiModel.h"
#include "effect3D.h"
#include "fire.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int GAMEEND_WAIT_FRAME = 180;	// リザルト画面への遷移余韻フレーム

	const int SPOWN_NUM = 2;	// 初期の生成数
	const int SPOWN_RAND_POSX = 300;	// 幅のランダム生成範囲
	const float SPOWN_POSY = 1000.0f;	// 幅のランダム生成範囲
}

//************************************************************
//	親クラス [CGameManager] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CGameManager::CGameManager() :
	m_state	(STATE_NONE)	// 状態
{

}

//============================================================
//	デストラクタ
//============================================================
CGameManager::~CGameManager()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CGameManager::Init(void)
{
	//// ポインタを宣言
	//CPlayer *pPlayer = CScene::GetPlayer();	// プレイヤーの情報

	// メンバ変数を初期化
	m_state = STATE_NORMAL;	// 状態

	//生成レベルを初期化
	Spownlevel = SPOWN_NUM;

	//生成カウントを初期化
	SpownCount = 0;

	//// プレイヤーを出現させる
	//pPlayer->SetSpawn();

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CGameManager::Uninit(void)
{

}

//============================================================
//	更新処理
//============================================================
void CGameManager::Update(void)
{
	switch (m_state)
	{ // 状態ごとの処理
	case STATE_NONE:
	case STATE_STAGING:
		break;

	case STATE_NORMAL:
		SpownManager();
		break;

	default:	// 例外処理
		assert(false);
		break;
	}
}

//============================================================
//	敵生成の管理
//============================================================
void CGameManager::SpownManager()
{
	SpownCount++;

	//レベル管理
	if (SpownCount != 0 && SpownCount % 1200 == 0)
	{
		Spownlevel++;
	}

	//敵生成管理
	if (SpownCount % 300 == 0)
	{
		for (int Spown = 0; Spown < Spownlevel; Spown++)
		{
			float frandPos = (float)(rand() % SPOWN_RAND_POSX + 1);

			CFire::Create
			(
				CFire::EType::TYPE_NORMAL,
				1.0f,
				D3DXVECTOR3
				(
					frandPos - ((float)SPOWN_RAND_POSX * 0.5f),
					SPOWN_POSY,
					0.0f
				)
			);
		}
	}


}

//============================================================
//	状態設定処理
//============================================================
void CGameManager::SetState(const EState state)
{
	// 状態を設定
	m_state = state;
}

//============================================================
//	状態取得処理
//============================================================
CGameManager::EState CGameManager::GetState(void) const
{
	// 状態を返す
	return m_state;
}

//============================================================
//	リザルト画面遷移処理
//============================================================
void CGameManager::TransitionResult(const CRetentionManager::EWin win)
{
	// タイマーの計測終了
	CSceneGame::GetTimerUI()->End();

	// リザルト情報を保存
	GET_RETENTION->SetResult(win, CSceneGame::GetTimerUI()->Get());

	// リザルト画面に遷移
	GET_MANAGER->SetScene(CScene::MODE_RESULT, GAMEEND_WAIT_FRAME);
}

//============================================================
//	生成処理
//============================================================
CGameManager *CGameManager::Create(void)
{
	// ゲームマネージャーの生成
	CGameManager *pGameManager = new CGameManager;
	if (pGameManager == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// ゲームマネージャーの初期化
		if (FAILED(pGameManager->Init()))
		{ // 初期化に失敗した場合

			// ゲームマネージャーの破棄
			SAFE_DELETE(pGameManager);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pGameManager;
	}
}

//============================================================
//	破棄処理
//============================================================
void CGameManager::Release(CGameManager *&prGameManager)
{
	// ゲームマネージャーの終了
	assert(prGameManager != nullptr);
	prGameManager->Uninit();

	// メモリ開放
	SAFE_DELETE(prGameManager);
}
