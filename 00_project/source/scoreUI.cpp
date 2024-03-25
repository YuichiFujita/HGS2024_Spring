//============================================================
//
//	�^�C�}�[UI���� [timerUI.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "scoreUI.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "object2D.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char *TEXTURE_FILE[] =	// �e�N�X�`���t�@�C��
	{
		"data\\TEXTURE\\timer001.png",	// �w�i�e�N�X�`��
	};

	const int PRIORITY = 5;	// �^�C�}�[UI�̗D�揇��
}

//************************************************************
//	�X�^�e�B�b�N�A�T�[�g
//************************************************************
static_assert(NUM_ARRAY(TEXTURE_FILE) == CScoreUI::TEXTURE_MAX, "ERROR : Texture Count Mismatch");

//************************************************************
//	�q�N���X [CScoreUI] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CScoreUI::CScoreUI() :
	m_pBG		(nullptr),	// �w�i�̏��
	m_offsetBG	(VEC3_ZERO)	// �w�i�̃I�t�Z�b�g
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CScoreUI::~CScoreUI()
{

}

//============================================================
//	����������
//============================================================
HRESULT CScoreUI::Init(void)
{
	// �����o�ϐ���������
	m_pBG = nullptr;		// �w�i�̏��
	m_offsetBG = VEC3_ZERO;	// �w�i�̃I�t�Z�b�g

	// �w�i�̐���
	m_pBG = CObject2D::Create(VEC3_ZERO);
	if (m_pBG == nullptr)
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �e�N�X�`����o�^�E����
	m_pBG->BindTexture(TEXTURE_FILE[TEXTURE_BG]);

	// �^�C�}�[�}�l�[�W���[�̏�����
	if (FAILED(CMultiValue::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	SetLabel(LABEL_UI);

	// �D�揇�ʂ�ݒ�
	SetPriority(PRIORITY);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CScoreUI::Uninit(void)
{
	// �w�i�̏I��
	SAFE_UNINIT(m_pBG);

	// �^�C�}�[�}�l�[�W���[�̏I��
	CMultiValue::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CScoreUI::Update(void)
{
	// �w�i�̍X�V
	m_pBG->Update();

	// �^�C�}�[�}�l�[�W���[�̍X�V
	CMultiValue::Update();
}

//============================================================
//	�X�V�󋵂̐ݒ菈��
//============================================================
void CScoreUI::SetEnableUpdate(const bool bUpdate)
{
	// �w�i�̍X�V�󋵂�ݒ�
	m_pBG->SetEnableUpdate(bUpdate);

	// �X�V�󋵂̐ݒ�
	CMultiValue::SetEnableUpdate(bUpdate);
}

//============================================================
//	�`��󋵂̐ݒ菈��
//============================================================
void CScoreUI::SetEnableDraw(const bool bDraw)
{
	// �w�i�̍X�V�󋵂�ݒ�
	m_pBG->SetEnableDraw(bDraw);

	// �`��󋵂̐ݒ�
	CMultiValue::SetEnableDraw(bDraw);
}

//============================================================
//	��������
//============================================================
CScoreUI *CScoreUI::Create
(
	const int nNum,					// ����
	const int nDigit,				// ����
	const D3DXVECTOR3& rPos,		// �ʒu
	const D3DXVECTOR3& rSize,		// �傫��
	const D3DXVECTOR3& rSpace,		// �s��
	const D3DXVECTOR3& rRot,	// ����
	const D3DXCOLOR& rCol		// �F
)
{
	// �^�C�}�[UI�̐���
	CScoreUI *pTimerUI = new CScoreUI;
	if (pTimerUI == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �^�C�}�[UI�̏�����
		if (FAILED(pTimerUI->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �^�C�}�[UI�̔j��
			SAFE_DELETE(pTimerUI);
			return nullptr;
		}

		// ������ݒ�
		pTimerUI->SetDigit(nDigit);

		// ������ݒ�
		pTimerUI->SetNum(nNum);

		// �e�N�X�`����ݒ�
		pTimerUI->SetTexture(CValue::ETexture::TEXTURE_NORMAL);

		// ������ݒ�
		pTimerUI->SetVec3Rotation(rRot);

		// �傫����ݒ�
		pTimerUI->SetVec3Sizing(rSize);

		// �F��ݒ�
		pTimerUI->SetColor(rCol);

		// �s�Ԃ�ݒ�
		pTimerUI->SetSpace(rSpace);

		// �ʒu��ݒ�
		pTimerUI->SetVec3Position(rPos);

		// �m�ۂ����A�h���X��Ԃ�
		return pTimerUI;
	}
}

//============================================================
//	�j������
//============================================================
void CScoreUI::Release(CScoreUI *&prTimerUI)
{
	// �^�C�}�[UI�̏I��
	assert(prTimerUI != nullptr);
	prTimerUI->Uninit();

	// �������J��
	SAFE_DELETE(prTimerUI);
}

//============================================================
//	�I�t�Z�b�g�̐ݒ菈��
//============================================================
void CScoreUI::SetOffset(const D3DXVECTOR3& rOffset)
{
	// �I�t�Z�b�g�̐ݒ�
	m_offsetBG = rOffset;
}

//============================================================
//	�w�i�̑傫���ݒ菈��
//============================================================
void CScoreUI::SetSizingBG(const D3DXVECTOR3& rSize)
{
	// �w�i�̑傫����ݒ�
	assert(m_pBG != nullptr);
	m_pBG->SetVec3Sizing(rSize);
}
