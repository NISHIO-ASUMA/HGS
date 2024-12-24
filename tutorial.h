//=================================
//
// �`���[�g���A������ [tutorial.h]
// Author: TEAM_2
//
//=================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "main.h"

//********************************
// �`���[�g���A���̏�ԗ񋓌^�錾
//********************************
typedef enum
{
	TUTORIALSTATE_NORMAL = 0,	// �ʏ���
	TUTORIALSTATE_FLASH,		// �_�ŏ��
	TUTORIALSTATE_MAX			
}TUTORIALSTATE;

//*************************************
// �`���[�g���A���̃e�N�X�`���񋓌^�錾
//*************************************
typedef enum
{
	TUTORIALTEX_ONE = 0,
	TUTORIALTEX_TWO,
	TUTORIAL_MAX
}TUTORIALTEX;

static const char* TUTORIAL_TEXTURE[TUTORIAL_MAX] =
{
	"data\\TEXTURE\\reef.jpeg",
	"data\\TEXTURE\\reef.jpeg",
};
//****************************
// �`���[�g���A���\���̐錾
//****************************
typedef struct
{
	D3DXVECTOR3 pos;			// ���W
	int nType;					// ���
	float fWidth;				// ����
	float fHeight;				// ����
	TUTORIALSTATE state;		// ��ԕϐ�
}Tutorial;

//**********************
// �v���g�^�C�v�錾
//**********************
void InitTutorial(void);		// �`���[�g���A���̏�����
void UninitTutorial(void);		// �`���[�g���A���̏I��
void UpdateTutorial(void);		// �`���[�g���A���̍X�V
void DrawTutorial(void);		// �`���[�g���A���̕`��
void SetTutorial(D3DXVECTOR3 pos); // �`���[�g���A���̐ݒ�
#endif