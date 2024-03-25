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
	const int	LIFE = 10;					// ����
	const D3DXCOLOR CLO = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F
	
}

//============================================================
//	�R���X�g���N�^
//============================================================
CBullet::CBullet() : CObject(CObject::LABEL_EFFECT, CObject::DIM_3D, PRIORITY),
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
	CEffect3D::Create(m_pos,
		SIZE_BULLET,
		CEffect3D::TYPE_BUBBLE,
		LIFE, m_move,
		m_rot,
		CLO,
		0.0f,
		CRenderState::BLEND_ADD);
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
	const D3DXVECTOR3& rPos,	// �ʒu
	const D3DXVECTOR3& rRot		// ����
)
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

		// �ʒu��ݒ�
		pBullet->SetVec3Position(rPos);

		pBullet->SetVec3Rotation(rRot);

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