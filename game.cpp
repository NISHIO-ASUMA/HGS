//===============================
//
// �Q�[���S�ʏ��� [game.cpp]
// Author:TEAM_2
// 
//===============================

//**********************************
// �C���N���[�h�t�@�C���錾
//**********************************
#include "game.h"
#include "Player.h"
#include "input.h"
#include "fade.h"
#include "title.h"
#include "effect.h"
#include "pause.h"
#include "particle.h"
#include "camera.h"
#include "Timer.h"
#include "shadow.h"
#include "block.h"
#include "light.h"
#include "meshfield.h"
#include "meshwall.h"
#include "meshfan.h"
#include "enemy.h"
#include "score.h"
#include "rankscore.h"
#include "sound.h"

//**********************************
// �O���[�o���ϐ��錾
//**********************************
GAMESTATE g_gameState = GAMESTATE_NONE;		// �Q�[�����
int g_nCounterGameState = 0;				// ��ԊǗ��J�E���^�[
bool g_bPause = false;						// �|�[�Y�����ǂ���
bool isSelect = false;						// �Z���N�g��ʂ��ǂ���

//========================
// �Q�[����ʂ̏���������
//========================
void InitGame(void)
{
	// �J�����̏�����
	InitCamera();

	// ���b�V���t�B�[���h�̏�����
	InitMeshField();

	// ���b�V���̃V�����_�[�`�̏�����
	InitMeshWall();

	// ���b�V���h�[���̏�����
	InitmeshFan();

	// ���C�g�̏�����
	InitLight();

	// �e�̏�����
	InitShadow();

	// �G�t�F�N�g�̏�����
	InitEffect();			

	// �p�[�e�B�N���̏�����
	InitParticle();			

	// �v���C���[�̏�����
	InitPlayer();

	// �|�[�Y��ʂ̏�����
	InitPause();			

	// �^�C�}�[�̏�����
	InitTimer();

	// �G�̏�����
	InitEnemy();

	// �u���b�N�̏�����
	InitBlock();

	// �X�R�A�̏�����
	InitScore();

	g_gameState = GAMESTATE_NORMAL;	//�@�ʏ��Ԃ̐ݒ�
	g_nCounterGameState = 0;		//	�J�E���^�[�̏�����
	g_bPause = false;				//	�|�[�Y��ʂ̏�����(�|�[�Y����)

	// ���y���Đ�
	PlaySound(SOUND_LABLE_GAMEBGM);
}
//===================
//�Q�[���̏I��
//===================
void UninitGame(void)
{
	// ���y���~�߂�
	StopSound();

	// �X�R�A�̕ۑ�
	SaveScore();

	// �J�����̏I��
	UninitCamera();

	// ���C�g�̏I��
	UninitLight();

	// �e�̏I��
	UninitShadow();

	// ���b�V���t�B�[���h�̏I��
	UninitMeshField();

	 // ���b�V���̃V�����_�[�`�̏I��
	UninitMeshWall();

	 // ���b�V���h�[���̏I��
	UninitmeshFan();

	// �u���b�N�̏I��
	UninitBlock();

	// �G�̏I��
	UninitEnemy();

	// �v���C���[�̏I��
	UninitPlayer();

	// �v���C���[�̏I��
	UninitPlayer();			

	// �G�t�F�N�g�̏I��
	UninitEffect();			

	// �|�[�Y��ʂ̏I��
	UninitPause();			

	// �^�C�}�[�̏I��
	UninitTimer();

	// �X�R�A�̏I��
	UninitScore();
}
//===================
// �Q�[���̍X�V
//===================
void UpdateGame(void)
{
	if (KeyboardTrigger(DIK_RETURN))
	{
		// ��ʑJ��
		SetFade(MODE_RESULT);
	}

	// ���[�h�̎擾
	MODE nMode = GetMode();

	// �v���C���[�̎擾
	PLAYER* pPlayer = GetPlayer();

	// �G�̎擾
	int nNum = GetNumEnemy();

	// �^�C�}�[���擾
	int nTime = GetTimer();

	if ( (nTime <= 0 || pPlayer->bDisp == false) && g_gameState != GAMESTATE_NONE)
	{
		g_gameState = GAMESTATE_END;  //�I�����
	}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL: // �ʏ���
		break;

	case GAMESTATE_END:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			// �J�E���^�[��������
			g_nCounterGameState = 0;

			// 1�b�o��
			g_gameState = GAMESTATE_NONE;		// �������Ă��Ȃ����

			// ��ʑJ��
			SetFade(MODE_RESULT);

			//�ǂݍ���
			ResetRanking();

			//�����L���O�̐ݒ�
			SetRanking(GetScore());
		}
		break;

	case GAMESTATE_PAUSE:
		//�|�[�Y��
		//�|�[�Y�̍X�V����
		UpdatePause();
		break;

	}

	// �|�[�Y���
	if (nMode == MODE_GAME)
	{
		if (KeyboardTrigger(DIK_P) == true || JoypadTrigger(JOYKEY_START))
		{// p�������ꂽ or start�{�^��
			// �L��������������
			g_bPause = g_bPause ? false : true;

			// ���y�Đ�
			PlaySound(SOUND_LABLE_PAUSEMENU);
		}
	}

	if (g_bPause == true)
	{// g_bPause��true�̎�
		g_gameState = GAMESTATE_PAUSE;
	}
	else if (!g_bPause && g_gameState != GAMESTATE_SELECT)
	{
		g_gameState = GAMESTATE_NORMAL;
	}

	if (g_gameState == GAMESTATE_NORMAL)
	{//�|�[�Y���Ŗ������
		
		// �J�����̍X�V
		UpdateCamera();

		// �u���b�N�̍X�V
		UpdateBlock();

		// ���C�g�̍X�V
		UpdateLight();

		// ���b�V���t�B�[���h�̍X�V
		UpdateMeshField();

		// ���b�V���̃V�����_�[�`�̍X�V
		UpdateMeshWall();

		// ���b�V���h�[���̍X�V
		UpdatemeshFan();

		// �e�̍X�V
		UpdateShadow();

		// �G�̍X�V
		UpdateEnemy();

		// �v���C���[�̍X�V
		UpdatePlayer();

		// �G�t�F�N�g�̍X�V
		UpdateEffect();		

		// �p�[�e�B�N���̍X�V
		UpdateParticle();	

		// �^�C�}�[�̍X�V
		UpdateTimer();

		// �X�R�A�̍X�V
		UpdateScore();
	}
}
//===================
//�Q�[����ʂ̕`�揈��
//===================
void DrawGame(void)
{
	// �J�����̃Z�b�g
	SetCamera();

	// ���b�V���t�B�[���h�̕`��
	DrawMeshField();

	// ���b�V���h�[���̕`��
	DrawmeshFan();

	// ���b�V���̃V�����_�[�`�̕`��
	DrawMeshWall();

	// �e�̕`��
	DrawShadow();

	// �u���b�N�̕`��
	DrawBlock();

	// �G�̕`��
	DrawEnemy();

	// �v���C���[�̕`��
	DrawPlayer();

	// �G�t�F�N�g�̕`��
	DrawEffect();

	//�^�C�}�[
	DrawTimer();

	// �X�R�A�̕`��
	DrawScore();

	if (g_gameState == GAMESTATE_PAUSE)
	{
		//�|�[�Y��
		//�|�[�Y�̕`��
		DrawPause();
	}

}
//=====================
// �|�[�Y�̗L�������ݒ�
//=====================
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}
//=====================
// �Z���N�g�̗L�������ݒ�
//=====================
void SetEnableSelect(bool isSelectMenu)
{
	isSelect = isSelectMenu;
}
//=====================
// �Q�[���̏�Ԑݒ菈��
//=====================
void SetGamestate(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}
//=====================
// �Q�[���̏�Ԏ擾����
//=====================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}