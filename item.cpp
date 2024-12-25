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
#include "player.h"
#include "input.h"

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
bool g_bItem[ITEMTYPE_MAX];	// �擾	

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
		g_Item[nCnt].nLife = 1;							  // �̗�

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
	// �v���C���[�̎擾
	Player* pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	{
		if (!g_Item[nCnt].bUse)
		{// ���g�p��Ԃ̎�
			continue;
		}

		// ��ނ�ۑ�
		int nType = g_Item[nCnt].Type;

		// �e�̍��W�X�V�ݒ�
		SetPositionShadow(g_Item[nCnt].nIdxshadow, D3DXVECTOR3(g_Item[nCnt].pos.x, 0.0f, g_Item[nCnt].pos.z));

		// ���a���Z�o����ϐ�
		D3DXVECTOR3 PlayerPos(6.0f, 0.0f, 6.0f);
		D3DXVECTOR3 ItemPos(6.0f, 0.0f, 6.0f);

		// �v���C���[�Ƃ̋����̍������߂�
		D3DXVECTOR3 diff = pPlayer->pos - g_Item[nCnt].pos;

		// �p�x�̎Z�o
		float fAngle = atan2f(diff.x, diff.z);

		// �͈͌v�Z===============================================
		// ���������߂�
		float fDisX = (pPlayer->pos.x - g_Item[nCnt].pos.x);
		float fDisY = (pPlayer->pos.y - g_Item[nCnt].pos.y);
		float fDisZ = (pPlayer->pos.z - g_Item[nCnt].pos.z);

		// 2�̔��a
		float fRadX = (PlayerPos.x + ItemPos.x);
		float fRadY = (PlayerPos.y + ItemPos.y);
		float fRadZ = (PlayerPos.z + ItemPos.z);
		//========================================================

		// �͈͓��ɂ͂������Ƃ�
		if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX + fRadY + fRadZ) * (fRadX + fRadY + fRadZ))
		{
			if (KeyboardTrigger(DIK_RETURN) || JoyPadTrigger(JOYKEY_B))
			{// ENTER ��������B�{�^���������ꂽ
				// �q�b�g����
				HitItem(nCnt, 1);
			}
		}

		g_Item[nCnt].rot.y += 0.02f;
	}	
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

		if (!g_Item[nCnt].bUse)
		{// ���g�p��ԂȂ�
			continue;
		}

		// �^�C�v��ۑ�
		int nType = g_Item[nCnt].Type;

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

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Item[nCnt].aModel[nType].pBuffMat->GetBufferPointer();

		// �}�e���A����������
		for (int nCntMat = 0; nCntMat < (int)g_Item[nCnt].aModel[nType].dwNumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

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
//============================
// �q�b�g����
//============================
void HitItem(int nCnt, int nDamage)
{
	// �_���[�W���󂯂���̗͌���
	g_Item[nCnt].nLife -= nDamage;

	// Life��0�ȉ��̎�
	if (g_Item[nCnt].nLife <= 0)
	{
		//	���g�p����
		g_Item[nCnt].bUse = false;

		// �e������
		ShadowFalse(g_Item[nCnt].nIdxshadow);

		// �擾������Ԃɂ���
		g_bItem[g_Item[nCnt].Type] = true;
	}
}
//============================
// ���U���g�ւ̔ԍ���n��
//============================
int GetResultNumber()
{
	// TODO : ������A�C�e���ɂ���ă��U���g�̃e�N�X�`����ύX�����鏈��
	return nGetNumber;
}
//============================
// �擾����
//============================
Item* GetItem()
{
	return &g_Item[0];
}
