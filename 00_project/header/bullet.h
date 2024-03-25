//============================================================
//
//	弾ヘッダー [bullet.h]
//	Author：佐久間優香
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _BULLET_H_
#define _BULLET_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "main.h"
#include "effect3D.h"

//************************************************************
//	前方宣言
//************************************************************
class CShadow;	// 影クラス

//************************************************************
//	クラス定義
//************************************************************
// 花クラス
class CBullet : public CEffect3D
{
public:
	enum EState
	{
		NONE = 0,	// 何もしない
		SPAWN,		// スポーン
		MAX			// この列挙の総数
	};

	// コンストラクタ
	CBullet();

	// デストラクタ
	~CBullet();

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(void) override;		// 更新
	void Draw(CShader *pShader = nullptr) override;	// 描画

	// 静的メンバ関数
	static CBullet *Create(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rRot);	// 生成
	//static void RandomSpawn(const int nNum);	// ランダム生成

private:
	// メンバ変数
	CShadow *m_pShadow;	// 影の情報
	EState m_state;		// 状態
};

#endif	// _FLOWER_H_
