//============================================================
//
//	�^�C�}�[UI�w�b�_�[ [timerUI.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _SCORE_UI_H_
#define _SCORE_UI_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "multiValue.h"

//************************************************************
//	�O���錾
//************************************************************
class CObject2D;	// �I�u�W�F�N�g2D�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �^�C�}�[UI�N���X
class CScoreUI : public CMultiValue
{
public:
	// �e�N�X�`����
	enum ETexture
	{
		TEXTURE_BG = 0,	// �w�i�e�N�X�`��
		TEXTURE_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CScoreUI();

	// �f�X�g���N�^
	~CScoreUI() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(void) override;		// �X�V
	void SetEnableUpdate(const bool bUpdate) override;	// �X�V�󋵐ݒ�
	void SetEnableDraw(const bool bDraw) override;		// �`��󋵐ݒ�

	// �ÓI�����o�֐�
	static CScoreUI *Create	// ����
	( // ����
		const int nNum,					// ����
		const int nDigit,				// ����
		const D3DXVECTOR3& rPos,		// �ʒu
		const D3DXVECTOR3& rSize,		// �傫��
		const D3DXVECTOR3& rSpace,		// �s��
		const D3DXVECTOR3& rRot,	// ����
		const D3DXCOLOR& rCol		// �F
	);
	static void Release(CScoreUI *&prTimerUI);	// �j��

	// �����o�֐�
	void SetOffset(const D3DXVECTOR3& rOffset);	// �I�t�Z�b�g�ݒ�
	void SetSizingBG(const D3DXVECTOR3& rSize);	// �w�i�傫���ݒ�

private:
	// �����o�֐�

	// �����o�ϐ�
	CObject2D *m_pBG;		// �w�i�̏��
	D3DXVECTOR3 m_offsetBG;	// �w�i�̃I�t�Z�b�g
};

#endif	// _TIMER_UI_H_
