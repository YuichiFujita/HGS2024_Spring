//============================================================
//
//	���f�������w�b�_�[ [modelFont.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _MODEL_FONT_H_
#define _MODEL_FONT_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "objectModel.h"
#include "scene.h"

//************************************************************
//	�N���X��`
//************************************************************
// ���f�������N���X
class CPlayer : public CObjectModel
{
public:
	// ��ޗ�
	enum EType
	{
		TYPE_BOSS_NAME = 0,	// �{�X�̖��O
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CPlayer();

	// �f�X�g���N�^
	~CPlayer() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(void) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;	// �`��

	void UpdateRot();
	void UpdateShot();

	float GetRadius() { return 10.0f; }

	// �ÓI�����o�֐�
	static CPlayer* Create	// ����
	( // ����
		const CScene::EMode mode,				// ���[�h
		const EType type,						// ���
		const D3DXVECTOR3& rPos,				// �ʒu
		const D3DXVECTOR3& rRot = VEC3_ZERO,	// ����
		const D3DXVECTOR3& rScale = VEC3_ONE	// �傫��
	);

private:
	float ShotPower;	//�e�̋���
};

#endif	// _MODEL_FONT_H_
