//============================================================
//
//	�ԃw�b�_�[ [flower.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FLOWER_H_
#define _FLOWER_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "object3D.h"

//************************************************************
//	�O���錾
//************************************************************
class CShadow;	// �e�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �ԃN���X
class CFlower : public CObject3D
{
public:
	enum EState
	{
		NONE = 0,	// �������Ȃ�
		SPAWN,		// �X�|�[��
		MAX			// ���̗񋓂̑���
	};

	// �R���X�g���N�^
	CFlower();

	// �f�X�g���N�^
	~CFlower();

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(void) override;		// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CFlower *Create(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rRot);	// ����
	static void RandomSpawn(const int nNum);	// �����_������
	static int GetNumAll(void);	// �����擾

private:
	// �ÓI�����o�ϐ�
	static int m_nNumAll;	// �Ԃ̑���

	// �����o�ϐ�
	CShadow *m_pShadow;	// �e�̏��
	EState m_state;		// ���
};

#endif	// _FLOWER_H_
