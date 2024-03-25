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
#include "multiValue.h"
#include "flower.h"

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
	m_Kill = 0;

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

					// ���S���Ă��玟��
					if (pObjCheck->IsDeath()) { pObjCheck = pObjectNext; continue; }

					D3DXVECTOR3 posFire = pObjCheck->GetVec3Position();	// �G�ʒu

					if (collision::Circle3D(m_pos, posFire, 25.0f, 25.0f) == true)
					{
						CParticle3D::Create(CParticle3D::TYPE_STOMP_PLANT, posFire);

						m_Kill++;
						useful::LimitMaxNum(m_Kill, 5);

						m_pScoreBG = CObjectBillboard::Create(posFire, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
						m_pScoreBG->SetScale(true);
						m_pScoreBG->SetPriority(5);

						// �����_�[�X�e�[�g�̏����擾
						CRenderState *pRenderState = m_pScoreBG->GetRenderState();

						// Z�e�X�g�̐ݒ�
						pRenderState->SetZFunc(D3DCMP_ALWAYS);

						// Z�o�b�t�@�̎g�p�󋵂̐ݒ�
						pRenderState->SetZUpdate(false);

						// ���e�X�g��L���ɂ���
						pRenderState->SetAlphaTest(true);			// ���e�X�g�̗L�� / �����̐ݒ�
						pRenderState->SetAlphaFunc(D3DCMP_GREATER);	// ���e�X�g�̐ݒ�
						pRenderState->SetAlphaNumRef(160);			// ���e�X�g�̎Q�ƒl�ݒ�

						switch (m_Kill)
						{
						case 1:
							// SE�̍Đ�
							PLAY_SOUND(CSound::LABEL_SE_COMBO00);
							m_pScoreBG->BindTexture("data\\TEXTURE\\score1.png");
							break;
						case 2:
							// SE�̍Đ�
							PLAY_SOUND(CSound::LABEL_SE_COMBO01);
							m_pScoreBG->BindTexture("data\\TEXTURE\\score2.png");
							break;
						case 3:
							// SE�̍Đ�
							PLAY_SOUND(CSound::LABEL_SE_COMBO02);
							m_pScoreBG->BindTexture("data\\TEXTURE\\score3.png");
							break;
						case 4:
							// SE�̍Đ�
							PLAY_SOUND(CSound::LABEL_SE_COMBO03);
							m_pScoreBG->BindTexture("data\\TEXTURE\\score4.png");
							break;
						default:
							// SE�̍Đ�
							PLAY_SOUND(CSound::LABEL_SE_COMBO04);
							m_pScoreBG->BindTexture("data\\TEXTURE\\score5.png");
							break;
						}
						m_pScoreBG->SetLabel(CObject::ELabel::LABEL_UI);

						//�X�R�A���Z
						CMultiValue* pScore = CSceneGame::GetScoreUI();
						pScore->AddNum(m_Kill);

						// �Ԃ͂₵
						CFlower::RandomSpawn(m_Kill);

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