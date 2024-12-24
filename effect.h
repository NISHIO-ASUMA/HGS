//==========================
//
// �G�t�F�N�g���� [effect.h]
// Author: TEAM_2
//
//==========================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "main.h"

//***************************
// �}�N����`
//***************************
#define MAX_EFFECT (16)    // �ő吔
#define MAX_SIZE (10.0f)

//***************************
// �񋓌^�錾
//***************************
typedef enum
{
	EFECTTYPE_PLAYER = 0,	// �v���C���[
	EFFECTTYPE_BULLET,		// �e
	EFFECTTYPE_ENEMY,		// �G
	EFFECTTYPE_MAX
}EFFECTTYPE;

//***************************
// �\���̐錾
//***************************
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	D3DXVECTOR3 move;		// �ړ���
	D3DXMATRIX  mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXCOLOR col;			// �J���[
	D3DXVECTOR3 Scall;		// �傫��
	float fRadius;			// ���a
	bool bUse;				// �g�p���
	int nIdxeffect;			// �C���f�b�N�X
	int nLife;				// �̗�
	EFFECTTYPE Type;		// ���
}Effect;

//**********************
// �v���g�^�C�v�錾
//**********************
void InitEffect(void);				// �G�t�F�N�g����������
void UninitEffect(void);			// �G�t�F�N�g�I������
void UpdateEffect(void);			// �G�t�F�N�g�X�V����
void DrawEffect(void);				// �G�t�F�N�g�`�揈��
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXCOLOR col,D3DXVECTOR3 Scall,int nLife);    // �G�t�F�N�g�ݒ菈��
#endif 


