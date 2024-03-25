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

//************************************************************
//	�O���錾
//************************************************************

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
	static CBullet *Create(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rRot);	// ����

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override;	// �j��

	// �����o�ϐ�
	D3DXVECTOR3	m_pos;	// �ʒu
	D3DXVECTOR3	m_move;	// �ړ���
	D3DXVECTOR3	m_rot;	// �ړ���
};

#endif	// _FLOWER_H_
