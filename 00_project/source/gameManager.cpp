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
#include "effect3D.h"
#include "fire.h"
#include "hitStop.h"
#include "flash.h"
#include "wave.h"
#include "flower.h"
#include "collision.h"
#include "stage.h"
#include "multiValue.h"
#include "pause.h"
#include "rankingManager.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int GAMEEND_WAIT_FRAME = 90;	// ���U���g��ʂւ̑J�ڗ]�C�t���[��

	const int SPOWN_NUM = 4;	// �����̐�����
	const int SPOWN_RAND_POSX = 1200;	// ���̃����_�������͈�
	const float SPOWN_POSY = 1000.0f;	// �����̍���
	const int SPOWN_RAND_SPEED = 90;	// �������̉��̑��x�̃����_���͈�
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
	// �����o�ϐ���������
	m_state = STATE_NORMAL;	// ���

	//�������x����������
	Spownlevel = SPOWN_NUM;

	//�����J�E���g��������
	SpownCount = 0;

	// �Ԑ����J�E���g
	nFlowerCount = 0;

	// ���S����̔R���L�����
	m_fMoveBurn = 0.0f;

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
	case STATE_STAGING:
		break;

	case STATE_INIT_BURN:

		// �S�ĉ��o�̏������̊Ǘ�
		InitBurnManager();

		break;

	case STATE_BURN:

		// �S�ĉ��o�̊Ǘ�
		BurnManager();

		break;

	case STATE_NORMAL:
		if (!CSceneGame::GetPause()->IsPause())
		{
			SpownManager();
			CSceneGame::GetScoreUI()->SetNum(CFlower::GetList()->GetNumAll());
		}
		break;

	default:	// ��O����
		assert(false);
		break;
	}
}

//============================================================
//	�S�ď�Ԃ̐ݒ�
//============================================================
void CGameManager::SetBurn(void)
{
	if (m_state != STATE_NORMAL) { return; }

	// �^�C�}�[�v���I��
	CSceneGame::GetTimerUI()->End();

	// �J�����h���ݒ�
	GET_MANAGER->GetCamera()->SetSwing(CCamera::TYPE_MAIN, CCamera::SSwing(10.0f, 1.5f, 0.3f));

	// �q�b�g�X�g�b�v��ݒ�
	CSceneGame::GetHitStop()->SetStop(45);

	// �t���b�V����ݒ�
	CSceneGame::GetFlash()->Set(0.55f, 0.08f);

	// �����폜
	std::vector<CObject::ELabel> delVector;
	delVector.push_back(CObject::LABEL_FIRE);
	CObject::ReleaseAll(delVector);

	// �S�ď�������Ԃɂ���
	m_state = STATE_INIT_BURN;
}

//============================================================
//	�G�����̊Ǘ�
//============================================================
void CGameManager::SpownManager()
{
	SpownCount++;

	//���x���Ǘ�
	if (SpownCount != 0 && SpownCount % 1200 == 0)
	{
		Spownlevel++;
	}

	//�G�����Ǘ�
	if (SpownCount % 300 == 0)
	{
		for (int Spown = 0; Spown < Spownlevel; Spown++)
		{
			float frandPos = (float)(rand() % SPOWN_RAND_POSX + 1);
			float frandSpeed = (float)(rand() % SPOWN_RAND_SPEED + 1);
			int nRandFire = 0;

			if (Spownlevel >= 6)
			{
				nRandFire = rand() % 3;
			}
			else if (Spownlevel >= 5)
			{
				nRandFire = rand() % 2;
			}
			else
			{
				nRandFire = rand() % 1;
			}

			switch (nRandFire)
			{
			case 0:
				CFire::Create
				(
					CFire::EType::TYPE_NORMAL,
					1.0f + ((frandSpeed - ((float)SPOWN_RAND_SPEED * 0.5f)) * 0.01f),
					D3DXVECTOR3
					(
						frandPos - ((float)SPOWN_RAND_POSX * 0.5f),
						SPOWN_POSY,
						0.0f
					)
				);
				break;
			case 1:
				CFire::Create
				(
					CFire::EType::TYPE_FLUFFY,
					1.0f + ((frandSpeed - ((float)SPOWN_RAND_SPEED * 0.5f)) * 0.01f),
					D3DXVECTOR3
					(
						frandPos - ((float)SPOWN_RAND_POSX * 0.5f),
						SPOWN_POSY,
						0.0f
					)
				);
				break;
			case 2:
				CFire::Create
				(
					CFire::EType::TYPE_FAST,
					1.0f + ((frandSpeed - ((float)SPOWN_RAND_SPEED * 0.5f)) * 0.01f),
					D3DXVECTOR3
					(
						frandPos - ((float)SPOWN_RAND_POSX * 0.5f),
						SPOWN_POSY,
						0.0f
					)
				);
				break;
			default:
				break;
			}
		}
	}


}

//============================================================
//	�S�ĉ��o�̏������̊Ǘ�
//============================================================
void CGameManager::InitBurnManager(void)
{
	if (!CSceneGame::GetHitStop()->IsStop())
	{ // �q�b�g�X�g�b�v���I�������

		// �g������
		CWave::Create(CWave::TEXTURE_IMPACT, D3DXVECTOR3(0.0f, 80.0f, 0.0f), VEC3_ZERO, D3DXCOLOR(1.0f, 0.15f, 0.025f, 0.7f), CWave::SGrow(18.0f, 14.0f, 0.01f), POSGRID2(32, 1), ring::TEX_PART, ring::HOLE_RADIUS, ring::THICKNESS, 40.0f);
		//CWave::Create(CWave::TEXTURE_IMPACT, D3DXVECTOR3(0.0f, 90.0f, 0.0f),  VEC3_ZERO, D3DXCOLOR(1.0f, 0.15f, 0.025f, 0.7f), CWave::SGrow(40.0f, 12.0f, 0.03f), POSGRID2(32, 1), ring::TEX_PART, ring::HOLE_RADIUS, ring::THICKNESS, 40.0f);
		CWave::Create(CWave::TEXTURE_IMPACT, D3DXVECTOR3(0.0f, 40.0f, 0.0f),  VEC3_ZERO, D3DXCOLOR(1.0f, 0.15f, 0.025f, 0.7f), CWave::SGrow(3.0f, 10.0f, 0.015f), POSGRID2(32, 1), ring::TEX_PART, ring::HOLE_RADIUS, ring::THICKNESS, 40.0f);

		// �S�ĊJ�n
		m_state = STATE_BURN;
	}
}

//============================================================
//	�S�ĉ��o�̊Ǘ�
//============================================================
void CGameManager::BurnManager(void)
{
	// ���S����̔R���L����ʂ��L����
	m_fMoveBurn += 45.0f;

	// �Ԃ̃��X�g�擾
	CListManager<CFlower> *pList = CFlower::GetList();
	if (pList == nullptr) { return; }

	std::list<CFlower*> list = pList->GetList();
	for (auto pFlower : list)
	{ // �S�v�f���J��Ԃ�

		// ��Ԃ��ύX����Ă���ꍇ������
		CFlower::EState state = (CFlower::EState)pFlower->GetState();
		if (state != CFlower::EState::NONE) { continue; }

		// ����
		bool bHit = collision::Circle2D
		(
			pFlower->GetVec3Position(),
			VEC3_ZERO,
			pFlower->GetRadius(),
			m_fMoveBurn
		);
		if (bHit)
		{ // ���������ꍇ

			// ���������ɂ���
			pFlower->Burn();
		}
	}

	if (m_fMoveBurn >= CScene::GetStage()->GetStageLimit().fRadius)
	{ // �X�e�[�W�̔��a�𒴂���

		// ���U���g��ʑJ��
		TransitionResult();
	}
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
void CGameManager::TransitionResult(void)
{
	// �t�F�[�h���Ă���ꍇ������
	if (GET_MANAGER->GetFade()->GetState() != CFade::FADE_NONE) { return; }

	// �^�C�}�[�̌v���I��
	CSceneGame::GetTimerUI()->End();

	// ���U���g����ۑ�
	GET_RETENTION->SetResult(CSceneGame::GetTimerUI()->Get());

	// ���U���g����ۑ�
	GET_RETENTION->SetScore(CSceneGame::GetScoreUI()->GetNum());

	// �����L���O�ɐݒ�
	CRankingManager::Set(CSceneGame::GetScoreUI()->GetNum());

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
