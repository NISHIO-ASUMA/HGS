//================================
//
// �r���{�[�h���� [billboard.h]
// Author: TEAM_2
//
//================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "main.h"

//***************************
// �}�N����`
//***************************
#define MAX_BILLBOARD (24)    // �ő吔

//*****************************
// �r���{�[�h�̎�ނ̗񋓌^�錾
//*****************************
typedef enum
{
	BILLBOARDTYPE_SPRING = 0,
	BILLBOARDTYPE_SUMMER,
	BILLBOARDTYPE_AUTUMN,
	BILLBOARDTYPE_WINTER,

	BILLBOARDTYPE_SHOP,
	BILLBOARDTYPE_PARK,
	BILLBOARDTYPE_SCHOOL,

	BILLBOARDTYPE_FOOD1,
	BILLBOARDTYPE_FOOD2,
	BILLBOARDTYPE_FOOD3,
	BILLBOARDTYPE_FOOD4,

	BILLBOARDTYPE_MAX
}BILLBOARDTYPE;

//************************************
// �r���{�[�h�̃e�N�X�`���̗񋓌^�錾
//************************************
static const char* BILLBOARD_TEXTURE[BILLBOARDTYPE_MAX] = 
{
	"data\\TEXTURE\\00_Spring.png",
	"data\\TEXTURE\\01_Summer.png",
	"data\\TEXTURE\\02_Autumn.png",
	"data\\TEXTURE\\03_Winter.png",

	"data\\TEXTURE\\04_Shop.png",
	"data\\TEXTURE\\05_Park.png",
	"data\\TEXTURE\\06_School.png",

};

//***************************
// �\���̐錾
//***************************
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	D3DXVECTOR3 move;		// �ړ���
	D3DXVECTOR3 dir;		// �����x�N�g��
	D3DXMATRIX  mtxWorld;	// ���[���h�}�g���b�N�X
	bool bUse;				// �g�p����
	int nIdxshadow;			// �e
	BILLBOARDTYPE Type;		// ���
}Billboard;

//**********************
// �v���g�^�C�v�錾
//**********************
void InitBillboard(void);		// �r���{�[�h����������
void UninitBillboard(void);		// �r���{�[�h�I������
void UpdateBillboard(void);		// �r���{�[�h�X�V����
void DrawBillboard(void);		// �r���{�[�h�`�揈��
void SetBillboard(D3DXVECTOR3 pos, BILLBOARDTYPE Type, D3DXVECTOR3 rot); // �r���{�[�h�ݒ菈��(�����ɂ���Ĉ����ǉ�)
#endif 

