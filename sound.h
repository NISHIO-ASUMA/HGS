//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : TEAM_2
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************
// �C���N���[�h�t�@�C���錾
//*****************************
#include "main.h"

//*****************************************************************************
// �T�E���h�ꗗ
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_TITLEBGM = 0,
	SOUND_LABEL_TUTORIALBGM,
	SOUND_LABLE_GAMEBGM,
	SOUND_LABLE_RESULTBGM,
	SOUND_LABEL_RANKING,
	SOUND_LABLE_ENTERSE,
	SOUND_LABLE_DAMAGESE,
	SOUND_LABLE_PAUSESE,
	SOUND_LABLE_JUMPSE,
	SOUND_LABLE_EXITSE,
	SOUND_LABLE_PLAYERDAMAGE,
	SOUND_LABLE_PAUSEMENU,
	SOUND_LABLE_SELECTSE,
	SOUND_LABLE_STEP1,
	SOUND_LABLE_STEP2,

	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
