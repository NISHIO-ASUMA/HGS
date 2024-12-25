//=======================================
//
//���f������[model.h]
//Author : TANEKAWA RIKU
//
//=======================================
#ifndef _MODEL_H_//���̃}�N����`������Ă��Ȃ�������
#define _MODEL_H_//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

#define MAX_MODEL (25)	//	���f���̎g����
#define MAX_TEXTUREMODEL (128)

//�ǂ̎��
typedef enum
{
	WALLTYPE_OKU=0,
	WALLTYPE_HIDARI,
	WALLTYPE_TEMAE,
	WALLTYPE_MIGI,
	WALLTYPE_DOOR1,
	WALLTYPE_DOOR2,
	WALLTYPE_DOOR3,
	WALLTYPE_DOOR4,

	WALLTYPE_GOALOKU,
	WALLTYPE_GOALTEMAE,
	WALLTYPE_GOALMIGI,

	WALLTYPE_CLEAR,
	WALLTYPE_MAX
}WALLTYPE;

//���f���\����
typedef struct
{
	D3DXVECTOR3 pos;					//	�ʒu(�I�t�Z�b�g)
	LPDIRECT3DTEXTURE9 apTexture[MAX_TEXTUREMODEL];	//	�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 move;					//�ړ���
	D3DXVECTOR3 rot;					//	����
	D3DXVECTOR3 vtxMin;
	D3DXVECTOR3 vtxMax;
	D3DXVECTOR3 size;
	int nType;
	int Index;
	bool bUse;
	LPD3DXMESH pMesh;			
	LPD3DXBUFFER pBuffMat;				//	�}�e���A���ւ̃|�C���^
	DWORD dwNumMat;						//	�}�e���A����
	int nIdxModelParent;				//	�e���f���̃C���f�b�N�X
	D3DXMATRIX mtxWorld;				//	���[���h�}�g���b�N�X
	D3DXVECTOR3 Offpos;
	D3DXVECTOR3 Offrot;
	bool bScoreAdded;					// �X�R�A���Z�ς݂��ǂ���
	bool bSoundPlayed;					// �����Đ��ς݂��ǂ���
}Model;

static const char* MODEL[MAX_MODEL] =
{

	"data/MODEL/wall_oku.x",		//	���[��1�̉��̕�
	"data/MODEL/wall_hidari.x",		//	���[��1�̍���
	"data/MODEL/wall_temae.x",		//	���[��1�̎�O��
	"data/MODEL/wall_migi.x",		//	���[��1�̉E�ǉ�
	"data/MODEL/wall_migi.x",		//	���[��1�̉E�ǎ�O

	"data/MODEL/wall_oku.x",		//	���[��2�̉��̕�
	"data/MODEL/wall_temae.x",		//	���[��2�̎�O��
	"data/MODEL/wall_migi.x",		//	���[��2�̉E�ǉ�
	"data/MODEL/wall_migi.x",		//	���[��2�̉E�ǎ�O

	"data/MODEL/wall_oku.x",		//	���[��3�̉��̕�
	"data/MODEL/wall_temae.x",		//	���[��3�̎�O��
	"data/MODEL/wall_migi.x",		//	���[��3�̉E�ǉ�
	"data/MODEL/wall_migi.x",		//	���[��3�̉E�ǎ�O

	"data/MODEL/wall_oku.x",		//	���[��4�̉��̕�
	"data/MODEL/wall_temae.x",		//	���[��4�̎�O��
	"data/MODEL/wall_migi.x",		//	���[��4�̉E�ǉ�
	"data/MODEL/wall_migi.x",		//	���[��4�̉E�ǎ�O

	"data/MODEL/roomdoor.x",		//	���[��1�̃h�A
	"data/MODEL/roomdoor.x",		//	���[��2�̃h�A
	"data/MODEL/roomdoor.x",		//	���[��3�̃h�A
	"data/MODEL/roomdoor.x",		//	���[��4�̃h�A

	"data/MODEL/wall_goal_oku.x",	//	�S�[���̉���
	"data/MODEL/wall_goal_temae.x",	//	�S�[���̎�O��
	"data/MODEL/wall_goal_migi.x",	//	�S�[���̉E��

	"data/MODEL/present_box.x",		//	�S�[���̃v���[���g

};

//�v���g�^�C�v�錾
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
void SetModel(D3DXVECTOR3 pos, int nType);
void CollisionBlock(void);//�����蔻��
bool GetTask0(void);
bool GetTask(void);
bool GetTask2(void);
bool GetTask3(void);
bool GetTask4(void);
bool GetTask5(void);
bool GetExit(void);

#endif

