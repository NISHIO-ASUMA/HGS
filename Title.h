//=================================
//
// �^�C�g������ [title.h]
// Author: TEAM_2
//
//=================================
#ifndef _TITLE_H_
#define _TITLE_H_

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "main.h"
#include "input.h"
#include "fade.h"

//********************************
// �^�C�g���̏�ԗ񋓌^�錾
//********************************
typedef enum
{
	TITLESTATE_NORMAL = 0,	// �ʏ���
	TITLESTATE_FLASH,		// �_�ŏ��
	TITLESTATE_MAX
}TITLESTATE;

//*************************************
// �^�C�g���̃e�N�X�`���񋓌^�錾
//*************************************
typedef enum
{
	TITLE_FIRST = 0,					//1�ڂ̃^�C�g��
	TITLE_SECOND,						//2�ڂ̃^�C�g��
	TITLE_MAX
}TITLE;

static const char* TITLE_TEXTURE[TITLE_MAX] =
{
	"data\\TEXTURE\\tutorial101.png",
	"data\\TEXTURE\\Gamestart.png",
};
//****************************
// �^�C�g���\���̐錾
//****************************
typedef struct
{
	D3DXVECTOR3 pos;			// ���W
	int nType;					// ���
	float fWidth;				// ����
	float fHeight;				// ����
	TITLESTATE state;			// ��ԕϐ�
	bool bUse;					// �g�p���
}Title;

//**********************
// �v���g�^�C�v�錾
//**********************
void InitTitle(void);						// �^�C�g���̏�����
void UninitTitle(void);						// �^�C�g���̏I��
void UpdateTitle(void);						// �^�C�g���̍X�V
void DrawTitle(void);						// �^�C�g���̕`��
#endif