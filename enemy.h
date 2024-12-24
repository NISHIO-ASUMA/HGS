//=================================
//
// �G�̏��� [enemy.h]
// Author: TEAM_2
//
//=================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "main.h"
#include "model.h"

//****************************
// �}�N����`
//****************************
#define MAX_ENEMY (100)			// �G�̏o���ő吔
#define HALFSIZE (0.5f)			// �����̃T�C�Y���̒l

//********************************
// �G�̏�ԗ񋓌^�錾
//********************************
typedef enum
{
	ENEMYSTATE_NORMAL = 0,	// �ʏ���
	ENEMYSTATE_DAMAGE,		// �_���[�W���
	ENEMYSTATE_MAX
}ENEMYSTATE;

//*************************************
// �G�̎�ނ̗񋓌^�錾
//*************************************
typedef enum
{
	ENEMYTYPE_FIRE = 0,	// 1�ڂ̓G
	ENEMYTYPE_NOFIRE,	// 2�ڂ̓G
	ENEMYTYPE_PURA,		// 3�ڂ̓G
	ENEMYTYPE_KAN,		// 4�ڂ̓G
	ENEMYTYPE_RECYCLE,	// 5�ڂ̓G
	ENEMYTYPE_MAX
}ENEMYTYPE;

//*************************************
// �G�̃��f���̗񋓌^�錾
// TODO : �����̃��f���͊e���ύX�\
//*************************************
static const char* ENEMY_MODEL[ENEMYTYPE_MAX] =
{
	"data\\MODEL\\Enemy001.x",	// 1
	"data\\MODEL\\Enemy002.x",	// 2
	"data\\MODEL\\Enemy003.x",	// 3
	"data\\MODEL\\Enemy004.x",	// 4
	"data\\MODEL\\Enemy005.x",	// 5
};

//****************************
// �G�̃��f���̍\���̐錾
//****************************
typedef struct
{
	LPD3DXMESH pMeshEnemy;					   // ���b�V���̃|�C���^
	LPD3DXBUFFER pBuffMatEnemy;				   // �}�e���A���̃|�C���^
	DWORD dwNumMatEnemy;					   // �}�e���A����
	LPDIRECT3DTEXTURE9 pTexture[ENEMYTYPE_MAX];// �e�N�X�`���̃|�C���^
	D3DCOLORVALUE DiffUse, FirstDiffUse;	   // ���f���̃J���[
}EnemyModel;

//****************************
// �G�̍\���̐錾
//****************************
typedef struct
{
	EnemyModel aModel[ENEMYTYPE_MAX];	// ���f�����
	D3DXVECTOR3 pos;					// ���W
	D3DXVECTOR3 posOld;					// �ߋ����W
	D3DXVECTOR3 rot;					// �p�x
	D3DXVECTOR3 move;					// �ړ���
	D3DXMATRIX  mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3 Vtxmax, Vtxmin;			// ���_���
	D3DXVECTOR3 size;					// �T�C�Y
	ENEMYSTATE State;					// ���
	ENEMYTYPE nType;					// ���
	int nCntState;						// ��ԊǗ��J�E���^�[
	int nLife;							// �̗�
	int nIdxEnemy;						// �e
	bool bUse;							// �g�p���
}Enemy;

//**********************
// �v���g�^�C�v�錾
//**********************
void InitEnemy(void);							// �G�̏�����
void UninitEnemy(void);							// �G�̏I��
void UpdateEnemy(void);							// �G�̍X�V
void DrawEnemy(void);							// �G�̕`��
void SetEnemy(ENEMYTYPE nType, D3DXVECTOR3 pos);// �G�̐ݒ�
void HitEnemy(int nCntEnemy, int nDamage);		// �G�̓����蔻��
Enemy* GetEnemy();								// �G�̎擾
int GetNumEnemy();								// �G�̑����̎擾

#endif
