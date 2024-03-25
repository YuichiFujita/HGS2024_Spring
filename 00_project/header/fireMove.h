//============================================================
//
//	等速移動炎ヘッダー [fireMove.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _FIRE_MOVE_H_
#define _FIRE_MOVE_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object.h"
#include "fire.h"

//************************************************************
//	クラス定義
//************************************************************
// 等速移動炎クラス
class CFireMove : public CFire
{
public:
	// コンストラクタ
	explicit CFireMove(const EType type);

	// デストラクタ
	virtual ~CFireMove();

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了

	void SetMovePosition(const D3DXVECTOR3& rMove) override { m_moveDef = rMove; }	// 位置移動量設定

protected:
	// オーバーライド関数
	void UpdateMove(void) override;	// 挙動の更新

private:
	// メンバ変数
	D3DXVECTOR3	m_moveDef;	// 元の移動量
};

#endif	// _FIRE_MOVE_H_
