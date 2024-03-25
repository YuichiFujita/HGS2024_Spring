//============================================================
//
//	�ԏ��� [flower.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "flower.h"
#include "manager.h"
#include "scene.h"
#include "sceneGame.h"
#include "renderer.h"
#include "sound.h"
#include "texture.h"

#include "collision.h"
#include "player.h"
#include "shadow.h"
#include "field.h"
#include "stage.h"
#include "particle3D.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char *TEXTURE_FILE = "data\\TEXTURE\\flower000.png";	// �ԃe�N�X�`���t�@�C��

	const int		  PRIORITY		= 2;	// �Ԃ̗D�揇��
	const D3DXVECTOR3 SIZE_FLOWER	= D3DXVECTOR3(50.0f, 50.0f, 0.0f);	// ���a

	const float		  SHADOW_ALPHA	= 0.2f;	// �e�̃��l
	const D3DXVECTOR3 SHADOW_SIZE = D3DXVECTOR3(80.0f, 0.0f, 80.0f);	// �e�̑傫��

	const float SPAWN_ALPHA	= 0.65f;	// �Ԃ̐����������x
	const float GLOW_SPEED	= 2.0f;		// �Ԃ̐����鑬�x
}
//************************************************************
//	�萔�錾
//************************************************************
CListManager<CFlower> *CFlower::m_pList = nullptr;	// �I�u�W�F�N�g���X�g

//************************************************************
//	�q�N���X [CFlower] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CFlower::CFlower() : CObject3D(CObject::LABEL_FLOWER, CObject::DIM_3D, PRIORITY),
	m_state		(EState::NONE)	// ���
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CFlower::~CFlower()
{

}

//============================================================
//	����������
//============================================================
HRESULT CFlower::Init(void)
{
	// �����o�ϐ���������
	m_state = EState::SPAWN;	// ���

	// �I�u�W�F�N�g3D�̏�����
	if (FAILED(CObject3D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �e�N�X�`��������
	BindTexture(TEXTURE_FILE);

	// ���_��ݒ�
	SetOrigin(ORIGIN_DOWN);

	// �傫����ݒ�
	SetVec3Sizing(SIZE_FLOWER);

	// �����x��ݒ�
	D3DXCOLOR col = GetColor();
	SetColor(D3DXCOLOR(col.r, col.g, col.b, SPAWN_ALPHA));

	// �����_�[�X�e�[�g�̏����擾
	CRenderState *pRenderState = GetRenderState();

	// ���e�X�g��L���ɂ���
	pRenderState->SetAlphaTest(true);			// ���e�X�g�̗L�� / �����̐ݒ�
	pRenderState->SetAlphaFunc(D3DCMP_GREATER);	// ���e�X�g�̐ݒ�
	pRenderState->SetAlphaNumRef(160);			// ���e�X�g�̎Q�ƒl�ݒ�

	// �J�����O��ݒ�
	pRenderState->SetCulling(D3DCULL_NONE);

	// ���C�e�B���O��ݒ�
	pRenderState->SetLighting(false);

	// Z�e�X�g��ݒ�
	pRenderState->SetZFunc(D3DCMP_LESSEQUAL);

	// Z�o�b�t�@�̎g�p�󋵂�ݒ�
	pRenderState->SetZUpdate(true);

	if (m_pList == nullptr)
	{ // ���X�g�}�l�[�W���[�����݂��Ȃ��ꍇ

		// ���X�g�}�l�[�W���[�̐���
		m_pList = CListManager<CFlower>::Create();
		if (m_pList == nullptr)
		{ // �����Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}
	}

	// ���X�g�Ɏ��g�̃I�u�W�F�N�g��ǉ��E�C�e���[�^�[���擾
	m_iterator = m_pList->AddList(this);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CFlower::Uninit(void)
{
	// ���X�g���玩�g�̃I�u�W�F�N�g���폜
	m_pList->DeleteList(m_iterator);

	if (m_pList->GetNumAll() == 0)
	{ // �I�u�W�F�N�g������Ȃ��ꍇ

		// ���X�g�}�l�[�W���[�̔j��
		m_pList->Release(m_pList);
	}

	// �I�u�W�F�N�g3D�̏I��
	CObject3D::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CFlower::Update(void)
{
	// �ϐ���錾
	D3DXVECTOR3 pos = GetVec3Position();	// �ʒu
	float fLand = CScene::GetStage()->GetFieldPositionHeight(pos);	// ���n�_

	switch (m_state)
	{ // ��Ԃ��Ƃ̏���
	case CFlower::NONE:
	{
		// ������n�ʂɐݒ�
		pos.y = fLand;

		break;
	}
	case CFlower::SPAWN:
	{
		// �n�ʂ���͂₷
		pos.y += GLOW_SPEED;
		if (pos.y >= fLand)
		{ // �ʒu�����n�_�𒴂����ꍇ

			// �ʒu�␳
			pos.y = fLand;

			// �����x��ݒ�
			D3DXCOLOR col = GetColor();
			SetColor(D3DXCOLOR(col.r, col.g, col.b, 1.0f));

			// �������Ȃ���Ԃɂ���
			m_state = EState::NONE;
		}

		break;
	}
	case CFlower::BURN:
	{
		// �F��ݒ�
		D3DXCOLOR col = GetColor();
		col -= D3DXCOLOR(0.05f, 0.05f, 0.05f, 0.0f);
		SetColor(col);

		if (col.r <= 0.2f)
		{ // �F�����̏ꍇ

			SetColor(D3DXCOLOR(0.2f, 0.2f, 0.2f, GetColor().a));

			// �t�F�[�h�A�E�g��Ԃɂ���
			m_state = EState::FADE;
		}

		break;
	}
	case CFlower::FADE:
	{
		// �n�ʂ���͂₷
		pos.y -= 1.0f;

		// �F��ݒ�
		D3DXCOLOR col = GetColor();
		col.a -= 0.05f;
		SetColor(col);

		if (col.a <= 0.0f)
		{ // �����x�������肫�����ꍇ

			// ���g���I��
			Uninit();
			return;
		}

		break;
	}
	default:
		assert(false);
		break;
	}

	// �ʒu���X�V
	SetVec3Position(pos);

	// �I�u�W�F�N�g3D�̍X�V
	CObject3D::Update();
}

//============================================================
//	�`�揈��
//============================================================
void CFlower::Draw(CShader *pShader)
{
	// �I�u�W�F�N�g3D�̕`��
	CObject3D::Draw(pShader);
}

//============================================================
//	��Ԏ擾����
//============================================================
int CFlower::GetState(void) const
{
	return (int)m_state;
}

//============================================================
//	���a�擾����
//============================================================
float CFlower::GetRadius(void) const
{
	return SIZE_FLOWER.x;
}

//============================================================
//	��������
//============================================================
CFlower *CFlower::Create
(
	const D3DXVECTOR3& rPos,	// �ʒu
	const D3DXVECTOR3& rRot		// ����
)
{
	// �ϐ���錾
	D3DXVECTOR3 pos = rPos;	// ���W�ݒ�p

	// �Ԃ̐���
	CFlower *pFlower = new CFlower;
	if (pFlower == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �Ԃ̏�����
		if (FAILED(pFlower->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �Ԃ̔j��
			SAFE_DELETE(pFlower);
			return nullptr;
		}

		// �ʒu��ݒ�
		pos.y  = CScene::GetStage()->GetFieldPositionHeight(pos);	// ������n�ʂɐݒ�
		pos.y -= SIZE_FLOWER.y;	// �n�ʂɖ��߂�
		pFlower->SetVec3Position(pos);

		// ������ݒ�
		pFlower->SetVec3Rotation(rRot);

		// �m�ۂ����A�h���X��Ԃ�
		return pFlower;
	}
}

//============================================================
//	���X�g�擾����
//============================================================
CListManager<CFlower> *CFlower::GetList(void)
{
	// �I�u�W�F�N�g���X�g��Ԃ�
	return m_pList;
}

//============================================================
//	�����_����������
//============================================================
void CFlower::RandomSpawn(const int nNum)
{
	CStage *pStage = CScene::GetStage();					// �X�e�[�W���
	CStage::SStageLimit limit = pStage->GetStageLimit();	// �X�e�[�W�͈�
	int nLimit = (int)limit.fRadius;		// �X�e�[�W���a
	D3DXVECTOR3 posTarget = limit.center;	// ���S���W
	D3DXVECTOR3 posSet;	// �ʒu�ݒ�p
	D3DXVECTOR3 rotSet;	// �����ݒ�p

	for (int nCntGrow = 0; nCntGrow < nNum; nCntGrow++)
	{ // ���������J��Ԃ�

		// �����ʒu��ݒ�
		posSet.x = (float)(rand() % (nLimit * 2) - nLimit + 1);
		posSet.y = 0.0f;
		posSet.z = (float)(rand() % (nLimit * 2) - nLimit + 1);

		// �����ʒu��␳
		collision::CirclePillar(posSet, posTarget, SIZE_FLOWER.x, 10.0f);	// �^�[�Q�b�g�����̐����h�~
		CScene::GetStage()->LimitPosition(posSet, SIZE_FLOWER.x);	// �X�e�[�W�͈͊O�̐����h�~

		// ����������ݒ�
		rotSet = D3DXVECTOR3(0.0f, atan2f(posSet.x - posTarget.x, posSet.z - posTarget.z), 0.0f);

		// �ԃI�u�W�F�N�g�̐���
		CFlower::Create(posSet, rotSet);
	}
}
