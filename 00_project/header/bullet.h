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
#include "main.h"
#include "effect3D.h"

//************************************************************
//	�O���錾
//************************************************************
class CShadow;	// �e�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �ԃN���X
class CBullet : public CEffect3D
{
public:
	enum EState
	{
		NONE = 0,	// �������Ȃ�
		SPAWN,		// �X�|�[��
		MAX			// ���̗񋓂̑���
	};

	// �R���X�g���N�^
	CBullet();

	// �f�X�g���N�^
	~CBullet();

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(void) override;		// �X�V
	void Draw(CShader *pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CBullet *Create(const D3DXVECTOR3& rPos, const D3DXVECTOR3& rRot);	// ����
	//static void RandomSpawn(const int nNum);	// �����_������

private:
	// �����o�ϐ�
	CShadow *m_pShadow;	// �e�̏��
	EState m_state;		// ���
};

#endif	// _FLOWER_H_
