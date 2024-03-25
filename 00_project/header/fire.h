//============================================================
//
//	炎ヘッダー [fire.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _FIRE_H_
#define _FIRE_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "object.h"

//************************************************************
//	クラス定義
//************************************************************
// 炎クラス
class CFire : public CObject
{
public:
	// 種類列挙
	enum EType
	{
		TYPE_NORMAL = 0,	// 真っ直ぐ
		TYPE_MAX			// この列挙型の総数
	};

	// コンストラクタ
	explicit CFire(const EType type);

	// デストラクタ
	virtual ~CFire();

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(void) override;		// 更新
	void Draw(CShader *pShader = nullptr) override;			// 描画
	void SetVec3Position(const D3DXVECTOR3& rPos) override;	// 位置設定
	D3DXVECTOR3 GetVec3Position(void) const override;		// 位置取得
	int GetType(void) const override;						// 種類取得
	float GetRadius(void) const override;					// 半径取得

	// 静的メンバ関数
	static CFire *Create	// 生成
	( // 引数
		const EType type,		// 種類
		const float fGravity,	// 重力
		const D3DXVECTOR3& rPos	// 位置
	);

	// メンバ関数
	void SetMovePosition(const D3DXVECTOR3& rMove);	// 位置移動量設定
	D3DXVECTOR3 GetMovePosition(void) const;		// 位置移動量取得

protected:
	// 純粋仮想関数
	virtual void UpdateMove(void) = 0;	// 挙動の更新

	// メンバ関数
	void UpdatePosition(D3DXVECTOR3 *pPos);	// 位置の更新

private:
	// オーバーライド関数
	void Release(void) override;	// 破棄

	// メンバ関数
	void UpdateGravity(void);	// 重力の更新
	bool UpdateDelete(void);	// 削除の更新

	// メンバ変数
	D3DXVECTOR3	m_pos;	// 位置
	D3DXVECTOR3	m_move;	// 移動量
	float m_fGravity;	// 重力
	const EType m_type;	// 種類定数
};

#endif	// _FIRE_H_
