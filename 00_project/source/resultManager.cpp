//============================================================
//
//	リザルトマネージャー処理 [resultManager.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "resultManager.h"
#include "manager.h"
#include "sound.h"
#include "camera.h"
#include "fade.h"
#include "texture.h"
#include "model.h"
#include "object2D.h"
#include "multiValue.h"
#include "timerManager.h"
#include "retentionManager.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char *TEXTURE_FILE[] =	// テクスチャファイル
	{
		"data\\TEXTURE\\result001.png",		// ボス討伐テクスチャ
		"data\\TEXTURE\\result000.png",		// タイム表示テクスチャ
		"data\\TEXTURE\\continue000.png",	// コンテニュー表示テクスチャ
		"data\\TEXTURE\\select000.png",		// YESテクスチャ
		"data\\TEXTURE\\select001.png",		// NOテクスチャ
	};

	const int PRIORITY = 5;	// リザルトの優先順位

	const D3DXCOLOR SETCOL_FADE = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);	// α値の停止値
	const D3DXCOLOR INITCOL_FADE = XCOL_AWHITE;							// α値の初期値
	const D3DXVECTOR3 SIZE_FADE = SCREEN_SIZE - D3DXVECTOR3(50.0f, 300.0f, 0.0f);	// フェードの大きさ

	const float ADD_ALPHA = 0.008f;	// α値の加算量

	const D3DXVECTOR3 POS_SCORE_LOGO = D3DXVECTOR3(340.0f, 250.0f, 0.0f);	// リザルト表示の遅刻回避の位置
	const D3DXVECTOR3 SIZE_SCORE_LOGO = D3DXVECTOR3(500.0f * 0.9f, 150.0f * 0.9f, 0.0f);	// リザルト表示の大きさ
	const D3DXVECTOR3 POS_SCORE = D3DXVECTOR3(590.0f, 250.0f, 0.0f);	// タイム位置
	const D3DXVECTOR3 SIZE_SCORE = D3DXVECTOR3(98.0f, 117.0f, 0.0f);		// タイム数字大きさ
	const D3DXVECTOR3 SPACE_SCORE = D3DXVECTOR3(SIZE_SCORE.x * 0.85f, 0.0f, 0.0f);	// タイム数字空白

	const float SET_SCORE_SCALE = 8.0f;		// リザルト表示の初期拡大率
	const float SUB_SCORE_SCALE = 0.65f;	// リザルト表示拡大率の減算量

	const D3DXVECTOR3 POS_TIME_LOGO = D3DXVECTOR3(280.0f, 480.0f, 0.0f);	// タイムロゴ位置
	const D3DXVECTOR3 SIZE_TIME_LOGO = D3DXVECTOR3(487.5f * 0.9f, 154.7f * 0.9f, 0.0f);	// タイムロゴ大きさ
	const D3DXVECTOR3 POS_TIME = D3DXVECTOR3(590.0f, 480.0f, 0.0f);	// タイム位置
	const D3DXVECTOR3 SIZE_TIME_VAL = D3DXVECTOR3(98.0f, 117.0f, 0.0f);		// タイム数字大きさ
	const D3DXVECTOR3 SIZE_TIME_PART = D3DXVECTOR3(50.0f, 117.0f, 0.0f);		// タイム区切り大きさ
	const D3DXVECTOR3 SPACE_TIME_VAL = D3DXVECTOR3(SIZE_TIME_VAL.x * 0.85f, 0.0f, 0.0f);	// タイム数字空白
	const D3DXVECTOR3 SPACE_TIME_PART = D3DXVECTOR3(SIZE_TIME_PART.x * 0.85f, 0.0f, 0.0f);	// タイム区切り空白

	const float	SET_TIME_SCALE = 8.0f;	// タイム表示の初期拡大率
	const float	SUB_TIME_SCALE = 0.3f;	// タイム表示拡大率の減算量
	const int	TIME_WAIT_CNT = 3;	// タイム表示状態への変更待機フレーム数

	const D3DXVECTOR3 POS_CONT_LOGO = D3DXVECTOR3(SCREEN_CENT.x, 490.0f, 0.0f);	// コンテニューロゴ位置
	const D3DXVECTOR3 SIZE_CONT_LOGO = D3DXVECTOR3(576.0f, 172.0f, 0.0f);		// コンテニューロゴ大きさ
	const D3DXVECTOR3 POS_CONT_YES = D3DXVECTOR3(400.0f, 610.0f, 0.0f);		// コンテニュー表示のYESの位置
	const D3DXVECTOR3 POS_CONT_NO = D3DXVECTOR3(880.0f, 610.0f, 0.0f);		// コンテニュー表示のNOの位置
	const D3DXVECTOR3 SIZE_CONT = D3DXVECTOR3(222.0f, 94.0f, 0.0f);			// コンテニュー表示の大きさ

	const float	SET_CONT_SCALE = 8.0f;	// コンテニュー表示の初期拡大率
	const float	SUB_CONT_SCALE = 0.3f;	// コンテニュー表示拡大率の減算量
	const int	CONT_WAIT_CNT = 3;	// コンテニュー表示状態への変更待機フレーム数

	const D3DXCOLOR CHOICE_COL = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 選択中カラー
	const D3DXCOLOR DEFAULT_COL = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);	// 非選択中カラー
}

//************************************************************
//	スタティックアサート
//************************************************************
static_assert(NUM_ARRAY(TEXTURE_FILE) == CResultManager::TEXTURE_MAX, "ERROR : Texture Count Mismatch");

//************************************************************
//	親クラス [CResultManager] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CResultManager::CResultManager() :
	m_pContLogo(nullptr),		// コンテニューロゴの情報
	m_pScoreLogo(nullptr),		// タイムロゴの情報
	m_pTimeLogo(nullptr),		// タイムロゴの情報
	m_pFade(nullptr),		// フェードの情報
	m_pScore(nullptr),		// スコアの情報
	m_pTime(nullptr),		// タイムの情報
	m_state(STATE_NONE),	// 状態
	m_nSelect(SELECT_YES),	// 現在の選択
	m_nOldSelect(SELECT_YES),	// 前回の選択
	m_fScale(0.0f),			// ポリゴン拡大率
	m_nCounterState(0)				// 状態管理カウンター
{
	// メンバ変数をクリア
	memset(&m_apContinue[0], 0, sizeof(m_apContinue));	// コンテニュー表示の情報
}

//============================================================
//	デストラクタ
//============================================================
CResultManager::~CResultManager()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CResultManager::Init(void)
{
	static D3DXVECTOR3 aPosContinue[] =	// コンテニューの位置
	{
		POS_CONT_YES,	// YES位置
		POS_CONT_NO	,	// NO位置
	};

	// ポインタを宣言
	CTexture *pTexture = GET_MANAGER->GetTexture();	// テクスチャへのポインタ

	// メンバ変数を初期化
	memset(&m_apContinue[0], 0, sizeof(m_apContinue));	// コンテニュー表示の情報
	m_pContLogo = nullptr;		// コンテニューロゴの情報
	m_pScoreLogo = nullptr;		// スコアロゴの情報
	m_pTimeLogo = nullptr;		// タイムロゴの情報
	m_pFade = nullptr;		// フェードの情報
	m_pScore = nullptr;		// スコアの情報
	m_pTime = nullptr;		// タイムの情報
	m_state = STATE_FADEIN;	// 状態
	m_nCounterState = 0;			// 状態管理カウンター
	m_nSelect = SELECT_YES;	// 現在の選択
	m_nOldSelect = SELECT_YES;	// 前回の選択
	m_fScale = 0.0f;			// ポリゴン拡大率

	//--------------------------------------------------------
	//	フェードの生成・設定
	//--------------------------------------------------------
	// フェードの生成
	m_pFade = CObject2D::Create
	( // 引数
		SCREEN_CENT,	// 位置
		SIZE_FADE,		// 大きさ
		VEC3_ZERO,		// 向き
		INITCOL_FADE	// 色
	);
	if (m_pFade == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pFade->SetPriority(PRIORITY);

	//--------------------------------------------------------
	//	リザルト表示の生成・設定
	//--------------------------------------------------------
	// リザルト表示の生成
	m_pScoreLogo = CObject2D::Create
	( // 引数
		POS_SCORE_LOGO,	// 位置
		SIZE_SCORE_LOGO * SET_SCORE_SCALE	// 大きさ
	);
	if (m_pScoreLogo == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// テクスチャを登録・割当
	m_pScoreLogo->BindTexture(pTexture->Regist(TEXTURE_FILE[TEXTURE_SCORE]));

	// 優先順位を設定
	m_pScoreLogo->SetPriority(PRIORITY);

	// 描画をしない設定にする
	m_pScoreLogo->SetEnableDraw(false);

	//--------------------------------------------------------
	//	スコア表示の生成・設定
	//--------------------------------------------------------
	// スコア表示の生成
	m_pScore = CMultiValue::Create
	( // 引数
		CValue::TEXTURE_NORMAL,
		GET_RETENTION->GetScore(),
		3,
		POS_SCORE,						// 位置
		SIZE_SCORE * SET_SCORE_SCALE,	// 数字の大きさ
		SPACE_SCORE						// 数字の空白
	);
	if (m_pScore == nullptr)
	{ // 非使用中の場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pScore->SetPriority(PRIORITY);

	// 描画をしない設定にする
	m_pScore->SetEnableDraw(false);

	//--------------------------------------------------------
	//	タイムロゴ表示の生成・設定
	//--------------------------------------------------------
	// タイムロゴ表示の生成
	m_pTimeLogo = CObject2D::Create
	( // 引数
		POS_TIME_LOGO,					// 位置
		SIZE_TIME_LOGO * SET_TIME_SCALE	// 大きさ
	);
	if (m_pTimeLogo == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// テクスチャを登録・割当
	m_pTimeLogo->BindTexture(pTexture->Regist(TEXTURE_FILE[TEXTURE_TIME]));

	// 優先順位を設定
	m_pTimeLogo->SetPriority(PRIORITY);

	// 描画をしない設定にする
	m_pTimeLogo->SetEnableDraw(false);

	//--------------------------------------------------------
	//	タイム表示の生成・設定
	//--------------------------------------------------------
	// タイマーマネージャーの生成
	m_pTime = CTimerManager::Create
	( // 引数
		CTimerManager::TIME_SEC,			// 設定タイム
		0,									// 制限時間
		POS_TIME,							// 位置
		SIZE_TIME_VAL * SET_TIME_SCALE,		// 数字の大きさ
		SIZE_TIME_PART * SET_TIME_SCALE,	// 区切りの大きさ
		SPACE_TIME_VAL,						// 数字の空白
		SPACE_TIME_PART						// 区切りの空白
	);
	if (m_pTime == nullptr)
	{ // 非使用中の場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pTime->SetPriority(PRIORITY);

	// 描画をしない設定にする
	m_pTime->SetEnableDraw(false);

	// タイムを設定
	if (!m_pTime->SetMSec(GET_RETENTION->GetResult()))
	{ // 設定に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	//--------------------------------------------------------
	//	コンテニューロゴ表示の生成・設定
	//--------------------------------------------------------
	// コンテニューロゴ表示の生成
	m_pContLogo = CObject2D::Create
	( // 引数
		POS_CONT_LOGO,					// 位置
		SIZE_CONT_LOGO * SET_CONT_SCALE	// 大きさ
	);
	if (m_pContLogo == nullptr)
	{ // 生成に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// テクスチャを登録・割当
	m_pContLogo->BindTexture(pTexture->Regist(TEXTURE_FILE[TEXTURE_CONTINUE]));

	// 優先順位を設定
	m_pContLogo->SetPriority(PRIORITY);

	// 描画をしない設定にする
	m_pContLogo->SetEnableDraw(false);

	//--------------------------------------------------------
	//	コンテニュー表示の生成・設定
	//--------------------------------------------------------
	for (int nCntResult = 0; nCntResult < SELECT_MAX; nCntResult++)
	{ // 選択肢の総数分繰り返す

		// コンテニュー表示の生成
		m_apContinue[nCntResult] = CObject2D::Create
		( // 引数
			aPosContinue[nCntResult],	// 位置
			SIZE_CONT * SET_CONT_SCALE	// 大きさ
		);
		if (m_apContinue[nCntResult] == nullptr)
		{ // 生成に失敗した場合

			// 失敗を返す
			assert(false);
			return E_FAIL;
		}

		// 優先順位を設定
		m_apContinue[nCntResult]->SetPriority(PRIORITY);

		// 描画をしない設定にする
		m_apContinue[nCntResult]->SetEnableDraw(false);

		// 色を設定
		m_apContinue[nCntResult]->SetColor(DEFAULT_COL);
	}

	// テクスチャを登録・割当
	m_apContinue[SELECT_YES]->BindTexture(pTexture->Regist(TEXTURE_FILE[TEXTURE_YES]));
	m_apContinue[SELECT_NO]->BindTexture(pTexture->Regist(TEXTURE_FILE[TEXTURE_NO]));

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CResultManager::Uninit(void)
{
	// タイムの破棄
	SAFE_REF_RELEASE(m_pTime);

	for (int nCntResult = 0; nCntResult < SELECT_MAX; nCntResult++)
	{ // 選択肢の総数分繰り返す

		// コンテニュー表示の終了
		SAFE_UNINIT(m_apContinue[nCntResult]);
	}

	// コンテニューロゴ表示の終了
	SAFE_UNINIT(m_pContLogo);

	// すこあロゴ表示の終了
	SAFE_UNINIT(m_pScoreLogo);

	// タイムロゴ表示の終了
	SAFE_UNINIT(m_pTimeLogo);

	// フェードの終了
	SAFE_UNINIT(m_pFade);
}

//============================================================
//	更新処理
//============================================================
void CResultManager::Update(void)
{
	switch (m_state)
	{ // 状態ごとの処理
	case STATE_NONE:	// 何もしない状態

		// 無し

		break;

	case STATE_FADEIN:	// フェードイン状態

		// フェードインの更新
		UpdateFade();

		break;

	case STATE_RESULT:	// リザルト表示状態

		// リザルト表示の更新
		UpdateResult();

		break;

	case STATE_TIME_WAIT:	// タイム表示待機状態

		// 表示待機の更新
		if (UpdateDrawWait(TIME_WAIT_CNT))
		{ // 待機完了の場合

			// タイム表示の拡大率を設定
			m_fScale = SET_TIME_SCALE;

			// タイム表示の描画開始
			m_pTimeLogo->SetEnableDraw(true);
			m_pTime->SetEnableDraw(true);

			// 状態を変更
			m_state = STATE_TIME;	// タイム表示状態
		}

		break;

	case STATE_TIME:	// タイム表示状態

		// タイム表示の更新
		UpdateTime();

		break;

	case STATE_CONTINUE_WAIT:	// コンテニュー表示待機状態

		// 表示待機の更新
		if (UpdateDrawWait(CONT_WAIT_CNT))
		{ // 待機完了の場合

			// 状態を変更
			m_state = STATE_WAIT;	// コンテニュー表示状態
		}

		break;

	case STATE_CONTINUE:	// コンテニュー表示待機状態表示状態

		// コンテニュー表示の更新
		UpdateContinue();

		break;

	case STATE_WAIT:	// 遷移待機状態

		// 遷移決定の更新
		UpdateTransition();

		break;

	default:	// 例外処理
		assert(false);
		break;
	}

	// 遷移決定の更新
	UpdateTransition();

	//for (int nCntResult = 0; nCntResult < SELECT_MAX; nCntResult++)
	//{ // 選択肢の総数分繰り返す

	//	// コンテニュー表示の更新
	//	m_apContinue[nCntResult]->Update();
	//}

	//// コンテニューロゴ表示の更新
	//m_pContLogo->Update();

	// すこあロゴ表示の更新
	m_pScoreLogo->Update();

	// タイムロゴ表示の更新
	m_pTimeLogo->Update();

	// タイムの更新
	m_pTime->Update();

	// フェードの更新
	m_pFade->Update();
}

//============================================================
//	生成処理
//============================================================
CResultManager *CResultManager::Create(void)
{
	// リザルトマネージャーの生成
	CResultManager *pResultManager = new CResultManager;
	if (pResultManager == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// リザルトマネージャーの初期化
		if (FAILED(pResultManager->Init()))
		{ // 初期化に失敗した場合

			// リザルトマネージャーの破棄
			SAFE_DELETE(pResultManager);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pResultManager;
	}
}

//============================================================
//	破棄処理
//============================================================
void CResultManager::Release(CResultManager *&prResultManager)
{
	// リザルトマネージャーの終了
	assert(prResultManager != nullptr);
	prResultManager->Uninit();

	// メモリ開放
	SAFE_DELETE(prResultManager);
}

//============================================================
//	フェードインの更新処理
//============================================================
void CResultManager::UpdateFade(void)
{
	// 変数を宣言
	D3DXCOLOR colFade = m_pFade->GetColor();	// フェードの色

	if (colFade.a < SETCOL_FADE.a)
	{ // 透明量が設定値未満の場合

		// 透明度を加算
		colFade.a += ADD_ALPHA;
	}
	else
	{ // 透明量が設定値以上の場合

		// 透明度を補正
		colFade.a = SETCOL_FADE.a;

		// リザルト表示の描画開始
		m_pScoreLogo->SetEnableDraw(true);
		m_pScore->SetEnableDraw(true);

		// リザルト表示の拡大率を設定
		m_fScale = SET_SCORE_SCALE;

		// 状態を変更
		m_state = STATE_RESULT;	// リザルト表示状態
	}

	// 透明度を反映
	m_pFade->SetColor(colFade);
}

//============================================================
//	リザルト表示の更新処理
//============================================================
void CResultManager::UpdateResult(void)
{
	if (m_fScale > 1.0f)
	{ // 拡大率が最小値より大きい場合

		// 拡大率を減算
		m_fScale -= SUB_SCORE_SCALE;

		// リザルト表示の大きさを設定
		m_pScoreLogo->SetVec3Sizing(SIZE_SCORE_LOGO * m_fScale);
		m_pScore->SetVec3Sizing(SIZE_SCORE * m_fScale);
	}
	else
	{ // 拡大率が最小値以下の場合

		// リザルト表示の大きさを設定
		m_pScoreLogo->SetVec3Sizing(SIZE_SCORE_LOGO);
		m_pScore->SetVec3Sizing(SIZE_SCORE);

		// 状態を変更
		m_state = STATE_TIME_WAIT;	// タイム表示待機状態

		// サウンドの再生
		PLAY_SOUND(CSound::LABEL_SE_DECISION_001);	// 決定音01
	}
}

//============================================================
//	タイム表示処理
//============================================================
void CResultManager::UpdateTime(void)
{
	if (m_fScale > 1.0f)
	{ // 拡大率が最小値より大きい場合

		// 拡大率を減算
		m_fScale -= SUB_TIME_SCALE;

		// タイム表示の大きさを設定
		m_pTimeLogo->SetVec3Sizing(SIZE_TIME_LOGO * m_fScale);
		m_pTime->SetSizingValue(SIZE_TIME_VAL * m_fScale);
		m_pTime->SetSizingPart(SIZE_TIME_PART * m_fScale);
	}
	else
	{ // 拡大率が最小値以下の場合

		// 拡大率を補正
		m_fScale = 1.0f;

		// タイム表示の大きさを設定
		m_pTimeLogo->SetVec3Sizing(SIZE_TIME_LOGO);
		m_pTime->SetSizingValue(SIZE_TIME_VAL);
		m_pTime->SetSizingPart(SIZE_TIME_PART);

		// 状態を変更
		m_state = STATE_CONTINUE_WAIT;	// コンテニュー表示待機状態

		// サウンドの再生
		PLAY_SOUND(CSound::LABEL_SE_DECISION_001);	// 決定音01
	}
}

//============================================================
//	コンテニュー表示処理
//============================================================
void CResultManager::UpdateContinue(void)
{
	if (m_fScale > 1.0f)
	{ // 拡大率が最小値より大きい場合

		// 拡大率を減算
		m_fScale -= SUB_CONT_SCALE;

		// コンテニューロゴ表示の大きさを設定
		m_pContLogo->SetVec3Sizing(SIZE_CONT_LOGO * m_fScale);

		for (int nCntResult = 0; nCntResult < SELECT_MAX; nCntResult++)
		{ // 選択肢の総数分繰り返す

			// コンテニュー表示の大きさを設定
			m_apContinue[nCntResult]->SetVec3Sizing(SIZE_CONT * m_fScale);
		}
	}
	else
	{ // 拡大率が最小値以下の場合

		// 拡大率を補正
		m_fScale = 1.0f;

		// コンテニューロゴ表示の大きさを設定
		m_pContLogo->SetVec3Sizing(SIZE_CONT_LOGO);

		for (int nCntResult = 0; nCntResult < SELECT_MAX; nCntResult++)
		{ // 選択肢の総数分繰り返す

			// コンテニュー表示の大きさを設定
			m_apContinue[nCntResult]->SetVec3Sizing(SIZE_CONT);
		}

		// 状態を変更
		m_state = STATE_WAIT;	// 遷移待機状態

		// サウンドの再生
		PLAY_SOUND(CSound::LABEL_SE_DECISION_001);	// 決定音01
	}
}

//============================================================
//	選択の更新処理
//============================================================
void CResultManager::UpdateSelect(void)
{
	// ポインタを宣言
	CInputKeyboard	*pKeyboard = GET_INPUTKEY;	// キーボード
	CInputPad		*pPad = GET_INPUTPAD;		// パッド

	if (pKeyboard->IsTrigger(DIK_A)
		|| pKeyboard->IsTrigger(DIK_LEFT)
		|| pPad->IsTrigger(CInputPad::KEY_LEFT))
	{ // 左移動の操作が行われた場合

		// 左に選択をずらす
		m_nSelect = (m_nSelect + (SELECT_MAX - 1)) % SELECT_MAX;

		// サウンドの再生
		PLAY_SOUND(CSound::LABEL_SE_SELECT_000);	// 選択操作音00
	}
	if (pKeyboard->IsTrigger(DIK_D)
		|| pKeyboard->IsTrigger(DIK_RIGHT)
		|| pPad->IsTrigger(CInputPad::KEY_RIGHT))
	{ // 右移動の操作が行われた場合

		// 右に選択をずらす
		m_nSelect = (m_nSelect + 1) % SELECT_MAX;

		// サウンドの再生
		PLAY_SOUND(CSound::LABEL_SE_SELECT_000);	// 選択操作音00
	}

	// 前回の選択要素の色を黒に設定
	m_apContinue[m_nOldSelect]->SetColor(DEFAULT_COL);

	// 現在の選択要素の色を白に設定
	m_apContinue[m_nSelect]->SetColor(CHOICE_COL);

	// 現在の選択要素を代入
	m_nOldSelect = m_nSelect;
}

//============================================================
//	遷移決定の更新処理
//============================================================
void CResultManager::UpdateTransition(void)
{
	// ポインタを宣言
	CInputKeyboard	*pKeyboard = GET_INPUTKEY;	// キーボード
	CInputPad		*pPad = GET_INPUTPAD;		// パッド

	if (pKeyboard->IsTrigger(DIK_RETURN)
		|| pKeyboard->IsTrigger(DIK_SPACE)
		|| pPad->IsTrigger(CInputPad::KEY_A)
		|| pPad->IsTrigger(CInputPad::KEY_B)
		|| pPad->IsTrigger(CInputPad::KEY_X)
		|| pPad->IsTrigger(CInputPad::KEY_Y)
		|| pPad->IsTrigger(CInputPad::KEY_START))
	{
		if (m_state != STATE_WAIT)
		{ // 遷移待機状態ではない場合

			// 演出スキップ
			SkipStaging();

			// サウンドの再生
			PLAY_SOUND(CSound::LABEL_SE_DECISION_001);	// 決定音01
		}
		else
		{ // 遷移待機状態の場合

			if (GET_MANAGER->GetFade()->GetState() == CFade::FADE_NONE)
			{ // フェード中ではない場合

					// シーンの設定
				GET_MANAGER->SetScene(CScene::MODE_RANKING);	// ランキング画面

			// サウンドの再生
				PLAY_SOUND(CSound::LABEL_SE_DECISION_000);	// 決定音00
			}
		}
	}
}

//============================================================
//	演出スキップ処理
//============================================================
void CResultManager::SkipStaging(void)
{
	// すこあ・タイム表示をONにする
	m_pScoreLogo->SetEnableDraw(true);
	m_pScore->SetEnableDraw(true);
	m_pTimeLogo->SetEnableDraw(true);
	m_pTime->SetEnableDraw(true);

	// すこあ・タイム表示の大きさを設定
	m_pScoreLogo->SetVec3Sizing(SIZE_SCORE_LOGO);
	m_pScore->SetVec3Sizing(SIZE_SCORE);
	m_pTimeLogo->SetVec3Sizing(SIZE_TIME_LOGO);
	m_pTime->SetSizingValue(SIZE_TIME_VAL);
	m_pTime->SetSizingPart(SIZE_TIME_PART);

	//// コンテニューロゴ表示の描画開始
	//m_pContLogo->SetEnableDraw(true);

	//// コンテニューロゴ表示の大きさを設定
	//m_pContLogo->SetVec3Sizing(SIZE_CONT_LOGO);

	//for (int nCntResult = 0; nCntResult < SELECT_MAX; nCntResult++)
	//{ // 選択肢の総数分繰り返す

	//	// コンテニュー表示の描画開始
	//	m_apContinue[nCntResult]->SetEnableDraw(true);

	//	// コンテニュー表示の大きさを設定
	//	m_apContinue[nCntResult]->SetVec3Sizing(SIZE_CONT);
	//}

	// フェードの透明度を設定
	m_pFade->SetColor(SETCOL_FADE);

	// 状態を変更
	m_state = STATE_WAIT;	// 遷移待機状態
}

//============================================================
//	表示待機処理
//============================================================
bool CResultManager::UpdateDrawWait(const int nWait)
{
	if (m_nCounterState < nWait)
	{ // カウンターが待機カウントまで達していない場合

		// カウンターを加算
		m_nCounterState++;

		// 待機未完了を返す
		return false;
	}
	else
	{ // カウンターが待機完了した場合

		// カウンターを初期化
		m_nCounterState = 0;

		// 待機完了を返す
		return true;
	}
}
