//===========================
//
// �������� [explosion.h]
// Author:TEAM_2
//
//===========================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "main.h"

//***************************
// �}�N����`
//***************************
#define MAX_EXPLOSION (128)			// �����̍ő吔
#define MAX_EXPLOSIONSIZE_X (30)	// �����̃T�C�Y
#define MAX_EXPLOSIONSIZE_Y (30)	// �����̃T�C�Y

//***************************
// �����\���̂̒�`
//***************************
typedef struct
{
	D3DXVECTOR3 pos;			// �ʒu
	D3DXVECTOR3 rot;			// �p�x
	D3DXVECTOR3 move;			// �ړ���
	D3DXMATRIX mtxWorld;		// ���[���h�}�g���b�N�X
	int nCounterAnimExplosion;	// �A�j���[�V�����J�E���^�[
	int nPatternAnimExplosion;	// �A�j���[�V�����p�^�[��
	bool bUse;					// �g�p���Ă��邩
}Explosion;

//***********************
// �v���g�^�C�v�錾
//***********************
void InitExplosion(void);			// �����̏�����
void UninitExplosion(void);			// �����̏I��
void UpdateExplosion(void);			// �����̍X�V
void DrawExplosion(void);			// �����̕`��
void SetExplosion(D3DXVECTOR3 pos);	//�����̐ݒ菈��

#endif
