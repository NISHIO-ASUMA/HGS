//=============================================================================
//
// �`���[�g���A������ [tutorial2.cpp]
// Author : TANEKAWA RIKU
//
//=============================================================================
#include "tutorial2.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial2 = NULL;   //���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTutorial2 = NULL;        //�^�C�g���w�i�e�N�X�`���̃|�C���^

//=================================
//�`���[�g���A�����2�̏�����
//=================================
void InitTutorial2(void)
{

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tutorial002.png",
		&g_pTextureTutorial2);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial2,
		NULL);


	VERTEX_2D* pVtx;


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTutorial2->Lock(0, 0, (void**)&pVtx, 0);


	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);


	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;


	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorial2->Unlock();

}
//=================================
//�`���[�g���A�����2�̏I������
//=================================
void UninitTutorial2(void)
{
	StopSound();

	//�e�N�X�`���̔j��
	if (g_pTextureTutorial2 != NULL)
	{
		g_pTextureTutorial2->Release();
		g_pTextureTutorial2 = NULL;
	}


	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTutorial2 != NULL)
	{
		g_pVtxBuffTutorial2->Release();
		g_pVtxBuffTutorial2 = NULL;
	}

}
//=================================
//�`���[�g���A�����2�̍X�V����
//=================================
void UpdateTutorial2(void)
{
	FADE g_fade = GetFade(); // ���݂̏��

	if (g_fade == FADE_NONE && (KeyboardTrigger(DIK_RIGHT) == true || JoyPadTrigger(JOYKEY_A) == true))
	{//����L�[(ENTER�L�[)�������ꂽ

		//���[�h�ݒ�(�Z���N�g��ʂɈڍs)
		SetFade(MODE_GAME);

		//PlaySound(SOUND_LABEL_TUTORIALEND);

	}
	else if (g_fade == FADE_NONE && (KeyboardTrigger(DIK_LEFT) == true || JoyPadTrigger(JOYKEY_B) == true))
	{
		//���[�h�ݒ�(�`���[�g���A����ʂɈڍs)
		SetMode(MODE_TUTORIAL);

		//PlaySound(SOUND_LABEL_TUTORIAL);

	}
}
//=================================
//�`���[�g���A�����2�̍X�V����
//=================================
void DrawTutorial2(void)
{

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial2, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTutorial2);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}