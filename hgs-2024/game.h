//=============================
//
// �Q�[���S�ʏ��� [game.h]
// Author:TEAM_2
//
//============================
#ifndef _GAME_H_
#define _GAME_H_

//**********************************
// �C���N���[�h�t�@�C���錾
//**********************************
#include "main.h"

//**********************************
// �Q�[���̏�ԗ񋓌^�錾
//**********************************
typedef enum
{
	GAMESTATE_NONE = 0,		// �������Ă��Ȃ����
	GAMESTATE_NORMAL,		// �ʏ���
	GAMESTATE_END,			// �I�����
	GAMESTATE_PAUSE,		// �|�[�Y���
	GAMESTATE_SELECT,		// �Z���N�g��ʏ��
	GAMESTATE_MAX
}GAMESTATE;

//**********************************
// �v���g�^�C�v�錾
//**********************************

void InitGame(void);					// �Q�[���̏�����
void UninitGame(void);					// �Q�[���̏I��
void UpdateGame(void);					// �Q�[���̍X�V
void DrawGame(void);					// �Q�[���̕`��
void SetGamestate(GAMESTATE state);		// �Q�[���̏�Ԃ̐ݒ�
GAMESTATE GetGameState(void);			// �Q�[���̏�Ԃ̎擾
void SetEnablePause(bool bPause);		// �|�[�Y���j���[�̐ݒ�
void SetEnableSelect(bool isSelectMenu);// �Z���N�g���j���[�̐ݒ�

#endif