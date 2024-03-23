//============================================================
//
//	����֐����� [collision.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "collision.h"
#include "effect3D.h"

//============================================================
//	XZ���ʂ̋�`�̓����蔻��
//============================================================
bool collision::Box2D
(
	D3DXVECTOR3 centerPos,		// ����ʒu
	D3DXVECTOR3 targetPos,		// ����ڕW�ʒu
	D3DXVECTOR3 centerSizeUp,	// ����T�C�Y(�E�E��E��)
	D3DXVECTOR3 centerSizeDown,	// ����T�C�Y(���E���E�O)
	D3DXVECTOR3 targetSizeUp,	// ����ڕW�T�C�Y(�E�E��E��)
	D3DXVECTOR3 targetSizeDown	// ����ڕW�T�C�Y(���E���E�O)
)
{
	if (centerPos.x + centerSizeUp.x   > targetPos.x - targetSizeDown.x
	&&  centerPos.z + centerSizeUp.z   > targetPos.z - targetSizeDown.z
	&&  centerPos.x - centerSizeDown.x < targetPos.x + targetSizeUp.x
	&&  centerPos.z - centerSizeDown.z < targetPos.z + targetSizeUp.z)
	{ // ������̏ꍇ

		// �^��Ԃ�
		return true;
	}

	// �U��Ԃ�
	return false;
}

//============================================================
//	3���̋�`�̓����蔻��
//============================================================
bool collision::Box3D
(
	D3DXVECTOR3 centerPos,		// ����ʒu
	D3DXVECTOR3 targetPos,		// ����ڕW�ʒu
	D3DXVECTOR3 centerSizeUp,	// ����T�C�Y(�E�E��E��)
	D3DXVECTOR3 centerSizeDown,	// ����T�C�Y(���E���E�O)
	D3DXVECTOR3 targetSizeUp,	// ����ڕW�T�C�Y(�E�E��E��)
	D3DXVECTOR3 targetSizeDown	// ����ڕW�T�C�Y(���E���E�O)
)
{
	if (centerPos.x + centerSizeUp.x   > targetPos.x - targetSizeDown.x
	&&  centerPos.y + centerSizeUp.y   > targetPos.y - targetSizeDown.y
	&&  centerPos.z + centerSizeUp.z   > targetPos.z - targetSizeDown.z
	&&  centerPos.x - centerSizeDown.x < targetPos.x + targetSizeUp.x
	&&  centerPos.y - centerSizeDown.y < targetPos.y + targetSizeUp.y
	&&  centerPos.z - centerSizeDown.z < targetPos.z + targetSizeUp.z)
	{ // ������̏ꍇ

		// �^��Ԃ�
		return true;
	}

	// �U��Ԃ�
	return false;
}

//============================================================
//	XZ���ʂ̉~�̓����蔻��
//============================================================
bool collision::Circle2D
(
	D3DXVECTOR3 centerPos,	// ����ʒu
	D3DXVECTOR3 targetPos,	// ����ڕW�ʒu
	float fCenterRadius,	// ���蔼�a
	float fTargetRadius,	// ����ڕW���a
	float *pLength			// ����ڕW�Ƃ̋���
)
{
	// �ϐ���錾
	float fLength  = 0.0f;	// ����ʒu�Ɣ���ڕW�ʒu�̊Ԃ̋���

	// ����ʒu�Ɣ���ڕW�ʒu�̋��������߂�
	fLength = (centerPos.x - targetPos.x) * (centerPos.x - targetPos.x)
			+ (centerPos.z - targetPos.z) * (centerPos.z - targetPos.z);

	if (pLength != nullptr)
	{ // �|�C���^���g�p����Ă���ꍇ

		// ����ڕW�Ƃ̋�������
		*pLength = fLength;
	}

	if (fLength < ((fCenterRadius + fTargetRadius) * (fCenterRadius + fTargetRadius)))
	{ // ������̏ꍇ

		// �^��Ԃ�
		return true;
	}

	// �U��Ԃ�
	return false;
}

//============================================================
//	3���̉~�̓����蔻��
//============================================================
bool collision::Circle3D
(
	D3DXVECTOR3 centerPos,	// ����ʒu
	D3DXVECTOR3 targetPos,	// ����ڕW�ʒu
	float fCenterRadius,	// ���蔼�a
	float fTargetRadius		// ����ڕW���a
)
{
	// �ϐ���錾
	float fLength  = 0.0f;	// ����ʒu�Ɣ���ڕW�ʒu�̊Ԃ̋���

	// ����ʒu�Ɣ���ڕW�ʒu�̋��������߂�
	fLength = (centerPos.x - targetPos.x) * (centerPos.x - targetPos.x)
			+ (centerPos.y - targetPos.y) * (centerPos.y - targetPos.y)
			+ (centerPos.z - targetPos.z) * (centerPos.z - targetPos.z);

	if (fLength < ((fCenterRadius + fTargetRadius) * (fCenterRadius + fTargetRadius)))
	{ // ������̏ꍇ

		// �^��Ԃ�
		return true;
	}

	// �U��Ԃ�
	return false;
}

//============================================================
//	XZ���ʂ̐�`�̓����蔻��
//============================================================
bool collision::Sector
(
	D3DXVECTOR3 centerPos,	// ����ʒu
	D3DXVECTOR3 targetPos,	// ����ڕW�ʒu
	float fCenterRot,		// �������
	float fRadius,			// ���E�͈�
	float fAngle,			// ����p
	float *pLength			// ����ڕW�Ƃ̋���
)
{
	// �ϐ���錾
	bool  bHit = false;		// �����蔻��̌���
	float fLength;			// ���S�ʒu�ƖڕW�ʒu�̋���
	float fHalfAngle;		// �����̊p�x�̔����̒l�̑���p
	D3DXVECTOR3 vecToPos;	// ���[�ƈʒu�̃x�N�g��

	// �ϐ��z���錾
	float fRotEdge[2];		// ��`�̉��̊p�x     [��] 0�F�� 1�F�E
	D3DXVECTOR3 posEdge[2];	// ��`�̉��̐�[�ʒu [��] 0�F�� 1�F�E
	D3DXVECTOR3 vecEdge[2];	// ��`�̉��x�N�g��   [��] 0�F�� 1�F�E

	// ���S�ʒu�ƖڕW�ʒu�̋������߂�
	fLength = (centerPos.x - targetPos.x) * (centerPos.x - targetPos.x)
			+ (centerPos.z - targetPos.z) * (centerPos.z - targetPos.z);

	if (pLength != nullptr)
	{ // �|�C���^���g�p����Ă���ꍇ

		// ����ڕW�Ƃ̋�������
		*pLength = fLength;
	}

	if (fLength < fRadius * fRadius)
	{ // �~�͈͓̔��̏ꍇ

		// �����̊p�x�̔����̒l�����߂�
		fHalfAngle = fAngle * 0.5f;

		// ��`�̍����̊p�x�����߂�
		fRotEdge[0] = fCenterRot + fHalfAngle;	// �p�x�����ɌX����
		useful::NormalizeRot(fRotEdge[0]);		// �����𐳋K��

		// ��`�̉E���̊p�x�����߂�
		fRotEdge[1] = fCenterRot - fHalfAngle;	// �p�x���E�ɌX����
		useful::NormalizeRot(fRotEdge[1]);		// �����𐳋K��

		// ��`�̍����̐�[�ʒu�����߂�
		posEdge[0].x = centerPos.x + sinf(fRotEdge[0]);
		posEdge[0].y = 0.0f;
		posEdge[0].z = centerPos.z + cosf(fRotEdge[0]);

		// ��`�̉E���̐�[�ʒu�����߂�
		posEdge[1].x = centerPos.x + sinf(fRotEdge[1]);
		posEdge[1].y = 0.0f;
		posEdge[1].z = centerPos.z + cosf(fRotEdge[1]);

		// ��`�̍����̃x�N�g�������߂�
		vecEdge[0] = posEdge[0] - centerPos;
		vecEdge[0].y = 0.0f;

		// ��`�̉E���̃x�N�g�������߂�
		vecEdge[1] = posEdge[1] - centerPos;
		vecEdge[1].y = 0.0f;

		// ���[�ƈʒu�̃x�N�g�������߂�
		vecToPos = targetPos - centerPos;

		if ((vecEdge[0].z * vecToPos.x) - (vecEdge[0].x * vecToPos.z) < 0
		&&  (vecEdge[1].z * vecToPos.x) - (vecEdge[1].x * vecToPos.z) > 0)
		{ // ��`�̗����͈͓̔��̏ꍇ

			// �������Ă����Ԃɂ���
			bHit = true;
		}
	}

	// �����蔻��̌��ʂ�Ԃ�
	return bHit;
}

//============================================================
//	�p���̏Փ˔���
//============================================================
bool collision::BoxPillar
(
	D3DXVECTOR3& rCenterPos,	// ����ʒu
	D3DXVECTOR3& rCenterPosOld,	// ����ߋ��ʒu
	D3DXVECTOR3 targetPos,		// ����ڕW�ʒu
	D3DXVECTOR3 centerSizeUp,	// ����T�C�Y(�E�E��E��)
	D3DXVECTOR3 centerSizeDown,	// ����T�C�Y(���E���E�O)
	D3DXVECTOR3 targetSizeUp,	// ����ڕW�T�C�Y(�E�E��E��)
	D3DXVECTOR3 targetSizeDown	// ����ڕW�T�C�Y(���E���E�O)
)
{
	// �ϐ���錾
	bool bHit = false;	// �Փ˔��茋��

	// �O��̓����蔻��
	if (rCenterPos.x + centerSizeUp.x > targetPos.x - targetSizeDown.x
	&&  rCenterPos.x - centerSizeDown.x < targetPos.x + targetSizeUp.x)
	{ // ���E�͈͓̔��̏ꍇ

		if (rCenterPos.z    + centerSizeUp.z >  targetPos.z - targetSizeDown.z
		&&  rCenterPosOld.z + centerSizeUp.z <= targetPos.z - targetSizeDown.z)
		{ // �O����̓����蔻��

			// �ʒu��␳
			rCenterPos.z = targetPos.z - targetSizeDown.z - centerSizeUp.z;

			// �Փˏ�Ԃɂ���
			bHit = true;
		}
		else if (rCenterPos.z    - centerSizeDown.z <  targetPos.z + targetSizeUp.z
		     &&  rCenterPosOld.z - centerSizeDown.z >= targetPos.z + targetSizeUp.z)
		{ // �ォ��̓����蔻��

			// �ʒu��␳
			rCenterPos.z = targetPos.z + targetSizeUp.z + centerSizeDown.z;

			// �Փˏ�Ԃɂ���
			bHit = true;
		}
	}

	// ���E�̓����蔻��
	if (rCenterPos.z + centerSizeUp.z > targetPos.z - targetSizeDown.z
	&&  rCenterPos.z - centerSizeDown.z < targetPos.z + targetSizeUp.z)
	{ // �O��͈͓̔��̏ꍇ

		if (rCenterPos.x    + centerSizeUp.x >  targetPos.x - targetSizeDown.x
		&&  rCenterPosOld.x + centerSizeUp.x <= targetPos.x - targetSizeDown.x)
		{ // ������̓����蔻��

			// �ʒu��␳
			rCenterPos.x = targetPos.x - targetSizeDown.x - centerSizeUp.x;

			// �Փˏ�Ԃɂ���
			bHit = true;
		}
		else if (rCenterPos.x    - centerSizeDown.x <  targetPos.x + targetSizeUp.x
		     &&  rCenterPosOld.x - centerSizeDown.x >= targetPos.x + targetSizeUp.x)
		{ // �E����̓����蔻��
			
			// �ʒu��␳
			rCenterPos.x = targetPos.x + targetSizeUp.x + centerSizeDown.x;

			// �Փˏ�Ԃɂ���
			bHit = true;
		}
	}

	// �Փ˔����Ԃ�
	return bHit;
}

//============================================================
//	�~���̏Փ˔���
//============================================================
bool collision::CirclePillar
(
	D3DXVECTOR3& rCenterPos,	// ����ʒu
	D3DXVECTOR3 targetPos,		// ����ڕW�ʒu
	float fCenterRadius,		// ���蔼�a
	float fTargetRadius			// ����ڕW���a
)
{
	// �ϐ���錾
	float fLength = 0.0f;	// ����ʒu�Ɣ���ڕW�ʒu�̊Ԃ̋���

	// ����ʒu�Ɣ���ڕW�ʒu�̋��������߂�
	fLength = (rCenterPos.x - targetPos.x) * (rCenterPos.x - targetPos.x)
			+ (rCenterPos.z - targetPos.z) * (rCenterPos.z - targetPos.z);

	if (fLength < (fCenterRadius + fTargetRadius) * (fCenterRadius + fTargetRadius))
	{ // ������̏ꍇ

		// �ϐ���錾
		float fCenterRot = atan2f(rCenterPos.x - targetPos.x, rCenterPos.z - targetPos.z);	// ����ڕW���猩���������

		// �ʒu��␳
		rCenterPos.x = targetPos.x + sinf(fCenterRot) * (fCenterRadius + fTargetRadius);
		rCenterPos.z = targetPos.z + cosf(fCenterRot) * (fCenterRadius + fTargetRadius);

		// �^��Ԃ�
		return true;
	}

	// �U��Ԃ�
	return false;
}

//============================================================
//	�O���̋�`�̏Փ˔���
//============================================================
bool collision::ResponseBox3D
(
	D3DXVECTOR3& rCenterPos,	// ����ʒu
	D3DXVECTOR3& rCenterPosOld,	// ����ߋ��ʒu
	D3DXVECTOR3 targetPos,		// ����ڕW�ʒu
	D3DXVECTOR3 centerSizeUp,	// ����T�C�Y(�E�E��E��)
	D3DXVECTOR3 centerSizeDown,	// ����T�C�Y(���E���E�O)
	D3DXVECTOR3 targetSizeUp,	// ����ڕW�T�C�Y(�E�E��E��)
	D3DXVECTOR3 targetSizeDown,	// ����ڕW�T�C�Y(���E���E�O)
	D3DXVECTOR3 *pMove,	// �ړ���
	bool *pUp,			// �ォ��̔���
	bool *pSide,		// ������̔���
	bool *pDown			// ������̔���
)
{
	// �ϐ���錾
	bool bHit = false;	// �Փ˔��茋��

	// ���E�̓����蔻��
	if (rCenterPos.y + centerSizeUp.y   > targetPos.y - targetSizeDown.y
	&&  rCenterPos.y - centerSizeDown.y < targetPos.y + targetSizeUp.y
	&&  rCenterPos.z + centerSizeUp.z   > targetPos.z - targetSizeDown.z
	&&  rCenterPos.z - centerSizeDown.z < targetPos.z + targetSizeUp.z)
	{ // �㉺�ƑO��͈͓̔��̏ꍇ

		if (rCenterPos.x    + centerSizeUp.x >  targetPos.x - targetSizeDown.x
		&&  rCenterPosOld.x + centerSizeUp.x <= targetPos.x - targetSizeDown.x)
		{ // ������̓����蔻��

			// �ʒu��␳
			rCenterPos.x = targetPos.x - targetSizeDown.x - centerSizeUp.x;

			// �Փˏ�Ԃɂ���
			bHit = true;

			if (pMove != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �ړ��ʂ�������
				pMove->x = 0.0f;
			}

			if (pSide != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// ���ɓ������Ă����Ԃ�ݒ�
				*pSide = true;
			}
		}
		else if (rCenterPos.x    - centerSizeDown.x <  targetPos.x + targetSizeUp.x
		     &&  rCenterPosOld.x - centerSizeDown.x >= targetPos.x + targetSizeUp.x)
		{ // �E����̓����蔻��
			
			// �ʒu��␳
			rCenterPos.x = targetPos.x + targetSizeUp.x + centerSizeDown.x;

			// �Փˏ�Ԃɂ���
			bHit = true;

			if (pMove != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �ړ��ʂ�������
				pMove->x = 0.0f;
			}

			if (pSide != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// ���ɓ������Ă����Ԃ�ݒ�
				*pSide = true;
			}
		}
	}

	// �㉺�̓����蔻��
	if (rCenterPos.x + centerSizeUp.x   > targetPos.x - targetSizeDown.x
	&&  rCenterPos.x - centerSizeDown.x < targetPos.x + targetSizeUp.x
	&&  rCenterPos.z + centerSizeUp.z   > targetPos.z - targetSizeDown.z
	&&  rCenterPos.z - centerSizeDown.z < targetPos.z + targetSizeUp.z)
	{ // ���E�ƑO��͈͓̔��̏ꍇ

		if (rCenterPos.y    + centerSizeUp.y >  targetPos.y - targetSizeDown.y
		&&  rCenterPosOld.y + centerSizeUp.y <= targetPos.y - targetSizeDown.y)
		{ // ������̓����蔻��

			// �ʒu��␳
			rCenterPos.y = targetPos.y - targetSizeDown.y - centerSizeUp.y;

			// �Փˏ�Ԃɂ���
			bHit = true;

			if (pMove != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �ړ��ʂ�������
				pMove->y = 0.0f;
			}

			if (pDown != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// ���ɓ������Ă����Ԃ�ݒ�
				*pDown = true;
			}
		}
		else if (rCenterPos.y    - centerSizeDown.y <  targetPos.y + targetSizeUp.y
		     &&  rCenterPosOld.y - centerSizeDown.y >= targetPos.y + targetSizeUp.y)
		{ // �ォ��̓����蔻��
			
			// �ʒu��␳
			rCenterPos.y = targetPos.y + targetSizeUp.y + centerSizeDown.y;

			// �Փˏ�Ԃɂ���
			bHit = true;

			if (pMove != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �ړ��ʂ�������
				pMove->y = 0.0f;
			}

			if (pUp != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// ��ɓ������Ă����Ԃ�ݒ�
				*pUp = true;
			}
		}
	}

	// �O��̓����蔻��
	if (rCenterPos.x + centerSizeUp.x   > targetPos.x - targetSizeDown.x
	&&  rCenterPos.x - centerSizeDown.x < targetPos.x + targetSizeUp.x
	&&  rCenterPos.y + centerSizeUp.y   > targetPos.y - targetSizeDown.y
	&&  rCenterPos.y - centerSizeDown.y < targetPos.y + targetSizeUp.y)
	{ // ���E�Ə㉺�͈͓̔��̏ꍇ

		if (rCenterPos.z    + centerSizeUp.z >  targetPos.z - targetSizeDown.z
		&&  rCenterPosOld.z + centerSizeUp.z <= targetPos.z - targetSizeDown.z)
		{ // �O����̓����蔻��

			// �ʒu��␳
			rCenterPos.z = targetPos.z - targetSizeDown.z - centerSizeUp.z;

			// �Փˏ�Ԃɂ���
			bHit = true;

			if (pMove != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �ړ��ʂ�������
				pMove->z = 0.0f;
			}

			if (pSide != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// ���ɓ������Ă����Ԃ�ݒ�
				*pSide = true;
			}
		}
		else if (rCenterPos.z    - centerSizeDown.z <  targetPos.z + targetSizeUp.z
		     &&  rCenterPosOld.z - centerSizeDown.z >= targetPos.z + targetSizeUp.z)
		{ // �ォ��̓����蔻��

			// �ʒu��␳
			rCenterPos.z = targetPos.z + targetSizeUp.z + centerSizeDown.z;

			// �Փˏ�Ԃɂ���
			bHit = true;

			if (pMove != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �ړ��ʂ�������
				pMove->z = 0.0f;
			}

			if (pSide != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// ���ɓ������Ă����Ԃ�ݒ�
				*pSide = true;
			}
		}
	}

	// �Փ˔����Ԃ�
	return bHit;
}

//============================================================
//	�O���̉~�̏Փ˔���
//============================================================
bool collision::ResponseCircle3D
(
	D3DXVECTOR3& rCenterPos,	// ����ʒu
	D3DXVECTOR3 targetPos,		// ����ڕW�ʒu
	float fCenterRadius,		// ���蔼�a
	float fTargetRadius			// ����ڕW���a
)
{
	// �ϐ���錾
	float fLength = 0.0f;	// ����ʒu�Ɣ���ڕW�ʒu�̊Ԃ̋���

	// ����ʒu�Ɣ���ڕW�ʒu�̋��������߂�
	fLength = (rCenterPos.x - targetPos.x) * (rCenterPos.x - targetPos.x)
			+ (rCenterPos.y - targetPos.y) * (rCenterPos.y - targetPos.y)
			+ (rCenterPos.z - targetPos.z) * (rCenterPos.z - targetPos.z);

	if (fLength < ((fCenterRadius + fTargetRadius) * (fCenterRadius + fTargetRadius)))
	{ // ������̏ꍇ

		// �ϐ���錾
		D3DXVECTOR3 vecRev = rCenterPos - targetPos;	// �␳����
		D3DXVECTOR3 sphere;	// �����W
		float fPhi, fTheta;	// ���ʊp�E�p

		// �x�N�g���������ɕϊ����A�������狅���W�����߂�
		useful::VecToRot(vecRev, &fPhi, &fTheta);
		useful::RotToVec(fPhi, fTheta, &sphere);

		// �ʒu��␳
		rCenterPos = targetPos + sphere * (fCenterRadius + fTargetRadius);

		// �^��Ԃ�
		return true;
	}

	// �U��Ԃ�
	return false;
}

//============================================================
//	�O���̃J�v�Z���̏Փ˔���
//============================================================
bool collision::ResponseCapsule3D
(
	D3DXVECTOR3 *pCenterPos,	// ����ʒu
	D3DXVECTOR3& rTargetPos,	// ����ڕW�ʒu
	float fCenterRadius,		// ���蔼�a
	float fTargetRadius,		// ����ڕW���a
	float fTargetHeight			// ����ڕW�c��
)
{
	// �ϐ���錾
	bool bHit = false;	// �Փ˔��茋��
	float fHalfHeight = (fTargetHeight - (fTargetRadius * 2.0f)) * 0.5f;			// �~���c���̔���
	D3DXVECTOR3 centUp   = *pCenterPos + D3DXVECTOR3(0.0f, fCenterRadius, 0.0f);	// ����ʒu�̏�
	D3DXVECTOR3 centDown = *pCenterPos - D3DXVECTOR3(0.0f, fCenterRadius, 0.0f);	// ����ʒu�̉�
	D3DXVECTOR3 targUp   = rTargetPos + D3DXVECTOR3(0.0f, fHalfHeight, 0.0f);		// ����ڕW�ʒu�̏�
	D3DXVECTOR3 targDown = rTargetPos - D3DXVECTOR3(0.0f, fHalfHeight, 0.0f);		// ����ڕW�ʒu�̉�

	if (centDown.y >= targUp.y)
	{ // �~������̏㑤�ɂ���ꍇ

		// ��̋�����
		bHit = collision::ResponseCircle3D
		( // ����
			*pCenterPos,	// ����ʒu
			targUp,			// ����ڕW�ʒu
			fCenterRadius,	// ���蔼�a
			fTargetRadius	// ����ڕW���a
		);
	}
	else if (centUp.y <= targDown.y)
	{ // �~������̉����ɂ���ꍇ

		// ���̋�����
		bHit = collision::ResponseCircle3D
		( // ����
			*pCenterPos,	// ����ʒu
			targDown,		// ����ڕW�ʒu
			fCenterRadius,	// ���蔼�a
			fTargetRadius	// ����ڕW���a
		);
	}
	else
	{ // �㉺�͈͓̔��̏ꍇ

		// �~���̔���
		bHit = collision::CirclePillar
		( // ����
			*pCenterPos,	// ����ʒu
			rTargetPos,		// ����ڕW�ʒu
			fCenterRadius,	// ���蔼�a
			fTargetRadius	// ����ڕW���a
		);
	}

	// �Փ˔����Ԃ�
	return bHit;
}

//============================================================
//	X���̏Փ˔���
//============================================================
bool collision::ResponseSingleX
(
	D3DXVECTOR3& rCenterPos,	// ����ʒu
	D3DXVECTOR3& rCenterPosOld,	// ����ߋ��ʒu
	D3DXVECTOR3 targetPos,		// ����ڕW�ʒu
	D3DXVECTOR3 centerSizeUp,	// ����T�C�Y(�E�E��E��)
	D3DXVECTOR3 centerSizeDown,	// ����T�C�Y(���E���E�O)
	D3DXVECTOR3 targetSizeUp,	// ����ڕW�T�C�Y(�E�E��E��)
	D3DXVECTOR3 targetSizeDown,	// ����ڕW�T�C�Y(���E���E�O)
	D3DXVECTOR3 *pMove,	// �ړ���
	bool *pLeft,		// ������̔���
	bool *pRight		// �E����̔���
)
{
	// �ϐ���錾
	bool bHit = false;	// �Փ˔��茋��

	// ���E�̓����蔻��
	if (rCenterPos.y + centerSizeUp.y   > targetPos.y - targetSizeDown.y
	&&  rCenterPos.y - centerSizeDown.y < targetPos.y + targetSizeUp.y
	&&  rCenterPos.z + centerSizeUp.z   > targetPos.z - targetSizeDown.z
	&&  rCenterPos.z - centerSizeDown.z < targetPos.z + targetSizeUp.z)
	{ // �㉺�ƑO��͈͓̔��̏ꍇ

		if (rCenterPos.x    + centerSizeUp.x >  targetPos.x - targetSizeDown.x
		&&  rCenterPosOld.x + centerSizeUp.x <= targetPos.x - targetSizeDown.x)
		{ // ������̓����蔻��

			// �ʒu��␳
			rCenterPos.x = targetPos.x - targetSizeDown.x - centerSizeUp.x;

			// �Փˏ�Ԃɂ���
			bHit = true;

			if (pMove != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �ړ��ʂ�������
				pMove->x = 0.0f;
			}

			if (pLeft != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// ���ɓ������Ă����Ԃ�ݒ�
				*pLeft = true;
			}
		}
		else if (rCenterPos.x    - centerSizeDown.x <  targetPos.x + targetSizeUp.x
		     &&  rCenterPosOld.x - centerSizeDown.x >= targetPos.x + targetSizeUp.x)
		{ // �E����̓����蔻��
			
			// �ʒu��␳
			rCenterPos.x = targetPos.x + targetSizeUp.x + centerSizeDown.x;

			// �Փˏ�Ԃɂ���
			bHit = true;

			if (pMove != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �ړ��ʂ�������
				pMove->x = 0.0f;
			}

			if (pRight != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �E�ɓ������Ă����Ԃ�ݒ�
				*pRight = true;
			}
		}
	}

	// �Փ˔����Ԃ�
	return bHit;
}

//============================================================
//	Y���̏Փ˔���
//============================================================
bool collision::ResponseSingleY
(
	D3DXVECTOR3& rCenterPos,	// ����ʒu
	D3DXVECTOR3& rCenterPosOld,	// ����ߋ��ʒu
	D3DXVECTOR3 targetPos,		// ����ڕW�ʒu
	D3DXVECTOR3 centerSizeUp,	// ����T�C�Y(�E�E��E��)
	D3DXVECTOR3 centerSizeDown,	// ����T�C�Y(���E���E�O)
	D3DXVECTOR3 targetSizeUp,	// ����ڕW�T�C�Y(�E�E��E��)
	D3DXVECTOR3 targetSizeDown,	// ����ڕW�T�C�Y(���E���E�O)
	D3DXVECTOR3 *pMove,	// �ړ���
	bool *pDown,		// ������̔���
	bool *pUp			// �ォ��̔���
)
{
	// �ϐ���錾
	bool bHit = false;	// �Փ˔��茋��

	// �㉺�̓����蔻��
	if (rCenterPos.x + centerSizeUp.x   > targetPos.x - targetSizeDown.x
	&&  rCenterPos.x - centerSizeDown.x < targetPos.x + targetSizeUp.x
	&&  rCenterPos.z + centerSizeUp.z   > targetPos.z - targetSizeDown.z
	&&  rCenterPos.z - centerSizeDown.z < targetPos.z + targetSizeUp.z)
	{ // ���E�ƑO��͈͓̔��̏ꍇ

		if (rCenterPos.y    + centerSizeUp.y >  targetPos.y - targetSizeDown.y
		&&  rCenterPosOld.y + centerSizeUp.y <= targetPos.y - targetSizeDown.y)
		{ // ������̓����蔻��

			// �ʒu��␳
			rCenterPos.y = targetPos.y - targetSizeDown.y - centerSizeUp.y;

			// �Փˏ�Ԃɂ���
			bHit = true;

			if (pMove != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �ړ��ʂ�������
				pMove->y = 0.0f;
			}

			if (pDown != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// ���ɓ������Ă����Ԃ�ݒ�
				*pDown = true;
			}
		}
		else if (rCenterPos.y    - centerSizeDown.y <  targetPos.y + targetSizeUp.y
		     &&  rCenterPosOld.y - centerSizeDown.y >= targetPos.y + targetSizeUp.y)
		{ // �ォ��̓����蔻��
			
			// �ʒu��␳
			rCenterPos.y = targetPos.y + targetSizeUp.y + centerSizeDown.y;

			// �Փˏ�Ԃɂ���
			bHit = true;

			if (pMove != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �ړ��ʂ�������
				pMove->y = 0.0f;
			}

			if (pUp != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// ��ɓ������Ă����Ԃ�ݒ�
				*pUp = true;
			}
		}
	}

	// �Փ˔����Ԃ�
	return bHit;
}

//============================================================
//	Z���̏Փ˔���
//============================================================
bool collision::ResponseSingleZ
(
	D3DXVECTOR3& rCenterPos,	// ����ʒu
	D3DXVECTOR3& rCenterPosOld,	// ����ߋ��ʒu
	D3DXVECTOR3 targetPos,		// ����ڕW�ʒu
	D3DXVECTOR3 centerSizeUp,	// ����T�C�Y(�E�E��E��)
	D3DXVECTOR3 centerSizeDown,	// ����T�C�Y(���E���E�O)
	D3DXVECTOR3 targetSizeUp,	// ����ڕW�T�C�Y(�E�E��E��)
	D3DXVECTOR3 targetSizeDown,	// ����ڕW�T�C�Y(���E���E�O)
	D3DXVECTOR3 *pMove,	// �ړ���
	bool *pBefore,		// �O����̔���
	bool *pAfter		// �ォ��̔���
)
{
	// �ϐ���錾
	bool bHit = false;	// �Փ˔��茋��

	// �O��̓����蔻��
	if (rCenterPos.x + centerSizeUp.x   > targetPos.x - targetSizeDown.x
	&&  rCenterPos.x - centerSizeDown.x < targetPos.x + targetSizeUp.x
	&&  rCenterPos.y + centerSizeUp.y   > targetPos.y - targetSizeDown.y
	&&  rCenterPos.y - centerSizeDown.y < targetPos.y + targetSizeUp.y)
	{ // ���E�Ə㉺�͈͓̔��̏ꍇ

		if (rCenterPos.z    + centerSizeUp.z >  targetPos.z - targetSizeDown.z
		&&  rCenterPosOld.z + centerSizeUp.z <= targetPos.z - targetSizeDown.z)
		{ // �O����̓����蔻��

			// �ʒu��␳
			rCenterPos.z = targetPos.z - targetSizeDown.z - centerSizeUp.z;

			// �Փˏ�Ԃɂ���
			bHit = true;

			if (pMove != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �ړ��ʂ�������
				pMove->z = 0.0f;
			}

			if (pBefore != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �O�ɓ������Ă����Ԃ�ݒ�
				*pBefore = true;
			}
		}
		else if (rCenterPos.z    - centerSizeDown.z <  targetPos.z + targetSizeUp.z
		     &&  rCenterPosOld.z - centerSizeDown.z >= targetPos.z + targetSizeUp.z)
		{ // �ォ��̓����蔻��

			// �ʒu��␳
			rCenterPos.z = targetPos.z + targetSizeUp.z + centerSizeDown.z;

			// �Փˏ�Ԃɂ���
			bHit = true;

			if (pMove != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// �ړ��ʂ�������
				pMove->z = 0.0f;
			}

			if (pAfter != nullptr)
			{ // �|�C���^���g�p����Ă���ꍇ

				// ��ɓ������Ă����Ԃ�ݒ�
				*pAfter = true;
			}
		}
	}

	// �Փ˔����Ԃ�
	return bHit;
}

//============================================================
//	�p���̓�������
//============================================================
bool collision::InBoxPillar
(
	D3DXVECTOR3& rCenterPos,	// ����ʒu
	D3DXVECTOR3 originPos,		// ���茴�_�ʒu
	D3DXVECTOR3 centerSizeUp,	// ����T�C�Y(�E�E��E��)
	D3DXVECTOR3 centerSizeDown,	// ����T�C�Y(���E���E�O)
	D3DXVECTOR3 originSizeUp,	// ���茴�_�T�C�Y(�E�E��E��)
	D3DXVECTOR3 originSizeDown	// ���茴�_�T�C�Y(���E���E�O)
)
{
	// �ϐ���錾
	bool bHit = false;	// ���茋��

	// ���E�̕␳
	if (useful::LimitNum(rCenterPos.x, originPos.x - originSizeDown.x + centerSizeUp.x, originPos.x + originSizeUp.x - centerSizeDown.x))
	{ // �␳���s��ꂽ�ꍇ

		// ���肵����Ԃɂ���
		bHit = true;
	}

	// �O��̕␳
	if (useful::LimitNum(rCenterPos.z, originPos.z - originSizeDown.z + centerSizeUp.z, originPos.z + originSizeUp.z - centerSizeDown.z))
	{ // �␳���s��ꂽ�ꍇ

		// ���肵����Ԃɂ���
		bHit = true;
	}

	// ���茋�ʂ�Ԃ�
	return bHit;
}

//============================================================
//	�~���̓�������
//============================================================
bool collision::InCirclePillar
(
	D3DXVECTOR3& rCenterPos,	// ����ʒu
	D3DXVECTOR3 originPos,		// ���茴�_�ʒu
	float fCenterRadius,		// ���蔼�a
	float fOriginRadius			// ���茴�_���a
)
{
	// �ϐ���錾
	float fLength = 0.0f;	// ����ʒu�Ɣ���ڕW�ʒu�̊Ԃ̋���

	// ����ʒu�Ɣ���ڕW�ʒu�̋��������߂�
	fLength = (rCenterPos.x - originPos.x) * (rCenterPos.x - originPos.x)
			+ (rCenterPos.z - originPos.z) * (rCenterPos.z - originPos.z);

	if (fLength > (fOriginRadius - fCenterRadius) * (fOriginRadius - fCenterRadius))
	{ // ����O�̏ꍇ

		// �ϐ���錾
		float fCenterRot = atan2f(rCenterPos.x - originPos.x, rCenterPos.z - originPos.z);	// ����ڕW���猩���������

		// �ʒu��␳
		rCenterPos.x = originPos.x + sinf(fCenterRot) * (fOriginRadius - fCenterRadius);
		rCenterPos.z = originPos.z + cosf(fCenterRot) * (fOriginRadius - fCenterRadius);

		// �^��Ԃ�
		return true;
	}

	// �U��Ԃ�
	return false;
}

//============================================================
//	�O�ς̍��E����
//============================================================
//	���E�����猩�č��E�ǂ���ɂ��邩�̔���Ɏg�p
//============================================================
float collision::LineOuterProduct
(
	D3DXVECTOR3 posLeft,	// ���E�������W
	D3DXVECTOR3 posRight,	// ���E���E���W
	D3DXVECTOR3 pos			// ����ʒu
)
{
	// �ϐ���錾
	D3DXVECTOR3 vecLine;	// ���E���x�N�g��
	D3DXVECTOR3 vecToPos;	// ���[�ƈʒu�̃x�N�g��

	// ���E���x�N�g�������߂�
	vecLine = posRight - posLeft;

	// ���[�ƈʒu�̃x�N�g�������߂�
	vecToPos = pos - posLeft;

	// �O�ς̌v�Z���ʂ�Ԃ�
	return (vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z);
}

//============================================================
//	�O�ς̏㉺����
//============================================================
//	���E�����猩�ď㉺�ǂ���ɂ��邩�̔���Ɏg�p
//============================================================
float collision::LineHeightOuterProduct
(
	D3DXVECTOR3 posLeft,	// ���E�������W
	D3DXVECTOR3 posRight,	// ���E���E���W
	D3DXVECTOR3 pos			// ����ʒu
)
{
	// �ϐ���錾
	D3DXVECTOR3 vecLine;	// ���E���x�N�g��
	D3DXVECTOR3 vecToPos;	// ���[�ƈʒu�̃x�N�g��

	// ���E���x�N�g�������߂�
	vecLine = posRight - posLeft;

	// ���[�ƈʒu�̃x�N�g�������߂�
	vecToPos = pos - posLeft;

	// �O�ς̌v�Z���ʂ�Ԃ�
	return (vecLine.y * vecToPos.x) - (vecLine.x * vecToPos.y);
}

//============================================================
//	�O�p���̓����蔻��
//============================================================
bool collision::TriangleOuterPillar
(
	D3DXVECTOR3 pos0,	// �O�p�̊e���_
	D3DXVECTOR3 pos1,	// �O�p�̊e���_
	D3DXVECTOR3 pos2,	// �O�p�̊e���_
	D3DXVECTOR3 pos		// ����ʒu
)
{
	if (collision::LineOuterProduct(pos0, pos1, pos) <= 0.0f
	&&  collision::LineOuterProduct(pos1, pos2, pos) <= 0.0f
	&&  collision::LineOuterProduct(pos2, pos0, pos) <= 0.0f)
	{ // ������̏ꍇ

		// �^��Ԃ�
		return true;
	}

	// �U��Ԃ�
	return false;
}

//============================================================
//	�l�p���̓����蔻��
//============================================================
bool collision::BoxOuterPillar
(
	D3DXVECTOR3 pos0,	// �l�p�̊e���_
	D3DXVECTOR3 pos1,	// �l�p�̊e���_
	D3DXVECTOR3 pos2,	// �l�p�̊e���_
	D3DXVECTOR3 pos3,	// �l�p�̊e���_
	D3DXVECTOR3 pos		// ����ʒu
)
{
	if (collision::LineOuterProduct(pos0, pos1, pos) <= 0.0f
	&&  collision::LineOuterProduct(pos1, pos2, pos) <= 0.0f
	&&  collision::LineOuterProduct(pos2, pos3, pos) <= 0.0f
	&&  collision::LineOuterProduct(pos3, pos0, pos) <= 0.0f)
	{ // ������̏ꍇ

		// �^��Ԃ�
		return true;
	}

	// �U��Ԃ�
	return false;
}