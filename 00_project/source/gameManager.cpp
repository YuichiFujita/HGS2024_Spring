//============================================================
//
//	�Q�[���}�l�[�W���[���� [gameManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "gameManager.h"
#include "manager.h"
#include "fade.h"
#include "scene.h"
#include "sceneGame.h"
#include "cinemaScope.h"
#include "timerUI.h"
#include "retentionManager.h"
#include "camera.h"
#include "player.h"
#include "multiModel.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int GAMEEND_WAIT_FRAME = 180;	// ���U���g��ʂւ̑J�ڗ]�C�t���[��
}

//************************************************************
//	�e�N���X [CGameManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CGameManager::CGameManager() :
	m_state	(STATE_NONE)	// ���
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CGameManager::~CGameManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CGameManager::Init(void)
{
	// �|�C���^��錾
	CPlayer *pPlayer = CScene::GetPlayer();	// �v���C���[�̏��

	// �����o�ϐ���������
	m_state = STATE_NORMAL;	// ���

	// �v���C���[���o��������
	pPlayer->SetSpawn();

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CGameManager::Uninit(void)
{

}

//============================================================
//	�X�V����
//============================================================
void CGameManager::Update(void)
{
	switch (m_state)
	{ // ��Ԃ��Ƃ̏���
	case STATE_NONE:
	case STATE_NORMAL:
	case STATE_STAGING:
		break;

	default:	// ��O����
		assert(false);
		break;
	}
}

//============================================================
//	��Ԑݒ菈��
//============================================================
void CGameManager::SetState(const EState state)
{
	// ��Ԃ�ݒ�
	m_state = state;
}

//============================================================
//	��Ԏ擾����
//============================================================
CGameManager::EState CGameManager::GetState(void) const
{
	// ��Ԃ�Ԃ�
	return m_state;
}

//============================================================
//	���U���g��ʑJ�ڏ���
//============================================================
void CGameManager::TransitionResult(const CRetentionManager::EWin win)
{
	// �^�C�}�[�̌v���I��
	CSceneGame::GetTimerUI()->End();

	// ���U���g����ۑ�
	GET_RETENTION->SetResult(win, CSceneGame::GetTimerUI()->Get());

	// ���U���g��ʂɑJ��
	GET_MANAGER->SetScene(CScene::MODE_RESULT, GAMEEND_WAIT_FRAME);
}

//============================================================
//	��������
//============================================================
CGameManager *CGameManager::Create(void)
{
	// �Q�[���}�l�[�W���[�̐���
	CGameManager *pGameManager = new CGameManager;
	if (pGameManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �Q�[���}�l�[�W���[�̏�����
		if (FAILED(pGameManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �Q�[���}�l�[�W���[�̔j��
			SAFE_DELETE(pGameManager);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pGameManager;
	}
}

//============================================================
//	�j������
//============================================================
void CGameManager::Release(CGameManager *&prGameManager)
{
	// �Q�[���}�l�[�W���[�̏I��
	assert(prGameManager != nullptr);
	prGameManager->Uninit();

	// �������J��
	SAFE_DELETE(prGameManager);
}
