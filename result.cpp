//=============================
//
// ���U���g���� [result.cpp]
// Author:TEAM_2
//
//=============================

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "result.h"
#include "fade.h"
#include "player.h"
#include "Timer.h"
#include "sound.h"
#include "input.h"
#include "item.h"

//***************************
// �O���[�o���ϐ��錾
//***************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL; // ���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureResult= NULL;		 // �e�N�X�`���̃|�C���^
int g_aCount;									 // �J�E���g
int nNumResult;
//==================
// ���U���g�̏�����
//==================
void InitResult(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		

	// �v���C���[�̎擾
	Player* pPlayer = GetPlayer();

	// �^�C�}�[�����擾
	int nTime = GetTimer();

	// ������
	g_aCount = 0;
	nNumResult = 0;

	// �擾
	nNumResult = GetResultNumber();

	const char* TextureName = {};

	switch (nNumResult)
	{
	case 0:
		TextureName = "data\\TEXTURE\\result_B.png";
		break;

	case 1:
		TextureName = "data\\TEXTURE\\result_D.png";
		break;

	case 2:
		TextureName = "data\\TEXTURE\\result_S.png";
		break;

	case 3:
		TextureName = "data\\TEXTURE\\result_A.png";
		break;

	case 4:
		TextureName = "data\\TEXTURE\\result_C.png";
		break;

	case 5:
		TextureName = "data\\TEXTURE\\result_hatena.png";
		break;

	default:
		TextureName = "data\\TEXTURE\\result_hatena.png";
		break;
	}

	// �e�N�X�`���ݒ�
	D3DXCreateTextureFromFile(pDevice,
		TextureName ,
		&g_pTextureResult);

	// ���_���̃|�C���^
	VERTEX_2D* pVtx;		

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 1�ڂ̒��_���
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);		// 2�ڂ̒��_���
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);		// 3�ڂ̒��_���
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);	// 4�ڂ̒��_���

	// rhw�̐ݒ�(1.0f�ŌŒ�)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// �A�����b�N
	g_pVtxBuffResult->Unlock();

	// ���y���Đ�
	PlaySound(SOUND_LABLE_RESULTBGM);
}
//==================
// ���U���g�̏I��
//==================
void UninitResult(void)
{
	// ���y���~�߂�
	StopSound();

	// �e�N�X�`���̔j��
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}
//==================
// ���U���g�̍X�V
//==================
void UpdateResult(void)
{
	// �v���C���[�̎擾
	Player* pPlayer = GetPlayer();

	// ���݂̃t�F�[�h�̎擾
	FADE g_fade = GetFade();

	// �J�E���g�����Z
	g_aCount++;

	if (g_fade == FADE_NONE && (g_aCount >= 380 || KeyboardTrigger(DIK_RETURN) == true || JoyPadTrigger(JOYKEY_A) == true))
	{
		// Enter�L�[�������ꂽ
		// ���[�h�ݒ�(���U���g�Ɉړ�)
		SetFade(MODE_TITLE);
	}
}
//==================
// ���U���g�̕`��
//==================
void DrawResult(void)
{
	//�v���C���[�̎擾
	Player* pPlayer = GetPlayer();

	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResult);

	// ���U���g�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
