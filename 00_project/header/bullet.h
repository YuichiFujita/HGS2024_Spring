//============================================================
//
//	�e�w�b�_�[ [bullet.h]
//	Author�F���v�ԗD��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _BULLET_H_
#define _BULLET_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "effect3D.h"

//************************************************************
//	�O���錾
//************************************************************
class CEffect3D;

//************************************************************
//	�N���X��`
//************************************************************
// �e�N���X
class CBullet : public CObject
{
public:
	// �R���X�g���N�^
	explicit CBullet();

	// �f�X�g���N�^
	~CBullet();

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(void) override;		// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CBullet *Create
	(
		const D3DXVECTOR3& rPos,		// �ʒu
		const float			fRadius,	// ���a
		const CEffect3D::EType	type,	// �e�N�X�`��
		const int			nLife,			// ����
		const D3DXVECTOR3& rMove	// �ړ���
	);	// ����

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override;	// �j��
	void CollisionFire();

	// �����o�ϐ�
	D3DXVECTOR3	m_pos;	// �ʒu
	D3DXVECTOR3	m_move;	// �ړ���
	D3DXVECTOR3	m_rot;	// �ړ���
	float	m_Radius;	// �ړ���
	CEffect3D::EType	m_type;	// �e�N�X�`��
	int		m_nLife;			// ����
	int		m_Kill;			// ����
	CObjectBillboard* m_pScoreBG;
};

#endif	// _FLOWER_H_
