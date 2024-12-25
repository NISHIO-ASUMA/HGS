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
#include "bullet.h"

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
	//���f���̏���������
	InitModel();


	//���f��
	SetModel(D3DXVECTOR3(-220.0f, 0.0f, 385.0f), WALLTYPE_OKU);		//	���[��1�̉���
	SetModel(D3DXVECTOR3(-560.0f, 0.0f, 60.0f), WALLTYPE_HIDARI);	//	���[��1�̍���
	SetModel(D3DXVECTOR3(-220.0f, 0.0f, -305.0f), WALLTYPE_TEMAE);	//	���[��1�̎�O��
	SetModel(D3DXVECTOR3(120.0f, 0.0f, 230.0f), WALLTYPE_MIGI);		//	���[��1�̉E�ǉ�
	SetModel(D3DXVECTOR3(120.0f, 0.0f, -150.0f), WALLTYPE_MIGI);	//	���[��1�̉E�ǎ�O

	SetModel(D3DXVECTOR3(460.0f, 0.0f, 385.0f), WALLTYPE_OKU);		//	���[��2�̉���
	SetModel(D3DXVECTOR3(460.0f, 0.0f, -305.0f), WALLTYPE_TEMAE);	//	���[��2�̎�O��
	SetModel(D3DXVECTOR3(800.0f, 0.0f, 230.0f), WALLTYPE_MIGI);		//	���[��2�̉E�ǉ�
	SetModel(D3DXVECTOR3(800.0f, 0.0f, -150.0f), WALLTYPE_MIGI);	//	���[��2�̉E�ǎ�O

	SetModel(D3DXVECTOR3(1140.0f, 0.0f, 385.0f), WALLTYPE_OKU);		//	���[��3�̉���
	SetModel(D3DXVECTOR3(1140.0f, 0.0f, -305.0f), WALLTYPE_TEMAE);	//	���[��3�̎�O��
	SetModel(D3DXVECTOR3(1480.0f, 0.0f, 230.0f), WALLTYPE_MIGI);	//	���[��3�̉E�ǉ�
	SetModel(D3DXVECTOR3(1480.0f, 0.0f, -150.0f), WALLTYPE_MIGI);	//	���[��3�̉E�ǎ�O

	SetModel(D3DXVECTOR3(1820.0f, 0.0f, 385.0f), WALLTYPE_OKU);		//	���[��4�̉���
	SetModel(D3DXVECTOR3(1820.0f, 0.0f, -305.0f), WALLTYPE_TEMAE);	//	���[��4�̎�O��
	SetModel(D3DXVECTOR3(2160.0f, 0.0f, 230.0f), WALLTYPE_MIGI);	//	���[��4�̉E�ǉ�
	SetModel(D3DXVECTOR3(2160.0f, 0.0f, -150.0f), WALLTYPE_MIGI);	//	���[��4�̉E�ǎ�O

	SetModel(D3DXVECTOR3(120.0f, 0.0f, 40.0f), WALLTYPE_DOOR1);		//	���[��1�̃h�A
	SetModel(D3DXVECTOR3(800.0f, 0.0f, 40.0f), WALLTYPE_DOOR2);		//	���[��2�̃h�A
	SetModel(D3DXVECTOR3(1480.0f, 0.0f, 40.0f), WALLTYPE_DOOR3);	//	���[��3�̃h�A
	SetModel(D3DXVECTOR3(2160.0f, 0.0f, 40.0f), WALLTYPE_DOOR4);	//	���[��4�̃h�A

	SetModel(D3DXVECTOR3(2260.0f, 0.0f, 140.0f), WALLTYPE_GOALOKU);		//	�S�[���̉���
	SetModel(D3DXVECTOR3(2260.0f, 0.0f, -60.0f), WALLTYPE_GOALTEMAE);	//	�S�[���̎�O��
	SetModel(D3DXVECTOR3(2370.0f, 0.0f, 30.0f), WALLTYPE_GOALMIGI);		//	�S�[���̉E��

	// �J�����̏�����
	InitCamera();

	// ���b�V���t�B�[���h�̏�����
	InitMeshfield();

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

	//// �G�̏�����
	//InitEnemy();

	//// �u���b�N�̏�����
	//InitBlock();

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
	UninitMeshfield();

	 // ���b�V���̃V�����_�[�`�̏I��
	UninitMeshWall();

	 // ���b�V���h�[���̏I��
	UninitmeshFan();

	//���f���̏I������
	UninitModel();

	//// �u���b�N�̏I��
	//UninitBlock();

	//// �G�̏I��
	//UninitEnemy();

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
	int nNum = GetScore();
	//int nTime = GetTime();
	//bool bExit = GetExit();

	Player* pPlayer = GetPlayer();//�v���C���[�̏��ւ̃|�C���^�Ƀv���C���[�̐擪�A�h���X����������

	if (KeyboardTrigger(DIK_P) == true || JoyPadTrigger(JOYKEY_START) == true)
	{//ESCAPE(�|�[�Y)�L�[�������ꂽ
		g_bPause = g_bPause ? false : true;

		//PlaySound(SOUND_LABEL_PAUSE);

	}

	if (g_bPause == true)
	{//�|�[�Y��

		//�|�[�Y�̍X�V����
		UpdatePause();

	}
	else
	{

		//�v���C���[�̍X�V����
		UpdatePlayer();


		////�G�̍X�V����
		//UpdateEnemy();


		////���b�V���t�B�[���h�̍X�V����
		//UpdateMeshfield();


		////���b�V���V�����_�[�̍X�V����
		//UpdateMeshcylinder();


		//�J�����̍X�V����
		UpdateCamera();


		//���C�g�̍X�V����
		UpdateLight();


		//���f���̍X�V����
		UpdateModel();


		//�e�̍X�V����
		UpdateShadow();


		//�e�̍X�V����
		UpdateBullet();


		////�r���{�[�h�̍X�V����
		//UpdateBillboard();


		////�ǂ̍X�V����
		//UpdateWall();


		//�G�t�F�N�g�̍X�V����
		UpdateEffect();


		////�^�C���̍X�V����
		//UpdateTime();


		//�X�R�A�̍X�V����
		UpdateScore();


		////���U���g�X�R�A�̍X�V����
		//UpdateResultScore();


		//�p�[�e�B�N���̍X�V����
		UpdateParticle();

		//if (KeyboardTrigger(DIK_F5) == true)
		//{
		//	onWireFrame();
		//}
		//else if (KeyboardTrigger(DIK_F6) == true)
		//{
		//	offWireFrame();
		//}
	}

	//bool bEnd = GetEnd();

	if ((pPlayer->bDisp == false /*|| bExit == true*/ /*|| nTime <= 0*/ /*|| bEnd == true*/) && g_gameState != GAMESTATE_NONE)
	{

		//���[�h�ݒ�(���U���g��ʂɈڍs)
		g_gameState = GAMESTATE_END;

	}

	int nResultScore;
	nResultScore = GetScore();
	//nTime = GetTime();

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL://�ʏ���
		break;

	case GAMESTATE_END://�I�����
		g_nCounterGameState++;

		if (g_nCounterGameState >= 60)
		{

			g_nCounterGameState = 0;

			g_gameState = GAMESTATE_NONE;

			//���[�h�ݒ�(���U���g��ʂɈڍs)
			SetFade(MODE_RESULT);

			//if (bExit == true)
			//{

				////�^�C���ɉ����ăX�R�A���Z
				//AddScore((nTime * GetScore()) * 0.2f);


				////���U���g�X�R�A�̐ݒ�
				//SetResultScore(GetScore());


				//�����L���O�̃��Z�b�g
				ResetRanking();


				//�����L���O�̐ݒ�
				SetRanking(GetScore());

			//}

		}
		break;
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
	DrawMeshfield();

	//// ���b�V���h�[���̕`��
	//DrawmeshFan();

	//// ���b�V���̃V�����_�[�`�̕`��
	//DrawMeshWall();

	// �e�̕`��
	DrawShadow();

	//���f���̕`�揈��
	DrawModel();

	//// �u���b�N�̕`��
	//DrawBlock();

	//// �G�̕`��
	//DrawEnemy();

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