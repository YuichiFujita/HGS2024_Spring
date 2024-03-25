//============================================================
//
//	�Q�[���}�l�[�W���[�w�b�_�[ [gameManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "retentionManager.h"

//************************************************************
//	�N���X��`
//************************************************************
// �Q�[���}�l�[�W���[�N���X
class CGameManager
{
public:
	// ��ԗ�
	enum EState
	{
		STATE_NONE = 0,		// �������Ȃ����
		STATE_NORMAL,		// �ʏ���
		STATE_INIT_BURN,	// �S�ď��������
		STATE_BURN,			// �S�ď��
		STATE_STAGING,		// ���o���
		STATE_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CGameManager();

	// �f�X�g���N�^
	~CGameManager();

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void SetBurn(void);	// �S�ď�Ԑݒ�
	EState GetState(void) const;	// ��Ԏ擾
	void TransitionResult(void);	// ���U���g��ʑJ��

	// �ÓI�����o�֐�
	static CGameManager *Create(void);	// ����
	static void Release(CGameManager *&prGameManager);	// �j��

private:
	// �����o�֐�
	void SpownManager(void);	// �G�����̊Ǘ�
	void InitBurnManager(void);	// �S�ĉ��o�̏������Ǘ�
	void BurnManager(void);		// �S�ĉ��o�̊Ǘ�

	// �����o�ϐ�
	EState m_state;		// ���
	int Spownlevel;		// �G�����̃��x��
	int SpownCount;		// �G�����̃J�E���g
	int nFlowerCount;	// �Ԑ����J�E���g
	float m_fMoveBurn;	// ���S����̔R���L�����
};

#endif	// _GAMEMANAGER_H_
