//================================
// 
// �A�C�e������ [item.h]
// Author : TEAM_2
// 
//================================
#ifndef _ITEM_H_
#define _ITEM_H_

//*********************************
// �C���N���[�h�t�@�C���錾
//*********************************
#include "main.h"

//*********************************
// ��ނ̍\���̐錾
//*********************************
typedef enum
{
	ITEMTYPE_SPRING = 0,	// �t
	ITEMTYPE_SUMMER,		// ��
	ITEMTYPE_AUTUMN,		// �H
	ITEMTYPE_WINTER,		// �~
	ITEMTYPE_FOOD1,			// �O�F�c�q
	ITEMTYPE_FOOD2,			// �X�C�J
	ITEMTYPE_FOOD3,			// �T�c�}�C��
	ITEMTYPE_FOOD4,			// �݂���
	ITEMTYPE_MAX
}ITEMTYPE;

//*********************************
// ���f���̎�ޏ��
//*********************************
static const char* ITEM_MODEL[ITEMTYPE_MAX] =
{

};

//*********************************
// ���f���ݒ���
//*********************************
typedef struct
{
	LPD3DXMESH pMesh;					   // ���b�V���̃|�C���^
	LPD3DXBUFFER pBuffMat;				   // �}�e���A���̃|�C���^
	DWORD dwNumMat;					       // �}�e���A����
	LPDIRECT3DTEXTURE9 pTexture[ITEMTYPE_MAX]; // �e�N�X�`���̃|�C���^
}ItemModel;

//*********************************
// �A�C�e���̍\���̐錾
//*********************************
typedef struct
{
	D3DXVECTOR3 pos; // ���W
	D3DXVECTOR3 rot; // �p�x
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	ITEMTYPE Type;	 // ���
	ItemModel aModel[ITEMTYPE_MAX]; // ���f�����
	bool bUse;       // �g�p����
	int nIdxshadow;  // �e
	int nLife;		 // �̗�
}Item;

//*********************************
// �v���g�^�C�v�錾
//*********************************
void InitItem();				// ����������
void UninitItem();				// �I������
void UpdateItem();				// �X�V����
void DrawItem();				// �`�揈��
void SetItem(D3DXVECTOR3 pos, ITEMTYPE Type);	// �ݒ菈��
void HitItem(int nCnt, int nDamage); // �q�b�g����
int GetResultNumber();			// ���U���g�ԍ�
Item* GetItem();				// �擾����

#endif