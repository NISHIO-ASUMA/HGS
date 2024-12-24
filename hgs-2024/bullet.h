//==========================
//
// �o���b�h���� [bullet.h]
// Author: TEAM_2
//
//==========================
#ifndef _BULLET_H_
#define _BULLET_H_

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "main.h"

//***************************
// �}�N����`
//***************************
#define MAX_BULLET (128)    // �ő吔

//***************************
// �񋓌^�錾
//***************************
typedef enum
{
	BULLETTYPE_PLAYER = 0,	// �v���C���[
	BULLETTYPE_ENEMY,		// �G
	BULLETTYPE_MAX
}BULLETTYPE;

//***************************
// �\���̐錾
//***************************
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 posOld;		// �ߋ��̈ʒu
	D3DXVECTOR3 rot;		// ����
	D3DXVECTOR3 move;		// �ړ���
	D3DXVECTOR3 dir;		// �����x�N�g��
	D3DXMATRIX  mtxWorld;	// ���[���h�}�g���b�N�X
	bool bUse;				// �g�p���
	int nIdxBullet;			// �C���f�b�N�X
	int nLife;				// �̗�
}Bullet;

//**********************
// �v���g�^�C�v�錾
//**********************
void InitBullet(void);		// �o���b�h����������
void UninitBullet(void);	// �o���b�h�I������
void UpdateBullet(void);	// �o���b�h�X�V����
void DrawBullet(void);		// �o���b�h�`�揈��
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 dir, int nLife, D3DXVECTOR3 move); // �o���b�h�ݒ菈��(�����ɂ���Ĉ����ǉ�)

#endif 


