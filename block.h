//==========================
//
// �u���b�N���� [block.h]
// Author: TEAM_2
//
//==========================
#ifndef _BLOCK_H_
#define _BLOCK_H_

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "main.h"

//***************************
// �u���b�N�̎�ނ̗񋓌^�錾
//***************************
typedef enum
{
	BLOCKTYPE_BOARD = 0,	// �Ŕ^�C�v
	BLOCKTYPE_BOARD2,		// �Ŕ^�C�v2
	BLOCKTYPE_BOARD3,		// �Ŕ^�C�v2
	BLOCKTYPE_MAX
}BLOCKTYPE;

//***************************
// �u���b�N��X�t�@�C���̐錾
//***************************
static const char* BLOCK_FILE[BLOCKTYPE_MAX] =
{
	"data\\MODEL\\kanban.x",	// �Ŕ�1
	"data\\MODEL\\kanban2.x",	// �Ŕ�2
	"data\\MODEL\\kanban3.x",	// �Ŕ�3
};

//***************************
// �\���̐錾
//***************************
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 Vtxmax;		// �ő�l��ێ�����ϐ�
	D3DXVECTOR3 Vtxmin;		// �ŏ��l��ێ�����ϐ�
	D3DXVECTOR3 size;		// �傫��
	LPD3DXMESH pMesh;		// ���b�V���̃|�C���^
	LPD3DXBUFFER pBuffMat;	// �}�e���A���̃|�C���^
	DWORD dwNumMat;			// �}�e���A����
	bool bUse;				// �g�p����
	BLOCKTYPE nType;		// ���
	D3DXVECTOR3 Scal;		// �傫��
	LPDIRECT3DTEXTURE9 pTexture[10];	// �e�N�X�`���̃|�C���^
	int nidxshadow;			// �e�ݒ�p
}Block;

//**********************
// �v���g�^�C�v�錾
//**********************
void InitBlock(void);		// �u���b�N����������
void UninitBlock(void);		// �u���b�N�I������
void UpdateBlock(void);		// �u���b�N�X�V����
void DrawBlock(void);		// �u���b�N�`�揈��
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot, BLOCKTYPE nType);	// �u���b�N�̐ݒ�
//void CollisionBlock(void);	// �����蔻��֐�
Block* GetBlock();

#endif // !_BLOCK_H_