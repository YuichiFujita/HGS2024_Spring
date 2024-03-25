//============================================================
//
//	���w�b�_�[ [fire.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _FIRE_H_
#define _FIRE_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object.h"

//************************************************************
//	�N���X��`
//************************************************************
// ���N���X
class CFire : public CObject
{
public:
	// ��ޗ�
	enum EType
	{
		TYPE_NORMAL = 0,	// �^������
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	explicit CFire(const EType type);

	// �f�X�g���N�^
	virtual ~CFire();

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	void Uninit(void) override;		// �I��
	void Update(void) override;		// �X�V
	void Draw(CShader *pShader = nullptr) override;			// �`��
	void SetVec3Position(const D3DXVECTOR3& rPos) override;	// �ʒu�ݒ�
	D3DXVECTOR3 GetVec3Position(void) const override;		// �ʒu�擾
	int GetType(void) const override;						// ��ގ擾
	float GetRadius(void) const override;					// ���a�擾

	// �ÓI�����o�֐�
	static CFire *Create	// ����
	( // ����
		const EType type,		// ���
		const float fGravity,	// �d��
		const D3DXVECTOR3& rPos	// �ʒu
	);

	// �����o�֐�
	void SetMovePosition(const D3DXVECTOR3& rMove);	// �ʒu�ړ��ʐݒ�
	D3DXVECTOR3 GetMovePosition(void) const;		// �ʒu�ړ��ʎ擾

protected:
	// �������z�֐�
	virtual void UpdateMove(void) = 0;	// �����̍X�V

	// �����o�֐�
	void UpdatePosition(D3DXVECTOR3 *pPos);	// �ʒu�̍X�V

private:
	// �I�[�o�[���C�h�֐�
	void Release(void) override;	// �j��

	// �����o�֐�
	void UpdateGravity(void);	// �d�͂̍X�V
	bool UpdateDelete(void);	// �폜�̍X�V

	// �����o�ϐ�
	D3DXVECTOR3	m_pos;	// �ʒu
	D3DXVECTOR3	m_move;	// �ړ���
	float m_fGravity;	// �d��
	const EType m_type;	// ��ޒ萔
};

#endif	// _FIRE_H_
