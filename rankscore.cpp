//==============================
//
// �����L���O�X�R�A����
// Author:TEAM_2
//
//==============================

//*******************************
// �C���N���[�h�t�@�C���錾
//*******************************
#include "rankscore.h"
#include "ranking.h"
#include "input.h"
#include "fade.h"
#include <stdio.h>
//#include "score.h"

//*******************************
// �}�N����`
//*******************************
#define MAX_RANK    (5)						// �\�����ʐ���ݒ�(5�ʂ܂�)
#define MAX_DIGIT	(8)						// ����
#define MAX_POLYGON (MAX_RANK * MAX_DIGIT)	// �ő�|���S����
#define POLYGON_SIZEWIDTH (68.0f)			// �|���S����
#define POLYGON_SIZEHIGHT (68.0f)			// �|���S������
#define POLYGON_INTERVAL_Y (60.0f)			// �X�R�A�\���̊Ԋu�󂯂鍂��

//*******************************
// �\���̐錾
//*******************************
typedef struct
{
	D3DXVECTOR3 pos;		// ���W
	int nScore;				// �X�R�A
}RankScore;

//*******************************
// �v���g�^�C�v�錾
//*******************************


// �O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureRankScore = NULL;			// �e�N�X�`���̃|�C���^(�X�R�A)
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankScore = NULL;		// ���_�o�b�t�@�̃|�C���^(�X�R�A)
RankScore g_aRankScore[MAX_RANK];						// �����L���O�X�R�A���
int g_nRankUpdate = -1;									// �X�V�����NNo
int g_nTimeRanking;										// �����L���O��ʕ\���^�C�}�[
int g_nCntscoreAnim;									// �X�R�A�̃A�j���[�V�����J�E���^�[

//====================
// ������
//====================
void InitRankingScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���(�X�R�A)
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number003.png",
		&g_pTextureRankScore);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankScore,
		NULL);

	g_nTimeRanking = 0;     // �����L���O��ʕ\���^�C�}�[
	g_nCntscoreAnim = 0;    // �X�R�A�̃A�j���[�V�����J�E���^�[

	VERTEX_2D* pVtx;		// ���_���̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	// ���ʐ�����(5)
	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		g_aRankScore[nCntRank].pos = D3DXVECTOR3(500.0f,160.0f + (POLYGON_SIZEHIGHT * nCntRank) + (POLYGON_INTERVAL_Y * nCntRank), 0.0f);
		g_aRankScore[nCntRank].nScore = 0;

		// ��������(8)
		for (int nCntScore = 0; nCntScore < MAX_DIGIT; nCntScore++)
		{
			// ���_���W1�̐ݒ�
			pVtx[0].pos.x = g_aRankScore[nCntRank].pos.x - POLYGON_SIZEWIDTH / 2 + (POLYGON_SIZEWIDTH * nCntScore);	  // 1�ڂ̒��_���
			pVtx[0].pos.y = g_aRankScore[nCntRank].pos.y - POLYGON_SIZEHIGHT / 2;									  // 1�ڂ̒��_���
			pVtx[0].pos.z = 0.0f;																					  // 1�ڂ̒��_���
																														 
			pVtx[1].pos.x = g_aRankScore[nCntRank].pos.x + POLYGON_SIZEWIDTH / 2 + (POLYGON_SIZEWIDTH * nCntScore);	  // 2�ڂ̒��_���
			pVtx[1].pos.y = g_aRankScore[nCntRank].pos.y - POLYGON_SIZEHIGHT / 2;									  // 2�ڂ̒��_���
			pVtx[1].pos.z = 0.0f;																					  // 2�ڂ̒��_���
																														 
			pVtx[2].pos.x = g_aRankScore[nCntRank].pos.x - POLYGON_SIZEWIDTH / 2 + (POLYGON_SIZEWIDTH * nCntScore);	  // 3�ڂ̒��_���
			pVtx[2].pos.y = g_aRankScore[nCntRank].pos.y + POLYGON_SIZEHIGHT / 2;									  // 3�ڂ̒��_���
			pVtx[2].pos.z = 0.0f;																					  // 3�ڂ̒��_���
																														 
			pVtx[3].pos.x = g_aRankScore[nCntRank].pos.x + POLYGON_SIZEWIDTH / 2 + (POLYGON_SIZEWIDTH * nCntScore);	  // 4�ڂ̒��_���
			pVtx[3].pos.y = g_aRankScore[nCntRank].pos.y + POLYGON_SIZEHIGHT / 2;									  // 4�ڂ̒��_���
			pVtx[3].pos.z = 0.0f;																					  // 4�ڂ̒��_���

			// rhw�̐ݒ�(1.0f�ŌŒ�)
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f,1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f,1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f,1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f,1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			pVtx += 4;

		}

	}

	// �A�����b�N
	g_pVtxBuffRankScore->Unlock();

}
//====================
// �I��
//====================
void UninitRankingScore(void)
{
	//�X�R�A
	//�e�N�X�`���̔j��
	if (g_pTextureRankScore != NULL)
	{
		g_pTextureRankScore->Release();
		g_pTextureRankScore = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRankScore != NULL)
	{
		g_pVtxBuffRankScore->Release();
		g_pVtxBuffRankScore = NULL;
	}

}
//====================
// �X�V
//====================
void UpdateRankingScore(void)
{
	static int nCounter{};

	if (g_nRankUpdate != -1)
	{
		nCounter++;   //���Z

		//�Y���X�R�A��_��
		if (nCounter == 5)
		{
			VERTEX_2D* pVtx{};       //���_���̃|�C���^

			//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
			g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (32 * g_nRankUpdate);

			for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
			{
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 120);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 120);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 120);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 120);
				pVtx += 4;
			}

			g_pVtxBuffRankScore->Unlock();
		}
		else if (nCounter == 10)
		{
			VERTEX_2D* pVtx{};       // ���_���̃|�C���^

			// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
			g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (32 * g_nRankUpdate);

			for (int nCnt1 = 0; nCnt1 < MAX_DIGIT; nCnt1++)
			{
				pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

				pVtx += 4;
			}

			g_pVtxBuffRankScore->Unlock();

			nCounter = 0;
		}

	}

	FADE g_fade = GetFade();

	g_nTimeRanking++;	// �^�C�}�[�����Z

	if (g_fade == FADE_NONE && (g_nTimeRanking >= 600 || KeyboardTrigger(DIK_RETURN) == true || JoyPadTrigger(JOYKEY_A) == true))
	{
		//�^�C�g���ɂ���
		SetFade(MODE_TITLE);
	}

	//�A�����b�N
	g_pVtxBuffRankScore->Unlock();

}
//=========================
// �����L���O�̃X�R�A�̕`��
//=========================
void DrawRankingScore(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;		

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRankScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_POLYGON; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRankScore);

		//�|���S���̕`��(1��ޖ�)
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}

}
//================================
// �����L���O�̐ݒ菈��
//================================
void SetRanking(int nScore)
{
	// �ꎞ�I�ɕێ�
	int Temp{};		

	// ������
	g_nRankUpdate = -1;	

	// �~���œ���ւ���
	for (int nCnt1 = 0; nCnt1 < MAX_RANK - 1; nCnt1++)	// �v�f1
	{
		for (int nCnt2 = nCnt1 + 1; nCnt2 < MAX_RANK; nCnt2++)	// �v�f2
		{
			if (g_aRankScore[nCnt1].nScore < g_aRankScore[nCnt2].nScore)
			{ // �v�f2���v�f1�����傫������
				// ����ւ�����
				Temp = g_aRankScore[nCnt1].nScore;							// �ۑ��p�ɗv�f1������
				g_aRankScore[nCnt1].nScore = g_aRankScore[nCnt2].nScore;	// �v�f1�ɗv�f2������
				g_aRankScore[nCnt2].nScore = Temp;							// �v�f2�ɕۑ��p (�v�f1) ������
			}
		}
	}

	// �ēx�~���œ���ւ��� (����̃X�R�A���݂Ń\�[�g����)
	for (int nCntScore = MAX_RANK - 1; nCntScore >= 0; nCntScore--)
	{
		if (g_aRankScore[nCntScore].nScore < nScore)
		{
			Temp = g_aRankScore[nCntScore].nScore;

			g_aRankScore[nCntScore].nScore = nScore;

			if (nCntScore != MAX_RANK - 1)
			{ 
				// �ŉ��ʂ���Ȃ���Γ���ւ��� (�ŉ��ʂ͓���ւ���K�v���Ȃ��C����ւ���킪�Ȃ�)
				g_aRankScore[nCntScore + 1].nScore = Temp;
			}
			// ����(�����N)���X�V
			g_nRankUpdate = nCntScore;	
		}
	}

	// �X�R�A�̏����o��
	WriteScore();

}
//================================
// �����L���O�̃��Z�b�g����
//================================
void ResetRanking(void)
{
	// �t�@�C��
	FILE* pFile;

	// �t�@�C���J��
	pFile = fopen("data\\ranking.txt", "r");

	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			//�t�@�C���J������
			fscanf(pFile, "%d", &g_aRankScore[nCnt].nScore);
		}
	}
	else
	{
		// �J���Ȃ�������
		// ���b�Z�[�WBOX�̕\��
		MessageBox(NULL, "�J���܂���", "�G���[", MB_OK);

		return;
	}

	// �t�@�C�������
	fclose(pFile);

}
//====================================
// �����L���O�̃X�R�A�̃e�N�X�`������
//====================================
void SetRankingTexture(void)
{
	// �������̐������i�[
	int aPosTexU[MAX_DIGIT] = {};		
	int aData = 10000000;
	int aData2 = 1000000;

	// ���_���̃|�C���^
	VERTEX_2D* pVtx;			

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		for (int nCntscore = 0; nCntscore < MAX_DIGIT; nCntscore++)
		{
			if (nCntscore == 0)
			{
				// 0�Ԗڂ̎�
				aPosTexU[0] = g_aRankScore[nCnt].nScore / aData;
			}
			else
			{
				// 0�ԖڈȊO�̎�
				aPosTexU[nCntscore] = g_aRankScore[nCnt].nScore % aData / aData2;
				aData = aData / 10;
				aData2 = aData2 / 10;
			}

			// �e�N�X�`���ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntscore]), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntscore]), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntscore]), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntscore]), 1.0f);

			// ���_��񕪂��炷
			pVtx += 4;
		}

		// �l��߂�
		aData = 10000000;
		aData2 = 1000000;

	}

	// �A�����b�N
	g_pVtxBuffRankScore->Unlock();
}
//=====================
// �X�R�A�������o��
//=====================
void WriteScore(void)
{
	// �t�@�C���|�C���^
	FILE* pFile;

	// �t�@�C�����J��
	pFile = fopen("data\\ranking.txt", "w");

	// �t�@�C�����J������
	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			// �z�u��������������
			fprintf(pFile, "%d\n", g_aRankScore[nCnt].nScore);
		}
	}
	else
	{
		// �t�@�C�����J���Ȃ�������
		// ���b�Z�[�WBOX�̕\��
		MessageBox(NULL, "�J���܂���", "�G���[", MB_OK);

		return;
	}

	// �t�@�C�������
	fclose(pFile);
}