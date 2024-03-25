//============================================================
//
//	タイマーUIヘッダー [timerUI.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _SCORE_UI_H_
#define _SCORE_UI_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "multiValue.h"

//************************************************************
//	前方宣言
//************************************************************
class CObject2D;	// オブジェクト2Dクラス

//************************************************************
//	クラス定義
//************************************************************
// タイマーUIクラス
class CScoreUI : public CMultiValue
{
public:
	// テクスチャ列挙
	enum ETexture
	{
		TEXTURE_BG = 0,	// 背景テクスチャ
		TEXTURE_MAX		// この列挙型の総数
	};

	// コンストラクタ
	CScoreUI();

	// デストラクタ
	~CScoreUI() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(void) override;		// 更新
	void SetEnableUpdate(const bool bUpdate) override;	// 更新状況設定
	void SetEnableDraw(const bool bDraw) override;		// 描画状況設定

	// 静的メンバ関数
	static CScoreUI *Create	// 生成
	( // 引数
		const int nNum,					// 数字
		const int nDigit,				// 桁数
		const D3DXVECTOR3& rPos,		// 位置
		const D3DXVECTOR3& rSize,		// 大きさ
		const D3DXVECTOR3& rSpace,		// 行間
		const D3DXVECTOR3& rRot,	// 向き
		const D3DXCOLOR& rCol		// 色
	);
	static void Release(CScoreUI *&prTimerUI);	// 破棄

	// メンバ関数
	void SetOffset(const D3DXVECTOR3& rOffset);	// オフセット設定
	void SetSizingBG(const D3DXVECTOR3& rSize);	// 背景大きさ設定

private:
	// メンバ関数

	// メンバ変数
	CObject2D *m_pBG;		// 背景の情報
	D3DXVECTOR3 m_offsetBG;	// 背景のオフセット
};

#endif	// _TIMER_UI_H_
