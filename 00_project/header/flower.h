//============================================================
//
//	花ヘッダー [flower.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _FLOWER_H_
#define _FLOWER_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "main.h"
#include "object3D.h"

//************************************************************
//	前方宣言
//************************************************************
class CShadow;	// 影クラス

//************************************************************
//	クラス定義
//************************************************************
// 花クラス
class CFlower : public CObject3D
{
public:
	enum EState
	{
		NONE = 0,	// 何もしない
		SPAWN,		// スポーン
		BURN,		// 燃え燃え
		FADE,		// フェードアウト
		MAX			// この列挙の総数
	};

	// コンストラクタ
	CFlower();

	// デストラクタ
	~CFlower();

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(void) override;		// 更新
	void Draw(CShader *pShader = nullptr) override;	// 描画
	int GetState(void) const override;				// 状態取得
	float GetRadius(void) const override;			// 半径取得

	// 静的メンバ関数
	static CFlower *Create(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rRot);	// 生成
	static CListManager<CFlower> *GetList(void);	// リスト取得
	static void RandomSpawn(const int nNum);		// ランダム生成

	// メンバ関数
	void Burn(void) { m_state = EState::BURN; }	// 燃えさせる

private:
	// 静的メンバ変数
	static CListManager<CFlower> *m_pList;	// オブジェクトリスト

	// メンバ変数
	CListManager<CFlower>::AIterator m_iterator;	// イテレーター
	CShadow *m_pShadow;	// 影の情報
	EState m_state;		// 状態
};

#endif	// _FLOWER_H_
