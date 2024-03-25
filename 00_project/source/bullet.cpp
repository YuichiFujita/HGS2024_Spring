#if 0
//============================================================
//
//	�e���� [bullet.cpp]
//	Author�F���v�ԗD��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "bullet.h"
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
	const int		  PRIORITY		= 2;	// �Ԃ̗D�揇��
	const D3DXVECTOR3 SIZE_FLOWER	= D3DXVECTOR3(50.0f, 50.0f, 0.0f);	// ���a

	const float		  SHADOW_ALPHA	= 0.2f;	// �e�̃��l
	const D3DXVECTOR3 SHADOW_SIZE = D3DXVECTOR3(80.0f, 0.0f, 80.0f);	// �e�̑傫��

	const float SPAWN_ALPHA	= 0.65f;	// �Ԃ̐����������x
	const float GLOW_SPEED	= 2.0f;		// �Ԃ̐����鑬�x
}

//************************************************************
//	�q�N���X [CFlower] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CBullet::CBullet() : CEffect3D(CEffect3D::TYPE_BUBBLE, CObject::LABEL_EFFECT),
	m_pShadow	(nullptr),		// �e�̏��
	m_state		(EState::NONE)	// ���
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CBullet::~CBullet()
{

}

//============================================================
//	����������
//============================================================
HRESULT CBullet::Init(void)
{
	// �����o�ϐ���������
	m_pShadow = nullptr;		// �e�̏��
	m_state = EState::SPAWN;	// ���

	// �e�̐���
	m_pShadow = CShadow::Create(CShadow::TEXTURE_NORMAL, SHADOW_SIZE, this, SHADOW_ALPHA, SHADOW_ALPHA);
	if (m_pShadow == nullptr)
	{ // ��g�p���̏ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �I�u�W�F�N�g3D�̏�����
	if (FAILED(CObject3D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	SetPriority(2);

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

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CBullet::Uninit(void)
{
	// �e��j��
	m_pShadow->Uninit();

	// �I�u�W�F�N�g3D�̏I��
	CObject3D::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CBullet::Update(void)
{
	// �ϐ���錾
	D3DXVECTOR3 pos = GetVec3Position();	// �ʒu
	float fLand = CScene::GetStage()->GetFieldPositionHeight(pos);	// ���n�_

	switch (m_state)
	{ // ��Ԃ��Ƃ̏���
	case CBullet::NONE:

		// ������n�ʂɐݒ�
		pos.y = fLand;

		break;

	case CBullet::SPAWN:

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

	default:
		assert(false);
		break;
	}

	// �ʒu���X�V
	SetVec3Position(pos);

	// �e�̍X�V
	m_pShadow->Update();

	// �I�u�W�F�N�g3D�̍X�V
	CObject3D::Update();
}

//============================================================
//	�`�揈��
//============================================================
void CBullet::Draw(CShader *pShader)
{
	// �I�u�W�F�N�g3D�̕`��
	CObject3D::Draw(pShader);
}

//============================================================
//	��������
//============================================================
CBullet* CBullet::Create
(
	const D3DXVECTOR3& rPos,	// �ʒu
	const D3DXVECTOR3& rRot		// ����
)
{
	// �ϐ���錾
	D3DXVECTOR3 pos = rPos;	// ���W�ݒ�p

	// �Ԃ̐���
	CBullet*pBullet = new CBullet;
	if (pBullet == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �Ԃ̏�����
		if (FAILED(pBullet->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �Ԃ̔j��
			SAFE_DELETE(pBullet);
			return nullptr;
		}

		// �ʒu��ݒ�
		pos.y  = CScene::GetStage()->GetFieldPositionHeight(pos);	// ������n�ʂɐݒ�
		pos.y -= SIZE_FLOWER.y;	// �n�ʂɖ��߂�
		pBullet->SetVec3Position(pos);

		// ������ݒ�
		pBullet->SetVec3Rotation(rRot);

		// �e�̕`�����ݒ�
		pBullet->m_pShadow->SetDrawInfo();

		// �m�ۂ����A�h���X��Ԃ�
		return pBullet;
	}
}

////============================================================
////	�����_����������
////============================================================
//void CBullet::RandomSpawn(const int nNum)
//{
//	CPlayer *pPlayer = CScene::GetPlayer();					// �v���C���[���
//	CStage *pStage = CScene::GetStage();					// �X�e�[�W���
//	CStage::SStageLimit limit = pStage->GetStageLimit();	// �X�e�[�W�͈�
//	int nLimit = (int)limit.fRadius;		// �X�e�[�W���a
//	D3DXVECTOR3 posTarget = limit.center;	// ���S���W
//	D3DXVECTOR3 posSet;	// �ʒu�ݒ�p
//	D3DXVECTOR3 rotSet;	// �����ݒ�p
//
//	for (int nCntGrow = 0; nCntGrow < nNum; nCntGrow++)
//	{ // ���������J��Ԃ�
//
//		// �����ʒu��ݒ�
//		posSet.x = (float)(rand() % (nLimit * 2) - nLimit + 1);
//		posSet.y = 0.0f;
//		posSet.z = (float)(rand() % (nLimit * 2) - nLimit + 1);
//
//		// �����ʒu��␳
//		collision::CirclePillar(posSet, posTarget, SIZE_FLOWER.x, /*pPlayer->GetRadius()*/ 10.0f);	// �^�[�Q�b�g�����̐����h�~
//		CScene::GetStage()->LimitPosition(posSet, SIZE_FLOWER.x);	// �X�e�[�W�͈͊O�̐����h�~
//
//		// ����������ݒ�
//		rotSet = D3DXVECTOR3(0.0f, atan2f(posSet.x - posTarget.x, posSet.z - posTarget.z), 0.0f);
//
//		// �ԃI�u�W�F�N�g�̐���
//		CBullet::Create(posSet, rotSet);
//	}
//}
#endif