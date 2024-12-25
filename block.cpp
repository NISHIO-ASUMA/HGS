//=============================
//
// �u���b�N���� [block.cpp]
// Author: TEAM_2
// 
//=============================

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "input.h"
#include "block.h"
#include <stdio.h>
#include "enemy.h"
#include "shadow.h"
#include "player.h"

//*****************************
// �}�N����`
//*****************************
#define MAX_BLOCK (2)				// �g�����f���̍ő吔(1�^�C�v�ɂ�)
#define HALF (0.5f)					// �����̒l

//*****************************
// �O���[�o���ϐ��錾
//*****************************
Block g_Block[BLOCKTYPE_MAX][MAX_BLOCK];		// �\���̕ϐ�

//=========================
//�@�u���b�N����������
//=========================
void InitBlock(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �\���̕ϐ��̏�����
	for (int nCnt1 = 0; nCnt1 < BLOCKTYPE_MAX; nCnt1++)
	{
		for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
		{
			g_Block[nCnt1][nCnt].bUse = false;
			g_Block[nCnt1][nCnt].nType = BLOCKTYPE_BOARD;
			g_Block[nCnt1][nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Block[nCnt1][nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Block[nCnt1][nCnt].nidxshadow = 0;
		}
	}

	for (int nCnt1 = 0; nCnt1 < BLOCKTYPE_MAX; nCnt1++)
	{
		for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
		{
			// X�t�@�C���̕`��
			D3DXLoadMeshFromX(BLOCK_FILE[nCnt1],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Block[nCnt1][nCnt].pBuffMat,
				NULL,		   
				&g_Block[nCnt1][nCnt].dwNumMat,
				&g_Block[nCnt1][nCnt].pMesh);

		}
	}

	for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
	{
		for (int nCnt3 = 0; nCnt3 < MAX_BLOCK; nCnt3++)
		{// ���_��

			// ���[�J���ϐ��錾-----------------------------
			int nNumVtx;		// ���_��
			DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
			BYTE* pVtxBuff;		// ���_�o�b�t�@�̃|�C���^
			//----------------------------------------------

			// ���_���̎擾
			nNumVtx = g_Block[nCnt][nCnt3].pMesh->GetNumVertices();

			// ���_�̃T�C�Y���擾
			sizeFVF = D3DXGetFVFVertexSize(g_Block[nCnt][nCnt3].pMesh->GetFVF());

			// ���_�o�b�t�@�����b�N
			g_Block[nCnt][nCnt3].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			// ���_������
			for (int nCntBlock = 0; nCntBlock < nNumVtx; nCntBlock++)
			{
				// ���_���W�̑��
				D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;

				// ���_���W�̔�r
				if (Vtx.x > g_Block[nCnt][nCnt3].Vtxmax.x)
				{// x���ő�l���傫��������
					// ���
					g_Block[nCnt][nCnt3].Vtxmax.x = Vtx.x;
				}
				if (Vtx.y > g_Block[nCnt][nCnt3].Vtxmax.y)
				{// y���ő�l���傫��������
					// ���
					g_Block[nCnt][nCnt3].Vtxmax.y = Vtx.y;
				}
				if (Vtx.z > g_Block[nCnt][nCnt3].Vtxmax.z)
				{// z���ő�l���傫��������
					// ���
					g_Block[nCnt][nCnt3].Vtxmax.z = Vtx.z;
				}

				if (Vtx.x < g_Block[nCnt][nCnt3].Vtxmin.x)
				{// x���ŏ��l��菬����������
					// ���
					g_Block[nCnt][nCnt3].Vtxmin.x = Vtx.x;
				}
				if (Vtx.y < g_Block[nCnt][nCnt3].Vtxmin.y)
				{// y���ŏ��l��菬����������
					// ���
					g_Block[nCnt][nCnt3].Vtxmin.y = Vtx.y;
				}
				if (Vtx.z < g_Block[nCnt][nCnt3].Vtxmin.z)
				{// z���ŏ��l��菬����������
					// ���
					g_Block[nCnt][nCnt3].Vtxmin.z = Vtx.z;
				}

				// ���_�t�H�[�}�b�g�̃T�C�Y���i�߂�
				pVtxBuff += sizeFVF;
			}

			// �T�C�Y��������
			g_Block[nCnt][nCnt3].size.x = g_Block[nCnt][nCnt3].Vtxmax.x - g_Block[nCnt][nCnt3].Vtxmin.x;	// size��x
			g_Block[nCnt][nCnt3].size.y = g_Block[nCnt][nCnt3].Vtxmax.y - g_Block[nCnt][nCnt3].Vtxmin.y;	// size��y
			g_Block[nCnt][nCnt3].size.z = g_Block[nCnt][nCnt3].Vtxmax.z - g_Block[nCnt][nCnt3].Vtxmin.z;	// size��z

			// �A�����b�N
			g_Block[nCnt][nCnt3].pMesh->UnlockVertexBuffer();

			// �}�e���A���f�[�^�ւ̃|�C���^
			D3DXMATERIAL* pMat;

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Block[nCnt][nCnt3].pBuffMat->GetBufferPointer();

			// �}�e���A����������
			for (int nCntMat = 0; nCntMat < (int)g_Block[nCnt][nCnt3].dwNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					// �e�N�X�`���̓ǂݍ���
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_Block[nCnt][nCnt3].pTexture[nCntMat]);
				}
			}
		}
	}
}
//=========================
//�@�u���b�N�I������
//=========================
void UninitBlock(void)
{
	for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
	{
		for (int nCnt1 = 0; nCnt1 < MAX_BLOCK; nCnt1++)
		{
			// ���b�V���̔j��
			if (g_Block[nCnt][nCnt1].pMesh != NULL)
			{
				g_Block[nCnt][nCnt1].pMesh->Release();
				g_Block[nCnt][nCnt1].pMesh = NULL;
			}

			// �}�e���A���̔j��
			if (g_Block[nCnt][nCnt1].pBuffMat != NULL)
			{
				g_Block[nCnt][nCnt1].pBuffMat->Release();
				g_Block[nCnt][nCnt1].pBuffMat = NULL;
			}

			// �}�e���A����������
			for (int nCntMat = 0; nCntMat < (int)g_Block[nCnt][nCnt1].dwNumMat; nCntMat++)
			{
				// �e�N�X�`���̔j��
				if (g_Block[nCnt][nCnt1].pTexture[nCntMat] != NULL)
				{
					g_Block[nCnt][nCnt1].pTexture[nCntMat]->Release();
					g_Block[nCnt][nCnt1].pTexture[nCntMat] = NULL;
				}
			}
		}
	}
}
//=========================
//�@�u���b�N�X�V����
//=========================
void UpdateBlock(void)
{
	// ��U�Ȃ�
}
//=========================
//�@�u���b�N�`�揈��
//=========================
void DrawBlock(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X���擾
	pDevice = GetDevice();

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans,mtxScall;

	// ���݂̃}�e���A����ۑ�
	D3DMATERIAL9 matDef;

	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL* pMat;

	for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
	{
		for (int nCnt1 = 0; nCnt1 < MAX_BLOCK; nCnt1++)
		{
			if (!g_Block[nCnt][nCnt1].bUse)
			{// ���g�p
				continue;
			}

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Block[nCnt][nCnt1].mtxWorld);

			// �����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Block[nCnt][nCnt1].rot.y, g_Block[nCnt][nCnt1].rot.x, g_Block[nCnt][nCnt1].rot.z);
			D3DXMatrixMultiply(&g_Block[nCnt][nCnt1].mtxWorld, &g_Block[nCnt][nCnt1].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Block[nCnt][nCnt1].pos.x, g_Block[nCnt][nCnt1].pos.y, g_Block[nCnt][nCnt1].pos.z);
			D3DXMatrixMultiply(&g_Block[nCnt][nCnt1].mtxWorld, &g_Block[nCnt][nCnt1].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Block[nCnt][nCnt1].mtxWorld);

			// ���݂̃}�g���b�N�X�̎擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Block[nCnt][nCnt1].pBuffMat->GetBufferPointer();

			// �}�e���A����������
			for (int nCntMat = 0; nCntMat < (int)g_Block[nCnt][nCnt1].dwNumMat; nCntMat++)
			{
				// �}�e���A���ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �e�N�X�`���ݒ�
				pDevice->SetTexture(0, g_Block[nCnt][nCnt1].pTexture[nCntMat]);

				// ���f��(�p�[�c)�̕`��
				g_Block[nCnt][nCnt1].pMesh->DrawSubset(nCntMat);

			}
			// �}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}
//=============================
//�@�u���b�N�̓����蔻�菈��
//=============================
//void CollisionBlock(void)
//{
//	for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
//	{
//		for (int nCnt1 = 0; nCnt1 < MAX_BLOCK; nCnt1++)
//		{// �ő吔����
//			// �v���C���[�̎擾
//			Player* pPlayer = GetPlayer();
//
//			if (g_Block[nCnt][nCnt1].bUse)
//			{// �g�p����̎�
//
//				if (pPlayer->pos.y < g_Block[nCnt][nCnt1].pos.y + g_Block[nCnt][nCnt1].size.y &&
//					pPlayer->pos.y + pPlayer->size.y > g_Block[nCnt][nCnt1].pos.y - g_Block[nCnt][nCnt1].size.y)
//				{
//					// ���E�̓����蔻��----------------------
//					if (pPlayer->posOld.z - pPlayer->size.z * HALF < g_Block[nCnt][nCnt1].pos.z + g_Block[nCnt][nCnt1].size.z * HALF &&
//						pPlayer->pos.z + pPlayer->size.z * HALF > g_Block[nCnt][nCnt1].pos.z - g_Block[nCnt][nCnt1].size.z * HALF)
//					{
//						// ������߂荞��
//						if (pPlayer->posOld.x + pPlayer->size.x * HALF < g_Block[nCnt][nCnt1].pos.x - g_Block[nCnt][nCnt1].size.x * HALF &&
//							pPlayer->pos.x + pPlayer->size.x * HALF > g_Block[nCnt][nCnt1].pos.x - g_Block[nCnt][nCnt1].size.x * HALF)
//						{
//							pPlayer->pos.x = g_Block[nCnt][nCnt1].pos.x - g_Block[nCnt][nCnt1].size.x * HALF - pPlayer->size.x * HALF - 0.1f;
//
//						}
//						// �E����߂荞��
//						else if (pPlayer->posOld.x - pPlayer->size.x * HALF > g_Block[nCnt][nCnt1].pos.x + g_Block[nCnt][nCnt1].size.x * HALF &&
//							pPlayer->pos.x - pPlayer->size.x * HALF < g_Block[nCnt][nCnt1].pos.x + g_Block[nCnt][nCnt1].size.x * HALF)
//						{
//							pPlayer->pos.x = g_Block[nCnt][nCnt1].pos.x + g_Block[nCnt][nCnt1].size.x * 0.5f + pPlayer->size.x * HALF + 0.1f;
//						}
//					}
//
//					// �O��̓����蔻��------------------------------
//					if (pPlayer->posOld.x - pPlayer->size.z * HALF < g_Block[nCnt][nCnt1].pos.x + g_Block[nCnt][nCnt1].size.x * HALF &&
//						pPlayer->pos.x + pPlayer->size.x * HALF > g_Block[nCnt][nCnt1].pos.x - g_Block[nCnt][nCnt1].size.x * HALF)
//					{
//						// ��O����߂荞��
//						if (pPlayer->posOld.z + pPlayer->size.z * HALF < g_Block[nCnt][nCnt1].pos.z - g_Block[nCnt][nCnt1].size.z * HALF &&
//							pPlayer->pos.z + pPlayer->size.z * HALF > g_Block[nCnt][nCnt1].pos.z - g_Block[nCnt][nCnt1].size.z * HALF)
//						{
//							pPlayer->pos.z = g_Block[nCnt][nCnt1].pos.z - g_Block[nCnt][nCnt1].size.z * 0.5f - pPlayer->size.z * HALF - 0.3f;
//
//						}
//						// ������߂荞��
//						else if (pPlayer->posOld.z - pPlayer->size.z * HALF > g_Block[nCnt][nCnt1].pos.z + g_Block[nCnt][nCnt1].size.z * HALF &&
//							pPlayer->pos.z - pPlayer->size.z * HALF < g_Block[nCnt][nCnt1].pos.z + g_Block[nCnt][nCnt1].size.z * HALF)
//						{
//							pPlayer->pos.z = g_Block[nCnt][nCnt1].pos.z + g_Block[nCnt][nCnt1].size.z * HALF + pPlayer->size.z * HALF + 0.3f;
//
//						}
//					}
//
//					// �c�̓����蔻��--------------------------
//					if (pPlayer->pos.x - pPlayer->size.x * HALF < g_Block[nCnt][nCnt1].pos.x + g_Block[nCnt][nCnt1].size.x * HALF &&
//						pPlayer->pos.x + pPlayer->size.x * HALF > g_Block[nCnt][nCnt1].pos.x - g_Block[nCnt][nCnt1].size.x * HALF)
//					{
//						if (pPlayer->posOld.z - pPlayer->size.z * HALF < g_Block[nCnt][nCnt1].pos.z + g_Block[nCnt][nCnt1].size.z * HALF &&
//							pPlayer->pos.z + pPlayer->size.z * HALF > g_Block[nCnt][nCnt1].pos.z - g_Block[nCnt][nCnt1].size.z * HALF)
//						{
//							// �ォ��߂荞�񂾎�
//							if (pPlayer->posOld.y >= g_Block[nCnt][nCnt1].pos.y + g_Block[nCnt][nCnt1].size.y * HALF &&
//								pPlayer->pos.y < g_Block[nCnt][nCnt1].pos.y + g_Block[nCnt][nCnt1].size.y * HALF)
//							{
//								//pPlayer->bLanding = true;	// �W�����v
//								pPlayer->pos.y = (g_Block[nCnt][nCnt1].pos.y + g_Block[nCnt][nCnt1].size.y * HALF);
//								pPlayer->move.y = 0.0f;
//
//							}
//							// ������߂荞�񂾎�
//							else if (pPlayer->posOld.y + pPlayer->size.y <= g_Block[nCnt][nCnt1].pos.y - g_Block[nCnt][nCnt1].size.y * HALF &&
//								pPlayer->pos.y + pPlayer->size.y > g_Block[nCnt][nCnt1].pos.y - g_Block[nCnt][nCnt1].size.y * HALF)
//							{
//								pPlayer->pos.y = (g_Block[nCnt][nCnt1].pos.y - g_Block[nCnt][nCnt1].size.y) - pPlayer->size.y * HALF;
//								pPlayer->move.y = 0.0f;
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//
//	// �G�l�~�[��
//	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
//	{
//		for (int nCnt = 0; nCnt < BLOCKTYPE_MAX; nCnt++)
//		{
//			for (int nCnt1 = 0; nCnt1 < MAX_BLOCK; nCnt1++)
//			{// �ő吔����
//				// �G�l�~�[�̎擾
//				Enemy* pEnemy = GetEnemy();
//
//				if (g_Block[nCnt][nCnt1].bUse)
//				{// �g�p����̎�
//
//					if (pEnemy[nCntEnemy].pos.y < g_Block[nCnt][nCnt1].pos.y + g_Block[nCnt][nCnt1].size.y &&
//						pEnemy[nCntEnemy].pos.y + pEnemy[nCntEnemy].size.y > g_Block[nCnt][nCnt1].pos.y - g_Block[nCnt][nCnt1].size.y)
//					{
//						// ���E�̓����蔻��----------------------
//						if (pEnemy[nCntEnemy].posOld.z - pEnemy[nCntEnemy].size.z * HALF < g_Block[nCnt][nCnt1].pos.z + g_Block[nCnt][nCnt1].size.z * HALF &&
//							pEnemy[nCntEnemy].pos.z + pEnemy[nCntEnemy].size.z * HALF > g_Block[nCnt][nCnt1].pos.z - g_Block[nCnt][nCnt1].size.z * HALF)
//						{
//							// ������߂荞��
//							if (pEnemy[nCntEnemy].posOld.x + pEnemy[nCntEnemy].size.x * HALF < g_Block[nCnt][nCnt1].pos.x - g_Block[nCnt][nCnt1].size.x * HALF &&
//								pEnemy[nCntEnemy].pos.x + pEnemy[nCntEnemy].size.x * HALF > g_Block[nCnt][nCnt1].pos.x - g_Block[nCnt][nCnt1].size.x * HALF)
//							{
//								pEnemy[nCntEnemy].pos.x = g_Block[nCnt][nCnt1].pos.x - g_Block[nCnt][nCnt1].size.x * HALF - pEnemy[nCntEnemy].size.x * HALF - 0.1f;
//
//							}
//							// �E����߂荞��
//							else if (pEnemy[nCntEnemy].posOld.x - pEnemy[nCntEnemy].size.x * HALF > g_Block[nCnt][nCnt1].pos.x + g_Block[nCnt][nCnt1].size.x * HALF &&
//								pEnemy[nCntEnemy].pos.x - pEnemy[nCntEnemy].size.x * HALF < g_Block[nCnt][nCnt1].pos.x + g_Block[nCnt][nCnt1].size.x * HALF)
//							{
//								pEnemy[nCntEnemy].pos.x = g_Block[nCnt][nCnt1].pos.x + g_Block[nCnt][nCnt1].size.x * 0.5f + pEnemy[nCntEnemy].size.x * HALF + 0.1f;
//							}
//						}
//
//						// �O��̓����蔻��------------------------------
//						if (pEnemy[nCntEnemy].posOld.x - pEnemy[nCntEnemy].size.z * HALF < g_Block[nCnt][nCnt1].pos.x + g_Block[nCnt][nCnt1].size.x * HALF &&
//							pEnemy[nCntEnemy].pos.x + pEnemy[nCntEnemy].size.x * HALF > g_Block[nCnt][nCnt1].pos.x - g_Block[nCnt][nCnt1].size.x * HALF)
//						{
//							// ��O����߂荞��
//							if (pEnemy[nCntEnemy].posOld.z + pEnemy[nCntEnemy].size.z * HALF < g_Block[nCnt][nCnt1].pos.z - g_Block[nCnt][nCnt1].size.z * HALF &&
//								pEnemy[nCntEnemy].pos.z + pEnemy[nCntEnemy].size.z * HALF > g_Block[nCnt][nCnt1].pos.z - g_Block[nCnt][nCnt1].size.z * HALF)
//							{
//								pEnemy[nCntEnemy].pos.z = g_Block[nCnt][nCnt1].pos.z - g_Block[nCnt][nCnt1].size.z * 0.5f - pEnemy[nCntEnemy].size.z * HALF - 0.3f;
//
//							}
//							// ������߂荞��
//							else if (pEnemy[nCntEnemy].posOld.z - pEnemy[nCntEnemy].size.z * HALF > g_Block[nCnt][nCnt1].pos.z + g_Block[nCnt][nCnt1].size.z * HALF &&
//								pEnemy[nCntEnemy].pos.z - pEnemy[nCntEnemy].size.z * HALF < g_Block[nCnt][nCnt1].pos.z + g_Block[nCnt][nCnt1].size.z * HALF)
//							{
//								pEnemy[nCntEnemy].pos.z = g_Block[nCnt][nCnt1].pos.z + g_Block[nCnt][nCnt1].size.z * HALF + pEnemy[nCntEnemy].size.z * HALF + 0.3f;
//							}
//						}
//
//					}
//				}
//			}
//		}
//	}
//}
//=============================
//�@�u���b�N�̐ݒ菈��
//=============================
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot,BLOCKTYPE nType)
{
	for (int nCnt1 = 0; nCnt1 < MAX_BLOCK; nCnt1++)
	{
		if (!g_Block[nType][nCnt1].bUse)

		{
			// ���g�p�Ȃ�
			g_Block[nType][nCnt1].pos = pos;	// ���W
			g_Block[nType][nCnt1].rot = rot;	// �p�x
			g_Block[nType][nCnt1].nType = nType;// ���
			g_Block[nType][nCnt1].bUse = true;	// �g�p����
			//g_Block[nType][nCnt1].nidxshadow = SetShadow(D3DXVECTOR3(g_Block[nType][nCnt1].pos.x, 0.0f, g_Block[nType][nCnt1].pos.z), g_Block[nType][nCnt1].rot, D3DXVECTOR3(2.0f, 2.0f, 2.0f));
			break;
		}
	}
}
//=============================
//�@�u���b�N�̎擾����
//=============================
Block* GetBlock()
{
	return &g_Block[0][0];
}