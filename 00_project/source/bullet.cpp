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
#include "effect3D.h"

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
	const int	PRIORITY		= 2;	// �e�̗D�揇��
	const float SIZE_BULLET	= 50.0f;		// ���a
	const int	LIFE = 5;					// ����
	const D3DXCOLOR CLO = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F
}

//============================================================
//	�R���X�g���N�^
//============================================================
CBullet::CBullet() : CObject(CObject::LABEL_BULLET, CObject::DIM_3D, PRIORITY),
	m_pos(VEC3_ZERO),	// �ʒu
	m_move(VEC3_ZERO),	// �ړ���
	m_rot(VEC3_ZERO)	// ����
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
	m_pos = VEC3_ZERO;	// �ʒu
	m_move = VEC3_ZERO;	// �ړ���

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CBullet::Uninit(void)
{
	Release();
}

//============================================================
//	�X�V����
//============================================================
void CBullet::Update(void)
{
	m_move.y -= 0.98f;

	m_pos += m_move;

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
}

//============================================================
//	���Ƃ̓����蔻��
//============================================================
void CBullet::CollisionFire(void)
{
	for (int nCntPri = 0; nCntPri < object::MAX_PRIO; nCntPri++)
	{ // �D�揇�ʂ̑������J��Ԃ�
		// �|�C���^��錾
		CObject* pObjectTop = CObject::GetTop(DIM_3D, nCntPri);	// �擪�I�u�W�F�N�g
		if (pObjectTop != NULL)
		{ // �擪�����݂���ꍇ

			// �|�C���^��錾
			CObject* pObjCheck = pObjectTop;	// �I�u�W�F�N�g�m�F�p

			while (pObjCheck != NULL)
			{ // �I�u�W�F�N�g���g�p����Ă���ꍇ�J��Ԃ�

				// �|�C���^��錾
				CObject* pObjectNext = pObjCheck->GetNext();	// ���I�u�W�F�N�g

				if (pObjCheck->GetLabel() == CObject::LABEL_FIRE)
				{ // �I�u�W�F�N�g���x�����n�Ղł͂Ȃ��ꍇ

					D3DXVECTOR3 posFire = pObjCheck->GetVec3Position();	// �G�ʒu

					if (collision::Circle3D(m_pos, posFire, 25.0f, 25.0f) == true)
					{
						pObjCheck->Uninit();
					}
				}

				// ���̃I�u�W�F�N�g�ւ̃|�C���^����
				pObjCheck = pObjectNext;
			}
		}
	}
}

//============================================================
//	�`�揈��
//============================================================
void CBullet::Draw(CShader */*pShader*/)
{
	
}

//============================================================
//	��������
//============================================================
CBullet* CBullet::Create
(
	const D3DXVECTOR3& rPos,		// �ʒu
	const float			fRadius,	// ���a
	const CEffect3D::EType	type,	// �e�N�X�`��
	const int			nLife,			// ����
	const D3DXVECTOR3& rMove	// �ړ���
)	// ����
{
	// �|�C���^��錾
	CBullet* pBullet = new CBullet;	// �e���

	if (pBullet == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// ���̏�����
		if (FAILED(pBullet->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ���̔j��
			SAFE_DELETE(pBullet);
			return nullptr;
		}

		//// �ʒu��ݒ�
		//pBullet->SetVec3Position(rPos);

		//pBullet->SetVec3Rotation(VEC3_ZERO);

		pBullet->m_pos = rPos;
		pBullet->m_Radius = fRadius;
		pBullet->m_type = type;
		pBullet->m_nLife = nLife;
		pBullet->m_move = rMove;

		// �m�ۂ����A�h���X��Ԃ�
		return pBullet;
	}
}

//============================================================
//	�j������
//============================================================
void CBullet::Release(void)
{
	// �I�u�W�F�N�g�̔j��
	CObject::Release();
}