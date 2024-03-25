//============================================================
//
//	ふわふわ炎ヘッダー [fireFluffy.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _FIRE_FLUFFY_H_
#define _FIRE_FLUFFY_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object.h"
#include "fire.h"

//************************************************************
//	クラス定義
//************************************************************
// 真っ直ぐ炎クラス
class CFireFluffy : public CFire
{
public:
	// コンストラクタ
	explicit CFireFluffy(const EType type);

	// デストラクタ
	virtual ~CFireFluffy();

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了

protected:
	// オーバーライド関数
	void UpdateMove(void) override;	// 挙動の更新

private:

	//メンバ変数
	D3DXVECTOR3 m_move;
	int m_nMoveCountMax;
	int m_nMoveCount;
};

#endif	// _FIRE_NORMAL_H_
