//============================================================
//
//	チュートリアルマネージャーヘッダー [tutorialManager.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _TUTORIAL_MANAGER_H_
#define _TUTORIAL_MANAGER_H_

//************************************************************
//	前方宣言
//************************************************************
class CObject2D;	// オブジェクト2Dクラス

//************************************************************
//	クラス定義
//************************************************************
// チュートリアルマネージャークラス
class CTutorialManager
{
public:
	// テクスチャ列挙
	enum ETexture
	{
		TEXTURE_CONTROL = 0,	// 操作方法テクスチャ
		TEXTURE_END,			// 終了方法テクスチャ
		TEXTURE_MAX				// この列挙型の総数
	};

	// コンストラクタ
	CTutorialManager();

	// デストラクタ
	~CTutorialManager();

	// メンバ関数
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新

	// 静的メンバ関数
	static CTutorialManager *Create(void);	// 生成
	static void Release(CTutorialManager *&prTutorialManager);	// 破棄

private:
	// メンバ変数
	CObject2D *m_pExplain;	// 説明表示の情報
	CObject2D *m_pControl;	// 操作説明の情報
};

#endif	// _TUTORIAL_MANAGER_H_
