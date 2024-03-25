//============================================================
//
//	弾処理 [bullet.cpp]
//	Author：佐久間優香
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "bullet.h"
#include "manager.h"
#include "scene.h"
#include "sceneGame.h"
#include "renderer.h"
#include "sound.h"
#include "texture.h"
#include "effect3D.h"

#include "collision.h"
#include "player.h"
#include "shadow.h"
#include "field.h"
#include "stage.h"
#include "particle3D.h"
#include "multiValue.h"
#include "flower.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int	PRIORITY		= 2;	// 弾の優先順位
	const float SIZE_BULLET	= 50.0f;		// 半径
	const int	LIFE = 5;					// 寿命
	const D3DXCOLOR CLO = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//色
}

//============================================================
//	コンストラクタ
//============================================================
CBullet::CBullet() : CObject(CObject::LABEL_BULLET, CObject::DIM_3D, PRIORITY),
	m_pos(VEC3_ZERO),	// 位置
	m_move(VEC3_ZERO),	// 移動量
	m_rot(VEC3_ZERO)	// 向き
{

}

//============================================================
//	デストラクタ
//============================================================
CBullet::~CBullet()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CBullet::Init(void)
{
	m_pos = VEC3_ZERO;	// 位置
	m_move = VEC3_ZERO;	// 移動量
	m_Kill = 0;

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CBullet::Uninit(void)
{
	Release();
}

//============================================================
//	更新処理
//============================================================
void CBullet::Update(void)
{
	m_move.y -= 0.98f;

	m_pos += m_move;

	CEffect3D::Create
	(
		m_pos,
		m_Radius,
		CEffect3D::TYPE_SMOKE,
		LIFE,
		VEC3_ZERO,
		m_rot,
		D3DXCOLOR(0.0f, 0.0f, 0.2f, 1.0f),
		0.0f,
		CRenderState::BLEND_NORMAL
	);

	CEffect3D::Create
	(
		m_pos,
		m_Radius,
		m_type,
		LIFE,
		VEC3_ZERO,
		m_rot,
		CLO
	);

	CollisionFire();

	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}
	if (m_pos.y < 0)
	{
		Uninit();
		return;
	}
}

//============================================================
//	炎との当たり判定
//============================================================
void CBullet::CollisionFire(void)
{
	for (int nCntPri = 0; nCntPri < object::MAX_PRIO; nCntPri++)
	{ // 優先順位の総数分繰り返す
		// ポインタを宣言
		CObject* pObjectTop = CObject::GetTop(DIM_3D, nCntPri);	// 先頭オブジェクト
		if (pObjectTop != NULL)
		{ // 先頭が存在する場合

			// ポインタを宣言
			CObject* pObjCheck = pObjectTop;	// オブジェクト確認用

			while (pObjCheck != NULL)
			{ // オブジェクトが使用されている場合繰り返す

				// ポインタを宣言
				CObject* pObjectNext = pObjCheck->GetNext();	// 次オブジェクト

				if (pObjCheck->GetLabel() == CObject::LABEL_FIRE)
				{ // オブジェクトラベルが地盤ではない場合

					// 死亡してたら次へ
					if (pObjCheck->IsDeath()) { pObjCheck = pObjectNext; continue; }

					D3DXVECTOR3 posFire = pObjCheck->GetVec3Position();	// 敵位置

					if (collision::Circle3D(m_pos, posFire, 25.0f, 25.0f) == true)
					{
						CParticle3D::Create(CParticle3D::TYPE_STOMP_PLANT, posFire);

						m_Kill++;
						useful::LimitMaxNum(m_Kill, 5);

						m_pScoreBG = CObjectBillboard::Create(posFire, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
						m_pScoreBG->SetScale(true);
						m_pScoreBG->SetPriority(5);

						// レンダーステートの情報を取得
						CRenderState *pRenderState = m_pScoreBG->GetRenderState();

						// Zテストの設定
						pRenderState->SetZFunc(D3DCMP_ALWAYS);

						// Zバッファの使用状況の設定
						pRenderState->SetZUpdate(false);

						// αテストを有効にする
						pRenderState->SetAlphaTest(true);			// αテストの有効 / 無効の設定
						pRenderState->SetAlphaFunc(D3DCMP_GREATER);	// αテストの設定
						pRenderState->SetAlphaNumRef(160);			// αテストの参照値設定

						switch (m_Kill)
						{
						case 1:
							// SEの再生
							PLAY_SOUND(CSound::LABEL_SE_COMBO00);
							m_pScoreBG->BindTexture("data\\TEXTURE\\score1.png");
							break;
						case 2:
							// SEの再生
							PLAY_SOUND(CSound::LABEL_SE_COMBO01);
							m_pScoreBG->BindTexture("data\\TEXTURE\\score2.png");
							break;
						case 3:
							// SEの再生
							PLAY_SOUND(CSound::LABEL_SE_COMBO02);
							m_pScoreBG->BindTexture("data\\TEXTURE\\score3.png");
							break;
						case 4:
							// SEの再生
							PLAY_SOUND(CSound::LABEL_SE_COMBO03);
							m_pScoreBG->BindTexture("data\\TEXTURE\\score4.png");
							break;
						default:
							// SEの再生
							PLAY_SOUND(CSound::LABEL_SE_COMBO04);
							m_pScoreBG->BindTexture("data\\TEXTURE\\score5.png");
							break;
						}
						m_pScoreBG->SetLabel(CObject::ELabel::LABEL_UI);

						//スコア加算
						CMultiValue* pScore = CSceneGame::GetScoreUI();
						pScore->AddNum(m_Kill);

						// 花はやし
						CFlower::RandomSpawn(m_Kill);

						pObjCheck->Uninit();
					}
				}

				// 次のオブジェクトへのポインタを代入
				pObjCheck = pObjectNext;
			}
		}
	}
}

//============================================================
//	描画処理
//============================================================
void CBullet::Draw(CShader */*pShader*/)
{
	
}

//============================================================
//	生成処理
//============================================================
CBullet* CBullet::Create
(
	const D3DXVECTOR3& rPos,		// 位置
	const float			fRadius,	// 半径
	const CEffect3D::EType	type,	// テクスチャ
	const int			nLife,			// 寿命
	const D3DXVECTOR3& rMove	// 移動量
)	// 生成
{
	// ポインタを宣言
	CBullet* pBullet = new CBullet;	// 弾情報

	if (pBullet == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// 炎の初期化
		if (FAILED(pBullet->Init()))
		{ // 初期化に失敗した場合

			// 炎の破棄
			SAFE_DELETE(pBullet);
			return nullptr;
		}

		//// 位置を設定
		//pBullet->SetVec3Position(rPos);

		//pBullet->SetVec3Rotation(VEC3_ZERO);

		pBullet->m_pos = rPos;
		pBullet->m_Radius = fRadius;
		pBullet->m_type = type;
		pBullet->m_nLife = nLife;
		pBullet->m_move = rMove;

		// 確保したアドレスを返す
		return pBullet;
	}
}

//============================================================
//	破棄処理
//============================================================
void CBullet::Release(void)
{
	// オブジェクトの破棄
	CObject::Release();
}