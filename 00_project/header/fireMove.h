//============================================================
//
//	�����ړ����w�b�_�[ [fireMove.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FIRE_MOVE_H_
#define _FIRE_MOVE_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "fire.h"

//************************************************************
//	�N���X��`
//************************************************************
// �����ړ����N���X
class CFireMove : public CFire
{
public:
	// �R���X�g���N�^
	explicit CFireMove(const EType type);

	// �f�X�g���N�^
	virtual ~CFireMove();

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��

	void SetMovePosition(const D3DXVECTOR3& rMove) override { m_moveDef = rMove; }	// �ʒu�ړ��ʐݒ�

protected:
	// �I�[�o�[���C�h�֐�
	void UpdateMove(void) override;	// �����̍X�V

private:
	// �����o�ϐ�
	D3DXVECTOR3	m_moveDef;	// ���̈ړ���
};

#endif	// _FIRE_MOVE_H_
