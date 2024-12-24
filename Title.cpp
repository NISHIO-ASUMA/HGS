//=================================
//
// �^�C�g������ [title.cpp]
// Author: TEAM_2
//
//=================================

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "Title.h"
#include "sound.h"

//***************************
// �v���g�^�C�v�錾
//***************************
void SetTitle(int nType, D3DXVECTOR3 pos);	// �^�C�g���̐ݒ�
void TitleFlash(int nType);					// �^�C�g���̓_��

//***************************
// �O���[�o���ϐ��錾
//***************************
Title g_Title[TITLE_MAX];								// �\���̕ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;			// ���_�o�b�t�@�̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleback = NULL;		// �^�C�g���w�i
														   
LPDIRECT3DTEXTURE9 g_pTextureTitle[TITLE_MAX] = {};		// �e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTitleback = NULL;			// �^�C�g���w�i�e�N�X�`���̃|�C���^

int g_nCntTitleAnim;				// �^�C�g�����
int g_nPatternAnim;					// ��ԃp�^�[��
int g_aTimeCount;					// �^�C���J�E���g
int g_aSelect;						// �I��p�̕ϐ�

//===========================
// �^�C�g������������
//===========================
void InitTitle(void)
{
	// �f�o�C�X�ւ̃|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���̃|�C���^
	VERTEX_2D* pVtx;				

	// �w�i�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Title0.png",
		&g_pTextureTitleback);

	for (int nCnt = 0; nCnt < TITLE_MAX; nCnt++)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			TITLE_TEXTURE[nCnt],
			&g_pTextureTitle[nCnt]);
	}

	// �\���̕ϐ��̏�����
	for (int nCnt = 0; nCnt < TITLE_MAX; nCnt++)
	{
		g_Title[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// ���W
		g_Title[nCnt].nType = 0;						  // ���
		g_Title[nCnt].fHeight = 0.0f;					  // ����
		g_Title[nCnt].fWidth = 0.0f;					  // ����
		g_Title[nCnt].state = TITLESTATE_NORMAL;		  // ���
		g_Title[nCnt].bUse = false;						  // ���g�p����
	}

	g_nCntTitleAnim = 0;		// �^�C�g����ԗp
	g_nPatternAnim = 0;			// ��ԃp�^�[���p
	g_aTimeCount = 0;			// �^�C���J�E���g�p
	g_aSelect = TITLE_FIRST;	// �����̑I�����

	//==================
	//�^�C�g���w�i
	//==================
	
	// ���_�o�b�t�@�̐��� �w�i
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitleback,
		NULL);

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffTitleback->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// �A�����b�N
	g_pVtxBuffTitleback->Unlock();

	//==================
	//�^�C�g���`��
	//==================

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TITLE_MAX,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < TITLE_MAX; nCntTitle++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 1�ڂ̒��_���
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 2�ڂ̒��_���
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 3�ڂ̒��_���
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 4�ڂ̒��_���

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

		// ���_�������炷
		pVtx += 4;
	}

	// �Z�b�g
	SetTitle(TITLE_FIRST, D3DXVECTOR3(650.0f, 400.0f, 0.0f));	// �^�C�g��1
	SetTitle(TITLE_SECOND, D3DXVECTOR3(650.0f, 550.0f, 0.0f));	// �^�C�g��2

	//�A�����b�N
	g_pVtxBuffTitle->Unlock();

	// ���y�Đ�
	PlaySound(SOUND_LABEL_TITLEBGM);
}
//===================
// �^�C�g���̏I������
//===================
void UninitTitle(void)
{
	// �T�E���h�̔j��
	StopSound();

	//=======================
	// �^�C�g���̔w�i�I������
	//=======================

	// �e�N�X�`���̔j��
	if (g_pTextureTitleback != NULL)
	{
		g_pTextureTitleback->Release();
		g_pTextureTitleback = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitleback != NULL)
	{
		g_pVtxBuffTitleback->Release();
		g_pVtxBuffTitleback = NULL;
	}

	//==================
	// �^�C�g���̏I��
	//==================

	for (int nCntTitle = 0; nCntTitle < TITLE_MAX; nCntTitle++)
	{
		// �e�N�X�`���̔j��
		if (g_pTextureTitle[nCntTitle] != NULL)
		{
			g_pTextureTitle[nCntTitle]->Release();
			g_pTextureTitle[nCntTitle] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

}
//=======================
// �^�C�g���̍X�V����
//=======================
void UpdateTitle(void)
{
	// ���݂̏�Ԃ̃t�F�[�h���擾
	FADE g_fade = GetFade();		

	// ���_���̃|�C���^
	VERTEX_2D* pVtx;

	g_aTimeCount++;//�J�E���g���Z

	if (g_aTimeCount >= 600)
	{// �^�C�}�[�J�E���g������ɒB������
		// ��ʑJ��
		SetFade(MODE_RANKING);
	}

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < TITLE_MAX; nCount++)
	{
		// ���_�J���[��ݒ�(��)
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���_�������炷
		pVtx += 4;
	}

	// pVtx��߂�
	pVtx -= 4 * TITLE_MAX;		

	// ���j���[�̑I��
	if (KeyboardTrigger(DIK_UP) == true || JoypadTrigger(JOYKEY_UP) == true || KeyboardTrigger(DIK_W) == true)
	{// UP�L�[ or �p�b�h�̏�L�[ or W�L�[�������ꂽ
		
		g_aSelect--;//�@�f�N�������g

		if (g_aSelect < TITLE_FIRST)
		{//�@TITLE_FIRST���Z���N�g��菬����������
			// �I����Ԃ�2�ڂɐݒ�
			g_aSelect = TITLE_SECOND;
		}
	}

	else if (KeyboardTrigger(DIK_DOWN) == true || JoypadTrigger(JOYKEY_DOWN) == true || KeyboardTrigger(DIK_S) == true)
	{// DOWN�L�[ or �p�b�h�̉��L�[ or S�L�[�������ꂽ
		
		g_aSelect++;// �C���N�������g

		if (g_aSelect >= TITLE_MAX)
		{//�@TITLE_MAX���Z���N�g��菬����������
			// �I����Ԃ�1�ڂɐݒ�	
			g_aSelect = TITLE_FIRST;
		}
	}

	// �I����
	pVtx += 4 * g_aSelect;							

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

	// �A�����b�N
	g_pVtxBuffTitle->Unlock();

	if (g_fade == FADE_NONE && (KeyboardTrigger(DIK_RETURN) == true || JoypadTrigger(JOYKEY_A) == true))
	{
		// ���y���Đ�
		PlaySound(SOUND_LABLE_ENTERSE);

		// �G���^�[�L�[�������ꂽ or A�{�^���������ꂽ
		// �e��ʂɈړ�
		switch (g_aSelect)
		{
		case TITLE_FIRST:

			//�`���[�g���A���Ɉڍs
			SetFade(MODE_TUTORIAL);

			// Enter�L�[�������ꂽ
			for (int nCntTitle = 0; nCntTitle < TITLE_MAX; nCntTitle++)
			{
				if (g_Title[nCntTitle].bUse == true && g_Title[nCntTitle].nType == TITLE_FIRST)
				{// �g�p��Ԃ���ڂ̃^�C�g��
					// �_�ł�����
					g_Title[nCntTitle].state = TITLESTATE_FLASH;
				}
			}
			break;

		case TITLE_SECOND:

			// �Q�[����ʂɈڍs
			SetFade(MODE_GAME);
			for (int nCntTitle = 0; nCntTitle < TITLE_MAX; nCntTitle++)
			{
				if (g_Title[nCntTitle].bUse == true && g_Title[nCntTitle].nType == TITLE_SECOND)
				{// �g�p��Ԃ���ڂ̃^�C�g��
					// �_�ł�����
					g_Title[nCntTitle].state = TITLESTATE_FLASH;
				}
			}

			break;

		}
	}

	TitleFlash(TITLE_FIRST);	// �^�C�g���̓_��
	TitleFlash(TITLE_SECOND);	// �^�C�g���̓_��
}
//===================
// �^�C�g���̕`�揈��
//===================
void DrawTitle(void)
{
	// �f�o�C�X�ւ̃|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	

	//=====================
	// �^�C�g���w�i�̕`��
	//=====================

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitleback, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitleback);

	// �^�C�g���|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//==================
	// �^�C�g���̕`��
	//==================

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < TITLE_MAX; nCntTitle++)
	{
		// �e�N�X�`���̐ݒ�(�^�C�v���ݒ�)
		pDevice->SetTexture(0, g_pTextureTitle[g_Title[nCntTitle].nType]);

		// �^�C�g���|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);
	}

}
//======================
// �^�C�g���̐ݒ菈��
//======================
void SetTitle(int nType, D3DXVECTOR3 pos)
{
	// ���_���̃|�C���^
	VERTEX_2D* pVtx;		

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < TITLE_MAX; nCnt++)
	{
		if (!g_Title[nCnt].bUse)
		{// �g���Ă�����
			g_Title[nCnt].nType = nType;
			g_Title[nCnt].pos = pos;
			g_Title[nCnt].bUse = true;

			//�ꍇ����
			switch (nType)
			{
			case TITLE_FIRST:
				// ����,������ݒ�
				g_Title[nCnt].fHeight = 100.0f;	// ����
				g_Title[nCnt].fWidth = 450.0f;	// ����
				break;

			case TITLE_SECOND:
				// ����,������ݒ�
				g_Title[nCnt].fHeight = 100.0f;	// ����
				g_Title[nCnt].fWidth = 400.0f;	// ����
				break;
			}

			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_Title[nCnt].pos.x - g_Title[nCnt].fWidth * 0.5f, g_Title[nCnt].pos.y - g_Title[nCnt].fHeight * 0.5f, 0.0f);		//1�ڂ̒��_���
			pVtx[1].pos = D3DXVECTOR3(g_Title[nCnt].pos.x + g_Title[nCnt].fWidth * 0.5f, g_Title[nCnt].pos.y - g_Title[nCnt].fHeight * 0.5f, 0.0f);		//2�ڂ̒��_���
			pVtx[2].pos = D3DXVECTOR3(g_Title[nCnt].pos.x - g_Title[nCnt].fWidth * 0.5f, g_Title[nCnt].pos.y + g_Title[nCnt].fHeight * 0.5f, 0.0f);		//3�ڂ̒��_���
			pVtx[3].pos = D3DXVECTOR3(g_Title[nCnt].pos.x + g_Title[nCnt].fWidth * 0.5f, g_Title[nCnt].pos.y + g_Title[nCnt].fHeight * 0.5f, 0.0f);		//4�ڂ̒��_���

			break;

		}

		// ���_��񕪂��炷
		pVtx += 4;

	}
	// �A�����b�N
	g_pVtxBuffTitle->Unlock();

}
//==============================
// �^�C�g���̓_��
//==============================
void TitleFlash(int nType)
{
	//���_���̃|�C���^
	VERTEX_2D* pVtx = 0;		

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < TITLE_MAX; nCntTitle++)
	{
		if (g_Title[nCntTitle].bUse == true && g_Title[nCntTitle].state == TITLESTATE_FLASH)
		{// �^�C�g�����g���Ă��ď�Ԃ��_�ŏ�Ԃ̎�

			// �J�E���^�[�����Z
			g_nCntTitleAnim++;				

			if (g_nCntTitleAnim == 5)		
			{// 5�̎�
				// ���_�J���[�̐ݒ�(����)
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);

			}

			else if (g_nCntTitleAnim == 10)	
			{// 10�̎�
				// ���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// �����l�ɖ߂�
				g_nCntTitleAnim = 0;		
			}
		}

		// ���_��񕪂��炷
		pVtx += 4;
	}
	// �A�����b�N
	g_pVtxBuffTitle->Unlock();

}
