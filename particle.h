//================================
//
// �p�[�e�B�N������ [particle.h]
// Author: TEAM_2
//
//================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "main.h"

//***************************
// �񋓌^�錾
//***************************
typedef enum
{
	PARTICLETYPE_PLAYER = 0,	// �v���C���[
	PARTICLETYPE_BULLET,		// �e
	PARTICLETYPE_ENEMY,			// �G
	PARTICLETYPE_MAX
}PARTICLETYPE;

//***************************
// �\���̐錾
//***************************
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXCOLOR col;			// �J���[
	bool bUse;				// �g�p���
	int nType;				// ���
	int nLife;				// �̗�
}Particle;

//**********************
// �v���g�^�C�v�錾
//**********************
void InitParticle(void);				// �p�[�e�B�N������������
void UpdateParticle(void);				// �p�[�e�B�N���X�V����
void SetParticle(D3DXVECTOR3 pos,D3DXCOLOR col, int nLife, PARTICLETYPE type);    // �p�[�e�B�N���ݒ菈��

#endif 


