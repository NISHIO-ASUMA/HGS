//================================
// 
// �A�C�e������ [item.cpp]
// Author : TEAM_2
// 
//================================

//*******************************
// �C���N���[�h�t�@�C���錾
//*******************************
#include "item.h"
#include "shadow.h"

//*******************************
// �}�N����`
//*******************************
#define MAX_ITEM (20)	// �ő吔

//*******************************
// �O���[�o���ϐ��錾
//*******************************
Item g_Item[MAX_ITEM];		// �\���̕ϐ�
int nNumItem;				// �A�C�e����
int nGetNumber;				// �擾�ԍ�

//==============================
// ������
//==============================
void InitItem()
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �O���[�o���ϐ��̏�����
	nGetNumber = 0;
	nNumItem = 0;

	// �\���̕ϐ��̏�����
	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	{
		g_Item[nCnt].bUse = false;						  // ���g�p����
		g_Item[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // ���W
		g_Item[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // �p�x
		g_Item[nCnt].Type = ITEMTYPE_SPRING;			  // ���

		for (int nModel = 0; nModel < ITEMTYPE_MAX; nModel++)
		{// ���f���̓ǂݍ���
			D3DXLoadMeshFromX(ITEM_MODEL[nModel],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Item[nCnt].aModel[nModel].pBuffMat,
				NULL,
				&g_Item[nCnt].aModel[nModel].dwNumMat,
				&g_Item[nCnt].aModel[nModel].pMesh);

			// �}�e���A���f�[�^�ւ̃|�C���^
			D3DXMATERIAL* pMat;

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Item[nCnt].aModel[nModel].pBuffMat->GetBufferPointer();

			// �}�e���A����������
			for (int nCntMat = 0; nCntMat < (int)g_Item[nCnt].aModel[nModel].dwNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					// �e�N�X�`���̓ǂݍ���
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_Item[nCnt].aModel[nModel].pTexture[nCntMat]);
				}
			}
		}
	}
}
//==============================
// �I��
//==============================
void UninitItem()
{
	// �e�N�X�`���̔j��
	// TODO : ���f���̃e�N�X�`�������ɂ�邽��,�̂��ɕύX

	// ���b�V��,�}�e���A���̔j��
	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	{
		for (int nModel = 0; nModel < ITEMTYPE_MAX; nModel++)
		{
			if (g_Item[nCnt].aModel[nModel].pBuffMat != NULL)
			{
				g_Item[nCnt].aModel[nModel].pBuffMat->Release();
				g_Item[nCnt].aModel[nModel].pBuffMat = NULL;
			}

			if (g_Item[nCnt].aModel[nModel].pMesh != NULL)
			{
				g_Item[nCnt].aModel[nModel].pMesh->Release();
				g_Item[nCnt].aModel[nModel].pMesh = NULL;
			}
		}
	}
}
//==============================
// �X�V
//==============================
void UpdateItem()
{
	// TODO : ��ɏ����ǉ�
}
//==============================
// �`��
//==============================
void DrawItem()
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans;

	// ���݂̃}�e���A����ۑ�
	D3DMATERIAL9 matDef;

	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL* pMat;

	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	{
		// �^�C�v��ۑ�
		int nType = g_Item[nCnt].Type;

		if (!g_Item[nCnt].bUse)
		{// ���g�p��ԂȂ�
			continue;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Item[nCnt].mtxWorld);

		// �����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Item[nCnt].rot.y, g_Item[nCnt].rot.x, g_Item[nCnt].rot.z);
		D3DXMatrixMultiply(&g_Item[nCnt].mtxWorld, &g_Item[nCnt].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Item[nCnt].pos.x, g_Item[nCnt].pos.y, g_Item[nCnt].pos.z);
		D3DXMatrixMultiply(&g_Item[nCnt].mtxWorld, &g_Item[nCnt].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Item[nCnt].mtxWorld);

		// ���݂̃}�g���b�N�X�̎擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A����������
		for (int nCntMat = 0; nCntMat < (int)g_Item[nCnt].aModel[nType].dwNumMat; nCntMat++)
		{
			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Item[nCnt].aModel[nType].pBuffMat->GetBufferPointer();

			// �e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_Item[nCnt].aModel[nType].pTexture[nCntMat]);

			// �u���b�N(�p�[�c)�̕`��
			g_Item[nCnt].aModel[nType].pMesh->DrawSubset(nCntMat);
		}
		// �}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}
//==============================
// �ݒ菈��
//==============================
void SetItem(D3DXVECTOR3 pos, ITEMTYPE Type)
{
	for (int nCnt1 = 0; nCnt1 < MAX_ITEM; nCnt1++)
	{
		if (!g_Item[nCnt1].bUse)
		{
			// ���g�p�Ȃ�
			g_Item[nCnt1].pos = pos;		// ���W
			g_Item[nCnt1].Type = Type;		// ���
			g_Item[nCnt1].bUse = true;		// �g�p����

			// �e�̐ݒ�
			g_Item[nCnt1].nIdxshadow = SetShadow(D3DXVECTOR3(g_Item[nCnt1].pos.x, 0.0f, g_Item[nCnt1].pos.z), g_Item[nCnt1].rot);

			// �A�C�e�������J�E���g
			nNumItem++;

			break;
		}
	}
}