//============================================================
//
//	モデル文字処理 [modelFont.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "player.h"
#include "manager.h"
#include "model.h"
#include "effect3D.h"
#include "sceneGame.h"
#include "multiValue.h"
#include "bullet.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char* MODEL_FILE[] =	// モデルファイル
	{
		"data\\MODEL\\PLAYER\\pump.x",	// ボスの名前
	};
	const int PRIORITY = 3;	// モデル文字の優先順位

	const float ROT_MOVE = 0.03f;
	const float SHOT_POAER_PULS = 1.0f;
	const float DEF_SHOTPOWER = 10.0f;
}

//************************************************************
//	スタティックアサート
//************************************************************
static_assert(NUM_ARRAY(MODEL_FILE) == CPlayer::TYPE_MAX, "ERROR : Type Count Mismatch");

//************************************************************
//	子クラス [CPlayer] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CPlayer::CPlayer() : CObjectModel(CObject::LABEL_UI, CObject::DIM_3D, PRIORITY)
{
	ShotPower = DEF_SHOTPOWER;
}

//============================================================
//	デストラクタ
//============================================================
CPlayer::~CPlayer()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CPlayer::Init(void)
{
	// オブジェクトモデルの初期化
	if (FAILED(CObjectModel::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	CObjectModel *pModel = CObjectModel::Create(GetVec3Position(), VEC3_ZERO);
	pModel->SetLabel(CObject::LABEL_PLAYER);
	pModel->SetPriority(PRIORITY);
	pModel->BindModel(GET_MANAGER->GetModel()->Regist("data\\MODEL\\PLAYER\\housu.x"));
	pModel->SetVec3Position(D3DXVECTOR3(0.0f, 150.0f, 0.0f));
	pModel->SetVec3Scaling(D3DXVECTOR3(3.0f, 3.0f, 3.0f));

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CPlayer::Uninit(void)
{
	// オブジェクトモデルの終了
	CObjectModel::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CPlayer::Update(void)
{
	//向きの変更
	UpdateRot();

	//発射の更新
	UpdateShot();

	// オブジェクトモデルの更新
	CObjectModel::Update();
}

//============================================================
//	描画処理
//============================================================
void CPlayer::Draw(CShader* pShader)
{
	// オブジェクトモデルの描画
	CObjectModel::Draw(pShader);
}

//============================================================
//	向き変更処理
//============================================================
void CPlayer::UpdateRot()
{
	D3DXVECTOR3 Rot = GetVec3Rotation();

	if (GET_INPUTKEY->IsPress(DIK_A) == true || GET_INPUTKEY->IsPress(DIK_LEFT) == true)
	{
		Rot.z += ROT_MOVE;

		if (Rot.z > D3DX_PI * 0.5f)
		{
			Rot.z = D3DX_PI * 0.5f;
		}
	}
	if (GET_INPUTKEY->IsPress(DIK_D) == true || GET_INPUTKEY->IsPress(DIK_RIGHT) == true)
	{
		Rot.z -= ROT_MOVE;

		if (Rot.z < -D3DX_PI * 0.5f)
		{
			Rot.z = -D3DX_PI * 0.5f;
		}
	}

	SetVec3Rotation(Rot);
}

//============================================================
//	向き変更処理
//============================================================
void CPlayer::UpdateShot()
{
	D3DXVECTOR3 Pos = GetVec3Position();
	D3DXVECTOR3 Rot = GetVec3Rotation();

	if (GET_INPUTKEY->IsPress(DIK_SPACE) == true)
	{
		ShotPower += SHOT_POAER_PULS;

		if (ShotPower > 50.0f)
		{
			ShotPower = 50.0f;
		}

		for (int nCntEffect = 0; nCntEffect < 10; nCntEffect++)
		{
			Pos.x += (sinf(-Rot.z) * (ShotPower * 0.1f) * nCntEffect);
			Pos.y += (cosf(Rot.z) * (ShotPower * 0.1f) * nCntEffect);

			CEffect3D::Create(D3DXVECTOR3((sinf(-Rot.z) * 80.0f) + Pos.x, (cosf(Rot.z) * 80.0f) + Pos.y,Pos.z), 10.0f, CEffect3D::EType::TYPE_NORMAL, 2);
		}
	}

	if (GET_INPUTKEY->IsRelease(DIK_SPACE) == true)
	{
		CBullet::Create
		(
			D3DXVECTOR3((sinf(-Rot.z) * 80.0f) + Pos.x, (cosf(Rot.z) * 80.0f) + Pos.y, Pos.z), 
			50.0f,
			CEffect3D::EType::TYPE_BUBBLE,
			60,
			D3DXVECTOR3(sinf(-Rot.z) * ShotPower, cosf(Rot.z) * ShotPower, 0.0f));

		ShotPower = DEF_SHOTPOWER;

		////スコア確認のデバッグ
		//CMultiValue *pScore = CSceneGame::GetScoreUI();
		//pScore->AddNum(1);
	}
}

//============================================================
//	生成処理
//============================================================
CPlayer* CPlayer::Create
( // 引数
	const EType type,			// 種類
	const D3DXVECTOR3& rPos,	// 位置
	const D3DXVECTOR3& rRot,	// 向き
	const D3DXVECTOR3& rScale	// 大きさ
)
{
	// モデル文字の生成
	CPlayer* pModelFont = new CPlayer;
	if (pModelFont == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// モデル文字の初期化
		if (FAILED(pModelFont->Init()))
		{ // 初期化に失敗した場合

			// モデル文字の破棄
			SAFE_DELETE(pModelFont);
			return nullptr;
		}

		// モデルを登録・割当
		pModelFont->BindModel(GET_MANAGER->GetModel()->Regist(MODEL_FILE[type]));

		// 位置を設定
		pModelFont->SetVec3Position(rPos);

		// 向きを設定
		pModelFont->SetVec3Rotation(rRot);

		// 拡大率を設定
		pModelFont->SetVec3Scaling(rScale);

		// 確保したアドレスを返す
		return pModelFont;
	}
}
