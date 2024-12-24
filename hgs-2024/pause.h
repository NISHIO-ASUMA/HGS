//===========================
//
// �|�[�Y���� [pause.h]
// Author:TEAM_2
//
//===========================
#ifndef _PAUSE_H_
#define _PAUSE_H_

//*****************************
// �C���N���[�h�t�@�C���錾
//*****************************
#include "main.h"

//*****************************
// �}�N����`
//*****************************
#define MAX_PAUSE_TEX (3)		// �|�[�Y��ʂ̃e�N�X�`��

//*****************************
// �|�[�Y���j���[�̎�ނ̗񋓌^
//*****************************
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,// �Q�[���ɖ߂�
	PAUSE_MENU_RETRY,       // �Q�[������蒼��
	PAUSE_MENU_QUIT,        // �^�C�g���ɖ߂�
	PAUSE_MENU_MAX
}PAUSE_MENU;

//*****************************
// �v���g�^�C�v�錾
//*****************************
void InitPause(void);		// �|�[�Y��ʂ̏�����
void UninitPause(void);		// �|�[�Y��ʂ̏I��
void UpdatePause(void);		// �|�[�Y��ʂ̍X�V
void DrawPause(void);		// �|�[�Y��ʂ̕`��

#endif