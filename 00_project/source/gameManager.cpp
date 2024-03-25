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
#include "hitStop.h"
#include "flash.h"
#include "wave.h"
#include "flower.h"
#include "collision.h"

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
	// メンバ変数を初期化
	m_state = STATE_NORMAL;	// 状態

	//生成レベルを初期化
	Spownlevel = SPOWN_NUM;

	//生成カウントを初期化
	SpownCount = 0;

	// 中心からの燃え広がり量
	m_fMoveBurn = 0.0f;

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

	case STATE_INIT_BURN:

		// 全焼演出の初期化の管理
		InitBurnManager();

		break;

	case STATE_BURN:

		// 全焼演出の管理
		BurnManager();

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
//	全焼状態の設定
//============================================================
void CGameManager::SetBurn(void)
{
	// カメラ揺れを設定
	GET_MANAGER->GetCamera()->SetSwing(CCamera::TYPE_MAIN, CCamera::SSwing(10.0f, 1.5f, 0.3f));

	// ヒットストップを設定
	CSceneGame::GetHitStop()->SetStop(45);

	// フラッシュを設定
	CSceneGame::GetFlash()->Set(0.55f, 0.08f);

	// 炎を削除
	std::vector<CObject::ELabel> delVector;
	delVector.push_back(CObject::LABEL_FIRE);
	CObject::ReleaseAll(delVector);

	// 全焼初期化状態にする
	m_state = STATE_INIT_BURN;
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
//	全焼演出の初期化の管理
//============================================================
void CGameManager::InitBurnManager(void)
{
	if (!CSceneGame::GetHitStop()->IsStop())
	{ // ヒットストップが終わったら

		// 波動生成
		CWave::Create(CWave::TEXTURE_IMPACT, D3DXVECTOR3(0.0f, 120.0f, 0.0f), VEC3_ZERO, D3DXCOLOR(1.0f, 0.15f, 0.025f, 0.7f), CWave::SGrow(70.0f, 14.0f, 0.02f), POSGRID2(32, 1), ring::TEX_PART, ring::HOLE_RADIUS, ring::THICKNESS, 40.0f);
		//CWave::Create(CWave::TEXTURE_IMPACT, D3DXVECTOR3(0.0f, 90.0f, 0.0f),  VEC3_ZERO, D3DXCOLOR(1.0f, 0.15f, 0.025f, 0.7f), CWave::SGrow(40.0f, 12.0f, 0.03f), POSGRID2(32, 1), ring::TEX_PART, ring::HOLE_RADIUS, ring::THICKNESS, 40.0f);
		CWave::Create(CWave::TEXTURE_IMPACT, D3DXVECTOR3(0.0f, 60.0f, 0.0f),  VEC3_ZERO, D3DXCOLOR(1.0f, 0.15f, 0.025f, 0.7f), CWave::SGrow(10.0f, 10.0f, 0.04f), POSGRID2(32, 1), ring::TEX_PART, ring::HOLE_RADIUS, ring::THICKNESS, 40.0f);

		// 全焼開始
		m_state = STATE_BURN;
	}
}

//============================================================
//	全焼演出の管理
//============================================================
void CGameManager::BurnManager(void)
{
	// 中心からの燃え広がり量を広げる
	m_fMoveBurn += 45.0f;

	// 花のリスト取得
	CListManager<CFlower> *pList = CFlower::GetList();
	if (pList == nullptr) { return; }

	std::list<CFlower*> list = pList->GetList();
	for (auto pFlower : list)
	{ // 全要素分繰り返す

		// 状態が変更されている場合抜ける
		CFlower::EState state = (CFlower::EState)pFlower->GetState();
		if (state != CFlower::EState::NONE) { continue; }

		// 判定
		bool bHit = collision::Circle2D
		(
			pFlower->GetVec3Position(),
			VEC3_ZERO,
			pFlower->GetRadius(),
			m_fMoveBurn
		);
		if (bHit)
		{ // 当たった場合

			// もえもえにする
			pFlower->Burn();
		}
	}
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
