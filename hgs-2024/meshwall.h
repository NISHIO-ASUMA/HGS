//======================================
//
// ���b�V���̕ǂ̏��� [mashwall.h]
// Author: TEAM_2
//
//======================================
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "main.h"

//***************************
// �}�N����`
//***************************
#define XVTX (30)	// X�̒l
#define ZVTX (1)	// Z�̒l

#define ALLVTX ((XVTX + 1) * (ZVTX + 1))	// ���_��
#define NUMPOLYGON (((XVTX * ZVTX) * 2)) + (4 * (ZVTX - 1))	// �|���S����
#define INDEXBUFF (NUMPOLYGON + 2)		// �C���f�b�N�X�o�b�t�@��

#define MAX_WALLX (300.0f)	// �t�B�[���h��X
#define MAX_WALLZ (300.0f)	// �t�B�[���h��Z

//***************************
// �\���̐錾
//***************************
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 Vtxpos[XVTX];
	D3DXVECTOR3 rot;		// ����
	D3DXMATRIX  mtxWorld;	// ���[���h�}�g���b�N�X
}MeshWall;

//**********************
// �v���g�^�C�v�錾
//**********************
void InitMeshWall(void);		// ���b�V���̕Ǐ���������
void UninitMeshWall(void);		// ���b�V���̕ǏI������
void UpdateMeshWall(void);		// ���b�V���̕ǍX�V����
void DrawMeshWall(void);		// ���b�V���̕Ǖ`�揈��
void CollisionMeshWall();		// �����蔻��
void CollisionEnemyToWall(int nCnt);// �G�Ƃ̔���

#endif // !_MESHWALL_H_
