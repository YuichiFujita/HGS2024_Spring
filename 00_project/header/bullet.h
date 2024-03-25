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
#include "object.h"
#include "effect3D.h"

//************************************************************
//	前方宣言
//************************************************************
class CEffect3D;

//************************************************************
//	クラス定義
//************************************************************
// 弾クラス
class CBullet : public CObject
{
public:
	// コンストラクタ
	explicit CBullet();

	// デストラクタ
	~CBullet();

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	void Uninit(void) override;		// 終了
	void Update(void) override;		// 更新
	void Draw(CShader *pShader = nullptr) override;	// 描画

	// 静的メンバ関数
	static CBullet *Create
	(
		const D3DXVECTOR3& rPos,		// 位置
		const float			fRadius,	// 半径
		const CEffect3D::EType	type,	// テクスチャ
		const int			nLife,			// 寿命
		const D3DXVECTOR3& rMove	// 移動量
	);	// 生成

private:
	// オーバーライド関数
	void Release(void) override;	// 破棄
	void CollisionFire();

	// メンバ変数
	D3DXVECTOR3	m_pos;	// 位置
	D3DXVECTOR3	m_move;	// 移動量
	D3DXVECTOR3	m_rot;	// 移動量
	float	m_Radius;	// 移動量
	CEffect3D::EType	m_type;	// テクスチャ
	int		m_nLife;			// 寿命
	int		m_Kill;			// 寿命
	CObjectBillboard* m_pScoreBG;
};

#endif	// _FLOWER_H_
