//=======================================
//
//���f������[model.h]
//Author : TANEKAWA RIKU
//
//=======================================
#ifndef _MODEL_H_//���̃}�N����`������Ă��Ȃ�������
#define _MODEL_H_//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

#define MAX_MODEL (2)	//	���f���̎g����
#define MAX_TEXTUREMODEL (128)

//�ǂ̎��
typedef enum
{
	WALLTYPE_NORMAL=0,
	WALLTYPE_MINI,
	WALLTYPE_DOOR,
	WALLTYPE_EXIT,
	WALLTYPE_ROOM,
	WALLTYPE_ENTERDOOR,

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

	"data/MODEL/wall.x",				//	���̕Ǎ�
	"data/MODEL/wall.x",				//	���̕ǉE
	//"data/MODEL/passagewall.x",			//	���̒ʘH�Ǎ�
	//"data/MODEL/passagewall.x",			//	���̒ʘH�Ǎ�
	//"data/MODEL/wall01.x",				//	�����̎�O�Ǎ�
	//"data/MODEL/wall01.x",				//	�����̎�O�ǉE
	//"data/MODEL/wall01.x",				//	�����̎�O�ǐ^��
	//"data/MODEL/rightwall001.x",		//	�����̉E����
	//"data/MODEL/rightwall001.x",		//	�����̉E��O��
	//"data/MODEL/wall2.x",				//	�ʘH�̎�O��
	//"data/MODEL/wall3.x",				//	�ʘH�̉���
	//"data/MODEL/rightwall001.x",		//	�����̍�����
	//"data/MODEL/rightwall001.x",		//	�����̍���O��
	//"data/MODEL/wall2.x",				//	�ʘH�̎�O��
	//"data/MODEL/wall3.x",				//	�ʘH�̉���
	//"data/MODEL/door1.x",				//	�o���h�A
	//"data/MODEL/centerwall.x",			//	�^�񒆂̍�
	//"data/MODEL/centerwall.x",			//	�^�񒆂̉E
	//"data/MODEL/centerwall2.x",			//	�^�񒆂̉�
	//"data/MODEL/centerwall2.x",			//	�^�񒆂̎�O
	//"data/MODEL/roomwall01.x",			//	���̕����̎�O��
	//"data/MODEL/roomwall01.x",			//	���̕����̎�O�E
	//"data/MODEL/roomwallside.x",		//	���̕����̍�
	//"data/MODEL/roomwallside.x",		//	���̕����̉E
	//"data/MODEL/roomwallOku.x",			//	���̕����̉���
	//"data/MODEL/exit.x",				//	�o���h�A
	//"data/MODEL/roomdoor.x",			//	���̕����̃h�A
	//"data/MODEL/exit.x",				//	�����h�A

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

