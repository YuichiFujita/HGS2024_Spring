//============================================================
//
//	数字UI処理 [valueUI.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "valueUI.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "object2D.h"
#include "multiValue.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int PRIORITY = 5;	// 数字UI表示の優先順位
}

//************************************************************
//	子クラス [CValueUI] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CValueUI::CValueUI() : CObject(CObject::LABEL_NONE, CObject::DIM_2D, PRIORITY),
	m_pTitle	(nullptr),		// タイトル情報
	m_pValue	(nullptr),		// 数字情報
	m_pos		(VEC3_ZERO),	// 位置
	m_space		(VEC3_ZERO)		// 行間
{

}

//============================================================
//	デストラクタ
//============================================================
CValueUI::~CValueUI()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CValueUI::Init(void)
{
	// メンバ変数を初期化
	m_pTitle	= nullptr;		// タイトル情報
	m_pValue	= nullptr;		// 数字情報
	m_pos		= VEC3_ZERO;	// 位置
	m_space		= VEC3_ZERO;	// 行間

	// タイトル情報の生成
	m_pTitle = CObject2D::Create(VEC3_ZERO);
	if (m_pTitle == nullptr)
	{ // 非使用中の場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pTitle->SetPriority(PRIORITY);

	// 数字情報の生成
	m_pValue = CMultiValue::Create(CValue::TEXTURE_NORMAL, 0, 1, VEC3_ZERO, VEC3_ONE, VEC3_ZERO);
	if (m_pValue == nullptr)
	{ // 非使用中の場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// 優先順位を設定
	m_pValue->SetPriority(PRIORITY);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CValueUI::Uninit(void)
{
	// タイトル情報の終了
	SAFE_UNINIT(m_pTitle);

	// 自身のオブジェクトを破棄
	Release();
}

//============================================================
//	更新処理
//============================================================
void CValueUI::Update(void)
{
	// タイトル情報の更新
	m_pTitle->Update();

	// 数字情報の更新
	m_pValue->Update();
}

//============================================================
//	描画処理
//============================================================
void CValueUI::Draw(CShader * /*pShader*/)
{

}

//============================================================
//	位置の設定処理
//============================================================
void CValueUI::SetVec3Position(const D3DXVECTOR3& rPos)
{
	// 引数の位置を設定
	m_pos = rPos;

	// 相対位置の設定
	SetPositionRelative();
}

//============================================================
//	位置取得処理
//============================================================
D3DXVECTOR3 CValueUI::GetVec3Position(void) const
{
	// 位置を返す
	return m_pos;
}

//============================================================
//	描画状況の設定処理
//============================================================
void CValueUI::SetEnableDraw(const bool bDraw)
{
	// 引数の描画状況を設定
	CObject::SetEnableDraw(bDraw);	// 自身
	m_pTitle->SetEnableDraw(bDraw);	// タイトル情報
	m_pValue->SetEnableDraw(bDraw);	// 数字情報
}

//============================================================
//	優先順位の設定処理
//============================================================
void CValueUI::SetPriority(const int nPriority)
{
	// 引数の優先順位を設定
	CObject::SetPriority(nPriority);	// 自身
	m_pTitle->SetPriority(nPriority);	// タイトル情報
	m_pValue->SetPriority(nPriority);	// 数字情報
}

//============================================================
//	生成処理
//============================================================
CValueUI *CValueUI::Create
(
	const char *pPassTex,			// タイトルテクスチャパス
	const CValue::ETexture texture,	// 数字テクスチャ
	const int nDigit,				// 桁数
	const D3DXVECTOR3& rPos,		// 位置
	const D3DXVECTOR3& rSpace,		// 行間
	const D3DXVECTOR3& rSpaceValue,	// 数字行間
	const D3DXVECTOR3& rSizeTitle,	// タイトル大きさ
	const D3DXVECTOR3& rSizeValue,	// 数字大きさ
	const D3DXVECTOR3& rRotTitle,	// タイトル向き
	const D3DXVECTOR3& rRotValue,	// 数字向き
	const D3DXCOLOR& rColTitle,		// タイトル色
	const D3DXCOLOR& rColValue		// 数字色
)
{
	// 数字UIの生成
	CValueUI *pValueUI = new CValueUI;
	if (pValueUI == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// 数字UIの初期化
		if (FAILED(pValueUI->Init()))
		{ // 初期化に失敗した場合

			// 数字UIの破棄
			SAFE_DELETE(pValueUI);
			return nullptr;
		}

		// 数字の桁数を設定
		pValueUI->GetMultiValue()->SetDigit(nDigit);

		// タイトルテクスチャを設定
		pValueUI->SetTextureTitle(pPassTex);

		// 数字テクスチャを設定
		pValueUI->GetMultiValue()->SetTexture(texture);

		// タイトル向きを設定
		pValueUI->SetRotationTitle(rRotTitle);

		// 数字向きを設定
		pValueUI->GetMultiValue()->SetVec3Rotation(rRotValue);

		// タイトル大きさを設定
		pValueUI->SetSizingTitle(rSizeTitle);

		// 数字大きさを設定
		pValueUI->GetMultiValue()->SetVec3Sizing(rSizeValue);

		// タイトル色を設定
		pValueUI->SetColorTitle(rColTitle);

		// 数字色を設定
		pValueUI->GetMultiValue()->SetColor(rColValue);

		// 数字の行間を設定
		pValueUI->GetMultiValue()->SetSpace(rSpaceValue);

		// 行間を設定
		pValueUI->SetSpace(rSpace);

		// 位置を設定
		pValueUI->SetVec3Position(rPos);

		// 確保したアドレスを返す
		return pValueUI;
	}
}

//============================================================
//	行間の設定処理
//============================================================
void CValueUI::SetSpace(const D3DXVECTOR3& rSpace)
{
	// 引数の行間を設定
	m_space = rSpace;

	// 相対位置の設定
	SetPositionRelative();
}

//============================================================
//	行間取得処理
//============================================================
D3DXVECTOR3 CValueUI::GetSpace(void) const
{
	// 行間を返す
	return m_space;
}

//============================================================
//	タイトル向きの設定処理
//============================================================
void CValueUI::SetRotationTitle(const D3DXVECTOR3& rRot)
{
	// 引数の向きを設定
	m_pTitle->SetVec3Rotation(rRot);
}

//============================================================
//	タイトル向き取得処理
//============================================================
D3DXVECTOR3 CValueUI::GetRotationTitle(void) const
{
	// タイトル向きを返す
	return m_pTitle->GetVec3Rotation();
}

//============================================================
//	タイトル大きさの設定処理
//============================================================
void CValueUI::SetSizingTitle(const D3DXVECTOR3& rSize)
{
	// 引数の大きさを設定
	m_pTitle->SetVec3Sizing(rSize);
}

//============================================================
//	タイトル大きさ取得処理
//============================================================
D3DXVECTOR3 CValueUI::GetSizingTitle(void) const
{
	// タイトル大きさを返す
	return m_pTitle->GetVec3Sizing();
}

//============================================================
//	タイトル色の設定処理
//============================================================
void CValueUI::SetColorTitle(const D3DXCOLOR& rCol)
{
	// 引数の色を設定
	m_pTitle->SetColor(rCol);
}

//============================================================
//	タイトル色取得処理
//============================================================
D3DXCOLOR CValueUI::GetColorTitle(void) const
{
	// タイトル色を返す
	return m_pTitle->GetColor();
}

//============================================================
//	タイトルテクスチャの設定処理
//============================================================
void CValueUI::SetTextureTitle(const char *pPassTex)
{
	// ポインタを宣言
	CTexture *pTexture = GET_MANAGER->GetTexture();	// テクスチャへのポインタ

	// 引数のテクスチャを割当
	m_pTitle->BindTexture(pTexture->Regist(pPassTex));
}

//============================================================
//	数字情報取得処理
//============================================================
CMultiValue *CValueUI::GetMultiValue(void) const
{
	// 数字情報を返す
	return m_pValue;
}

//============================================================
//	破棄処理
//============================================================
void CValueUI::Release(void)
{
	// オブジェクトの破棄
	CObject::Release();
}

//============================================================
//	相対位置の設定処理
//============================================================
void CValueUI::SetPositionRelative(void)
{
	// タイトルの位置を設定
	m_pTitle->SetVec3Position(m_pos);

	// 数字の位置を設定
	m_pValue->SetVec3Position(m_pTitle->GetVec3Position() + m_space);
}
