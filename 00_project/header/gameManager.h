//============================================================
//
//	ゲームマネージャーヘッダー [gameManager.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "retentionManager.h"

//************************************************************
//	クラス定義
//************************************************************
// ゲームマネージャークラス
class CGameManager
{
public:
	// 状態列挙
	enum EState
	{
		STATE_NONE = 0,		// 何もしない状態
		STATE_NORMAL,		// 通常状態
		STATE_INIT_BURN,	// 全焼初期化状態
		STATE_BURN,			// 全焼状態
		STATE_STAGING,		// 演出状態
		STATE_MAX			// この列挙型の総数
	};

	// コンストラクタ
	CGameManager();

	// デストラクタ
	~CGameManager();

	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void SetBurn(void);	// 全焼状態設定
	EState GetState(void) const;	// 状態取得
	void TransitionResult(void);	// リザルト画面遷移

	// 静的メンバ関数
	static CGameManager *Create(void);	// 生成
	static void Release(CGameManager *&prGameManager);	// 破棄

private:
	// メンバ関数
	void SpownManager(void);	// 敵生成の管理
	void InitBurnManager(void);	// 全焼演出の初期化管理
	void BurnManager(void);		// 全焼演出の管理

	// メンバ変数
	EState m_state;		// 状態
	int Spownlevel;		// 敵生成のレベル
	int SpownCount;		// 敵生成のカウント
	int nFlowerCount;	// 花生成カウント
	float m_fMoveBurn;	// 中心からの燃え広がり量
};

#endif	// _GAMEMANAGER_H_
