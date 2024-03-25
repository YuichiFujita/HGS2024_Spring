//============================================================
//
//	���f���������� [modelFont.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "player.h"
#include "manager.h"
#include "model.h"
#include "effect3D.h"
#include "sceneGame.h"
#include "multiValue.h"
#include "bullet.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char* MODEL_FILE[] =	// ���f���t�@�C��
	{
		"data\\MODEL\\PLAYER\\pump.x",	// �{�X�̖��O
	};
	const int PRIORITY = 3;	// ���f�������̗D�揇��

	const float ROT_MOVE = 0.03f;
	const float SHOT_POAER_PULS = 1.0f;
	const float DEF_SHOTPOWER = 10.0f;
}

//************************************************************
//	�X�^�e�B�b�N�A�T�[�g
//************************************************************
static_assert(NUM_ARRAY(MODEL_FILE) == CPlayer::TYPE_MAX, "ERROR : Type Count Mismatch");

//************************************************************
//	�q�N���X [CPlayer] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CPlayer::CPlayer() : CObjectModel(CObject::LABEL_UI, CObject::DIM_3D, PRIORITY)
{
	ShotPower = DEF_SHOTPOWER;
}

//============================================================
//	�f�X�g���N�^
//============================================================
CPlayer::~CPlayer()
{

}

//============================================================
//	����������
//============================================================
HRESULT CPlayer::Init(void)
{
	// �I�u�W�F�N�g���f���̏�����
	if (FAILED(CObjectModel::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	CObjectModel *pModel = CObjectModel::Create(GetVec3Position(), VEC3_ZERO);
	pModel->SetLabel(CObject::LABEL_PLAYER);
	pModel->SetPriority(PRIORITY);
	pModel->BindModel(GET_MANAGER->GetModel()->Regist("data\\MODEL\\PLAYER\\housu.x"));
	pModel->SetVec3Position(D3DXVECTOR3(0.0f, 150.0f, 0.0f));
	pModel->SetVec3Scaling(D3DXVECTOR3(3.0f, 3.0f, 3.0f));

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CPlayer::Uninit(void)
{
	// �I�u�W�F�N�g���f���̏I��
	CObjectModel::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CPlayer::Update(void)
{
	//�����̕ύX
	UpdateRot();

	//���˂̍X�V
	UpdateShot();

	// �I�u�W�F�N�g���f���̍X�V
	CObjectModel::Update();
}

//============================================================
//	�`�揈��
//============================================================
void CPlayer::Draw(CShader* pShader)
{
	// �I�u�W�F�N�g���f���̕`��
	CObjectModel::Draw(pShader);
}

//============================================================
//	�����ύX����
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
//	�����ύX����
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

		////�X�R�A�m�F�̃f�o�b�O
		//CMultiValue *pScore = CSceneGame::GetScoreUI();
		//pScore->AddNum(1);
	}
}

//============================================================
//	��������
//============================================================
CPlayer* CPlayer::Create
( // ����
	const EType type,			// ���
	const D3DXVECTOR3& rPos,	// �ʒu
	const D3DXVECTOR3& rRot,	// ����
	const D3DXVECTOR3& rScale	// �傫��
)
{
	// ���f�������̐���
	CPlayer* pModelFont = new CPlayer;
	if (pModelFont == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// ���f�������̏�����
		if (FAILED(pModelFont->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ���f�������̔j��
			SAFE_DELETE(pModelFont);
			return nullptr;
		}

		// ���f����o�^�E����
		pModelFont->BindModel(GET_MANAGER->GetModel()->Regist(MODEL_FILE[type]));

		// �ʒu��ݒ�
		pModelFont->SetVec3Position(rPos);

		// ������ݒ�
		pModelFont->SetVec3Rotation(rRot);

		// �g�嗦��ݒ�
		pModelFont->SetVec3Scaling(rScale);

		// �m�ۂ����A�h���X��Ԃ�
		return pModelFont;
	}
}
