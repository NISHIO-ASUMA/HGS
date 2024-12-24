//======================================
//
// �`���[�g���A������ [tutorial.cpp]
// Author: TEAM_2
//
//======================================

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "tutorial.h"
#include "fade.h"
#include "input.h"

//****************************
// �O���[�o���ϐ��錾
//****************************
Tutorial g_Tutorial;										// �\���̕ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;			// ���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTutorial[TUTORIAL_MAX] = {};	// �e�N�X�`���̃|�C���^

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorialBG = NULL;		// �w�i�p�̒��_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTutorialBG = NULL;				// �w�i�p�̃e�N�X�`���̃|�C���^

//============================
// �`���[�g���A������������
//============================
void InitTutorial(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < TUTORIAL_MAX; nCnt++)
	{// �񋓌^�̐��̕�
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			TUTORIAL_TEXTURE[nCnt],
			&g_pTextureTutorial[nCnt]);
	}

	// �w�i�̃e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\start.png",
		&g_pTextureTutorialBG);

	// �\���̕ϐ��̏�����
	g_Tutorial.fHeight = 0.0f;					 // ����
	g_Tutorial.fWidth = 0.0f;					 // ����
	g_Tutorial.nType = 0;						 // ���
	g_Tutorial.pos = D3DXVECTOR3(0.0f,0.0f,0.0f);// ���W
	g_Tutorial.state = TUTORIALSTATE_NORMAL;	 // �������

	// ���_���̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorialBG,
		NULL);

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffTutorialBG->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	1�ڂ̒��_���
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);		//	2�ڂ̒��_���
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);		//	3�ڂ̒��_���
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);	//	4�ڂ̒��_���

	// rhw�̐ݒ�(1.0f�ŌŒ�)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// �z�u
	SetTutorial(D3DXVECTOR3(600.0f, 360.0f, 0.0f));

	// �A�����b�N
	g_pVtxBuffTutorialBG->Unlock();
}
//============================
// �`���[�g���A���I������
//============================
void UninitTutorial(void)
{
	// �e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < TUTORIAL_MAX; nCnt++)
	{
		if (g_pTextureTutorial[nCnt] != NULL)
		{// NULL����Ȃ�������
			g_pTextureTutorial[nCnt]->Release();
			g_pTextureTutorial[nCnt] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffTutorial != NULL)
	{// NULL����Ȃ�������
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

	// �w�i�e�N�X�`���̔j��
	if (g_pTextureTutorialBG != NULL)
	{// NULL����Ȃ�������
		g_pTextureTutorialBG->Release();
		g_pTextureTutorialBG = NULL;
	}
	
	// �w�i���_�o�b�t�@�̔j��
	if (g_pVtxBuffTutorial != NULL)
	{// NULL����Ȃ�������
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}
}
//============================
// �`���[�g���A���X�V����
//============================
void UpdateTutorial(void)
{
	if (KeyboardTrigger(DIK_RETURN))
	{
		// ��ʑJ��
		SetFade(MODE_GAME);
	}
}
//============================
// �`���[�g���A���`�揈��
//============================
void DrawTutorial(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorialBG, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTutorialBG);

	// �`���[�g���A���|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);// 1�ڂ̃v���C���[�̎n�_(0�Ԗځ`3�Ԗ�)

}
//============================
// �`���[�g���A���ݒ菈��
//============================
void SetTutorial(D3DXVECTOR3 pos)
{
	g_Tutorial.pos = pos;		// ���W��ݒ�
}
