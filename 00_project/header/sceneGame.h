//============================================================
//
//	ゲーム画面ヘッダー [sceneGame.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _SCENE_GAME_H_
#define _SCENE_GAME_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "scene.h"

//************************************************************
//	前方宣言
//************************************************************
class CGameManager;	// ゲームマネージャークラス
class CTimerUI;		// タイマーUIクラス
class CCinemaScope;	// シネマスコープクラス
class CPause;		// ポーズクラス
class CHitStop;		// ヒットストップクラス
class CFlash;		// フラッシュクラス
class CMultiValue;	// スコアクラス

//************************************************************
//	クラス定義
//************************************************************
// ゲーム画面クラス
class CSceneGame : public CScene
{
public:
	// コンストラクタ
	explicit CSceneGame(const EMode mode);

	// デストラクタ
	~CSceneGame() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(void) override;		// 更新
	void Draw(void) override;		// 描画

	// 静的メンバ関数
	static CGameManager	*GetGameManager(void);	// ゲームマネージャー取得
	static CMultiValue	*GetScoreUI(void);		// スコアUI取得
	static CTimerUI		*GetTimerUI(void);		// タイマーUI取得
	static CCinemaScope	*GetCinemaScope(void);	// シネマスコープ取得
	static CPause		*GetPause(void);		// ポーズ取得
	static CHitStop		*GetHitStop(void);		// ヒットストップ取得
	static CFlash		*GetFlash(void);		// フラッシュ取得

private:
	// 静的メンバ変数
	static CGameManager	*m_pGameManager;	// ゲームマネージャー
	static CMultiValue	*m_pScoreUI;		// スコアUI
	static CTimerUI		*m_pTimerUI;		// タイマーUI
	static CCinemaScope	*m_pCinemaScope;	// シネマスコープ
	static CPause		*m_pPause;			// ポーズ
	static CHitStop		*m_pHitStop;		// ヒットストップ
	static CFlash		*m_pFlash;			// フラッシュ
};

#endif	// _SCENE_GAME_H_
