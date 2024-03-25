//============================================================
//
//	�`���[�g���A���}�l�[�W���[���� [tutorialManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "tutorialManager.h"
#include "manager.h"
#include "sound.h"
#include "camera.h"
#include "texture.h"
#include "object2D.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char *TEXTURE_FILE[] =	// �e�N�X�`���t�@�C��
	{
		"data\\TEXTURE\\tutorial.png",	// ��������e�N�X�`��
		"data\\TEXTURE\\tutorial001.png",	// �I�������e�N�X�`��
	};

	const int PRIORITY = 5;	// �`���[�g���A���̗D�揇��

	namespace lesson
	{
		const D3DXVECTOR3 POS	= SCREEN_CENT;	// ���b�X���\���̈ʒu
		const D3DXVECTOR3 SIZE	= SCREEN_SIZE;	// ���b�X���\���̈ʒu
	}

	namespace control
	{
		const D3DXVECTOR3 POS	= D3DXVECTOR3(1140.0f, 85.0f, 0.0f);	// ������@�̈ʒu
		const D3DXVECTOR3 SIZE	= D3DXVECTOR3(264.0f, 150.0f, 0.0f);	// ������@�̈ʒu
	}
}

//************************************************************
//	�X�^�e�B�b�N�A�T�[�g
//************************************************************
static_assert(NUM_ARRAY(TEXTURE_FILE) == CTutorialManager::TEXTURE_MAX, "ERROR : Texture Count Mismatch");

//************************************************************
//	�e�N���X [CTutorialManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CTutorialManager::CTutorialManager()
{
	// �����o�ϐ����N���A
	m_pExplain = nullptr;	// �����\���̏��
	m_pControl = nullptr;	// ��������̏��
}

//============================================================
//	�f�X�g���N�^
//============================================================
CTutorialManager::~CTutorialManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CTutorialManager::Init(void)
{
	// �����o�ϐ���������
	m_pExplain = nullptr;	// �����\���̏��
	m_pControl = nullptr;	// ��������̏��

	// �����\���̐���
	m_pExplain = CObject2D::Create
	( // ����
		lesson::POS,	// �ʒu
		lesson::SIZE	// �傫��
	);
	if (m_pExplain == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �e�N�X�`����o�^�E����
	m_pExplain->BindTexture(TEXTURE_FILE[TEXTURE_CONTROL]);

	// �D�揇�ʂ�ݒ�
	m_pExplain->SetPriority(PRIORITY);

	// ��������̐���
	m_pControl = CObject2D::Create
	( // ����
		control::POS,	// �ʒu
		control::SIZE	// �傫��
	);
	if (m_pControl == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �e�N�X�`����o�^�E����
	m_pControl->BindTexture(TEXTURE_FILE[TEXTURE_END]);

	// �D�揇�ʂ�ݒ�
	m_pControl->SetPriority(PRIORITY);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CTutorialManager::Uninit(void)
{
	// �����\���̏I��
	SAFE_UNINIT(m_pExplain);

	// ��������̏I��
	SAFE_UNINIT(m_pControl);
}

//============================================================
//	�X�V����
//============================================================
void CTutorialManager::Update(void)
{
	// �|�C���^��錾
	CInputKeyboard	*pKeyboard	= GET_INPUTKEY;	// �L�[�{�[�h
	CInputPad		*pPad		= GET_INPUTPAD;	// �p�b�h

	if (pKeyboard->IsTrigger(DIK_RETURN)
	||  pPad->IsTrigger(CInputPad::KEY_START)
	||	pPad->IsTrigger(CInputPad::KEY_A))
	{
		// �V�[���̐ݒ�
		GET_MANAGER->SetScene(CScene::MODE_TITLE);	// �^�C�g�����
	}

	// �����\���̍X�V
	m_pExplain->Update();

	// ��������̍X�V
	m_pControl->Update();
}

//============================================================
//	��������
//============================================================
CTutorialManager *CTutorialManager::Create(void)
{
	// �`���[�g���A���}�l�[�W���[�̐���
	CTutorialManager *pTutorialManager = new CTutorialManager;
	if (pTutorialManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �`���[�g���A���}�l�[�W���[�̏�����
		if (FAILED(pTutorialManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �`���[�g���A���}�l�[�W���[�̔j��
			SAFE_DELETE(pTutorialManager);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pTutorialManager;
	}
}

//============================================================
//	�j������
//============================================================
void CTutorialManager::Release(CTutorialManager *&prTutorialManager)
{
	// �`���[�g���A���}�l�[�W���[�̏I��
	assert(prTutorialManager != nullptr);
	prTutorialManager->Uninit();

	// �������J��
	SAFE_DELETE(prTutorialManager);
}
