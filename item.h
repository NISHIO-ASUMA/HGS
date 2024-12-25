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
	LPD3DXMESH pMeshEnemy;					   // ���b�V���̃|�C���^
	LPD3DXBUFFER pBuffMatEnemy;				   // �}�e���A���̃|�C���^
	DWORD dwNumMatEnemy;					   // �}�e���A����
	LPDIRECT3DTEXTURE9 pTexture[ITEMTYPE_MAX]; // �e�N�X�`���̃|�C���^
}ItemModel;

//*********************************
// �A�C�e���̍\���̐錾
//*********************************
typedef struct
{
	D3DXVECTOR3 pos; // ���W
	D3DXVECTOR3 rot; // �p�x
	bool bUse;       // �g�p����
	ITEMTYPE Type;	 // ���
	ItemModel aModel[ITEMTYPE_MAX]; // ���f�����
}Item;

//*********************************
// �v���g�^�C�v�錾
//*********************************
void InitItem();				// ����������
void UninitItem();				// �I������
void UpdateItem();				// �X�V����
void DrawItem();				// �`�揈��
void SetItem(D3DXVECTOR3 pos, ITEMTYPE Type);	// �ݒ菈��
void LoadItem();				// �ǂݍ���

#endif