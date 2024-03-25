//============================================================
//
//	�f�[�^�ۑ��}�l�[�W���[�w�b�_�[ [retentionManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _RETENTION_MANAGER_H_
#define _RETENTION_MANAGER_H_

//************************************************************
//	�N���X��`
//************************************************************
// �f�[�^�ۑ��}�l�[�W���[�N���X
class CRetentionManager
{
public:
	// �R���X�g���N�^
	CRetentionManager();

	// �f�X�g���N�^
	~CRetentionManager();

	// ���U���g���\����
	struct SResult
	{
		int nScore;	// �o�߃^�C��
		long nTime;	// �o�߃^�C��
	};

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��

	// �ÓI�����o�֐�
	static CRetentionManager *Create(void);	// ����
	static void Release(CRetentionManager *&prRetentionManager);	// �j��

	// �����o�֐�
	void SetScore(const int Score);	// ���U���g���ݒ�
	int GetScore(void) const { return m_result.nScore; }	// ���U���g���擾
	void SetResult(const long nTime);	// ���U���g���ݒ�
	int GetResult(void) const { return m_result.nTime; }	// ���U���g���擾

private:
	// �����o�ϐ�
	SResult m_result;	// ���U���g���
};

#endif	// _RETENTION_MANAGER_H_
