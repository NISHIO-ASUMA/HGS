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
bool bItemGet1 = false; //�A�C�e���擾����
bool bItemGet2 = false; //�A�C�e���擾����
bool bItemGet3 = false; //�A�C�e���擾����
bool bItemGet4 = false; //�A�C�e���擾����

bool bGet;
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
	bGet = false;

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

		// ���a���Z�o����ϐ�
		D3DXVECTOR3 PlayerPos(15.0f, 0.0f, 15.0f);
		D3DXVECTOR3 ItemPos(15.0f, 0.0f, 15.0f);

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
			if (KeyboardTrigger(DIK_RETURN) || JoyPadTrigger(JOYKEY_A))
			{// ENTER ��������B�{�^���������ꂽ
				// �q�b�g����
				HitItem(nCnt, 1);

				bGet = true;

				//�G���A1
				if (bGet && g_Item[nCnt].Type == ITEMTYPE_SPRING)
				{
					g_Item[ITEMTYPE_SUMMER].bUse = false;
					g_Item[ITEMTYPE_AUTUMN].bUse = false;
					g_Item[ITEMTYPE_WINTER].bUse = false;

					g_bItem[ITEMTYPE_SPRING] = true;

					bGet = false;
				}
				else if (bGet && g_Item[nCnt].Type == ITEMTYPE_SUMMER)
				{
					g_Item[ITEMTYPE_SPRING].bUse = false;
					g_Item[ITEMTYPE_AUTUMN].bUse = false;
					g_Item[ITEMTYPE_WINTER].bUse = false;

					g_bItem[ITEMTYPE_SUMMER] = true;

					bGet = false;
				}
				else if (bGet && g_Item[nCnt].Type == ITEMTYPE_AUTUMN)
				{
					g_Item[ITEMTYPE_SPRING].bUse = false;
					g_Item[ITEMTYPE_SUMMER].bUse = false;
					g_Item[ITEMTYPE_WINTER].bUse = false;

					g_bItem[ITEMTYPE_AUTUMN] = true;

					bGet = false;
				}
				else if (bGet && g_Item[nCnt].Type == ITEMTYPE_WINTER)
				{
					g_Item[ITEMTYPE_SPRING].bUse = false;
					g_Item[ITEMTYPE_SUMMER].bUse = false;
					g_Item[ITEMTYPE_AUTUMN].bUse = false;

					g_bItem[ITEMTYPE_WINTER] = true;

					bGet = false;
				}

				//�G���A2
				if (bGet && g_Item[nCnt].Type == ITEMTYPE_SHOP)
				{
					g_Item[ITEMTYPE_PARK].bUse = false;
					g_Item[ITEMTYPE_SCHOOL].bUse = false;

					g_bItem[ITEMTYPE_SHOP] = true;

					bGet = false;
				}
				else if (bGet && g_Item[nCnt].Type == ITEMTYPE_PARK)
				{
					g_Item[ITEMTYPE_SHOP].bUse = false;
					g_Item[ITEMTYPE_SCHOOL].bUse = false;

					g_bItem[ITEMTYPE_PARK] = true;

					bGet = false;
				}
				else if (bGet && g_Item[nCnt].Type == ITEMTYPE_SCHOOL)
				{
					g_Item[ITEMTYPE_SHOP].bUse = false;
					g_Item[ITEMTYPE_PARK].bUse = false;

					g_bItem[ITEMTYPE_SCHOOL] = true;

					bGet = false;
				}

				//�G���A3
				if (bGet && g_Item[nCnt].Type == ITEMTYPE_FOOD1)
				{
					g_Item[ITEMTYPE_FOOD2].bUse = false;
					g_Item[ITEMTYPE_FOOD3].bUse = false;
					g_Item[ITEMTYPE_FOOD4].bUse = false;

					g_bItem[ITEMTYPE_FOOD1] = true;

					bGet = false;
				}
				else if (bGet && g_Item[nCnt].Type == ITEMTYPE_FOOD2)
				{
					g_Item[ITEMTYPE_FOOD1].bUse = false;
					g_Item[ITEMTYPE_FOOD3].bUse = false;
					g_Item[ITEMTYPE_FOOD4].bUse = false;

					g_bItem[ITEMTYPE_FOOD2] = true;

					bGet = false;
				}
				else if (bGet && g_Item[nCnt].Type == ITEMTYPE_FOOD3)
				{
					g_Item[ITEMTYPE_FOOD1].bUse = false;
					g_Item[ITEMTYPE_FOOD2].bUse = false;
					g_Item[ITEMTYPE_FOOD4].bUse = false;

					g_bItem[ITEMTYPE_FOOD3] = true;

					bGet = false;
				}
				else if (bGet && g_Item[nCnt].Type == ITEMTYPE_FOOD4)
				{
					g_Item[ITEMTYPE_FOOD1].bUse = false;
					g_Item[ITEMTYPE_FOOD2].bUse = false;
					g_Item[ITEMTYPE_FOOD3].bUse = false;

					g_bItem[ITEMTYPE_FOOD4] = true;

					bGet = false;
				}

				//�G���A4
				if (bGet && g_Item[nCnt].Type == ITEMTYPE_TALK)
				{
					g_Item[ITEMTYPE_KIKAKU].bUse = false;
					g_Item[ITEMTYPE_KARISUMA].bUse = false;
					g_Item[ITEMTYPE_HYO].bUse = false;

					g_bItem[ITEMTYPE_TALK] = true;

					bGet = false;
				}
				else if (bGet && g_Item[nCnt].Type == ITEMTYPE_KIKAKU)
				{
					g_Item[ITEMTYPE_TALK].bUse = false;
					g_Item[ITEMTYPE_KARISUMA].bUse = false;
					g_Item[ITEMTYPE_HYO].bUse = false;

					g_bItem[ITEMTYPE_KIKAKU] = true;

					bGet = false;
				}
				else if (bGet && g_Item[nCnt].Type == ITEMTYPE_KARISUMA)
				{
					g_Item[ITEMTYPE_TALK].bUse = false;
					g_Item[ITEMTYPE_KIKAKU].bUse = false;
					g_Item[ITEMTYPE_HYO].bUse = false;

					g_bItem[ITEMTYPE_KARISUMA] = true;

					bGet = false;
				}
				else if (bGet && g_Item[nCnt].Type == ITEMTYPE_HYO)
				{
					g_Item[ITEMTYPE_TALK].bUse = false;
					g_Item[ITEMTYPE_KARISUMA].bUse = false;
					g_Item[ITEMTYPE_KIKAKU].bUse = false;

					g_bItem[ITEMTYPE_HYO] = true;

					bGet = false;
				}

			}
		}

		//�G���A1
		if (g_Item[nCnt].Type == ITEMTYPE_SPRING && g_Item[nCnt].bUse == false)
		{
			bItemGet1 = true;
		}
		else if (g_Item[nCnt].Type == ITEMTYPE_SUMMER && g_Item[nCnt].bUse == false)
		{
			bItemGet1 = true;
		}
		else if (g_Item[nCnt].Type == ITEMTYPE_AUTUMN && g_Item[nCnt].bUse == false)
		{
			bItemGet1 = true;
		}
		else if (g_Item[nCnt].Type == ITEMTYPE_WINTER && g_Item[nCnt].bUse == false)
		{
			bItemGet1 = true;
		}

		//�G���A2
		if (g_Item[nCnt].Type == ITEMTYPE_SHOP && g_Item[nCnt].bUse == false)
		{
			bItemGet2 = true;
		}
		else if (g_Item[nCnt].Type == ITEMTYPE_PARK && g_Item[nCnt].bUse == false)
		{
			bItemGet2 = true;
		}
		else if (g_Item[nCnt].Type == ITEMTYPE_SCHOOL && g_Item[nCnt].bUse == false)
		{
			bItemGet2 = true;
		}

		//�G���A3
		if (g_Item[nCnt].Type == ITEMTYPE_FOOD1 && g_Item[nCnt].bUse == false)
		{
			bItemGet3 = true;
		}
		else if (g_Item[nCnt].Type == ITEMTYPE_FOOD2 && g_Item[nCnt].bUse == false)
		{
			bItemGet3 = true;
		}
		else if (g_Item[nCnt].Type == ITEMTYPE_FOOD3 && g_Item[nCnt].bUse == false)
		{
			bItemGet3 = true;
		}
		else if (g_Item[nCnt].Type == ITEMTYPE_FOOD4 && g_Item[nCnt].bUse == false)
		{
			bItemGet3 = true;
		}

		//�G���A4
		if (g_Item[nCnt].Type == ITEMTYPE_TALK && g_Item[nCnt].bUse == false)
		{
			bItemGet4 = true;
		}
		else if (g_Item[nCnt].Type == ITEMTYPE_KIKAKU && g_Item[nCnt].bUse == false)
		{
			bItemGet4 = true;
		}
		else if (g_Item[nCnt].Type == ITEMTYPE_KARISUMA && g_Item[nCnt].bUse == false)
		{
			bItemGet4 = true;
		}
		else if (g_Item[nCnt].Type == ITEMTYPE_HYO && g_Item[nCnt].bUse == false)
		{
			bItemGet4 = true;
		}

		// ��]
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

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		// Life��0�ȉ��̎�
		if (g_Item[nCntItem].nLife <= 0)
		{
			//	���g�p����
			g_Item[nCntItem].bUse = false;

			// �e������
			ShadowFalse(g_Item[nCntItem].nIdxshadow);

			// �擾������Ԃɂ���
			g_bItem[g_Item[nCntItem].Type] = true;
		}
	}
}
//============================
// ���U���g�ւ̔ԍ���n��
//============================
int GetResultNumber()
{
	// ������A�C�e���ɂ���ă��U���g�̃e�N�X�`����ύX�����鏈��
	if (g_bItem[ITEMTYPE_SPRING])
	{// �t���l��
		if (g_bItem[ITEMTYPE_SHOP])
		{// �X
			if (g_bItem[ITEMTYPE_FOOD1])
			{// �c�q���l��
				if (g_bItem[ITEMTYPE_HYO])
				{// �\��
					// �ԍ���Ԃ�
					nGetNumber = 2;
				}
			}
			else if (g_bItem[ITEMTYPE_FOOD3])
			{// �T�c�}�C��
				// �ԍ���Ԃ�
				nGetNumber = 5;
			}
		}
		else
		{// �������ɓ���Ȃ��Ƃ�
			// �ԍ���Ԃ�
			nGetNumber = 5;
		}

	}
	else if (g_bItem[ITEMTYPE_SUMMER])
	{// �Ă��l��
		if (g_bItem[ITEMTYPE_PARK])
		{// ����
			if (g_bItem[ITEMTYPE_FOOD2])
			{// �X�C�J���l��
				if (g_bItem[ITEMTYPE_KARISUMA])
				{
					// �ԍ���Ԃ�
					nGetNumber = 2;
				}
			}
			else if (g_bItem[ITEMTYPE_FOOD4])
			{// �݂���
				// �ԍ���Ԃ�
				nGetNumber = 5;
			}

		}
		else if (g_bItem[ITEMTYPE_SHOP])
		{// �X
			if (g_bItem[ITEMTYPE_FOOD2])
			{// �X�C�J���l��
				if (g_bItem[ITEMTYPE_TALK])
				{
					// �ԍ���Ԃ�
					nGetNumber = 3;
				}
			}
		}

	}
	else if (g_bItem[ITEMTYPE_AUTUMN])
	{// �H���l��
		if (g_bItem[ITEMTYPE_SCHOOL])
		{// �w�Z
			if (g_bItem[ITEMTYPE_FOOD3])
			{// �T�c�}�C�����l��
				if (g_bItem[ITEMTYPE_KIKAKU])
				{
					// �ԍ���Ԃ�
					nGetNumber = 2;
				}
			}
			else if (g_bItem[ITEMTYPE_FOOD1])
			{// �c�q
				// �ԍ���Ԃ�
				nGetNumber = 5;
			}
		}
		else if (g_bItem[ITEMTYPE_SHOP])
		{// �X
			if (g_bItem[ITEMTYPE_FOOD3])
			{// �T�c�}�C�����l��
				if (g_bItem[ITEMTYPE_TALK])
				{
					// �ԍ���Ԃ�
					nGetNumber = 0;
				}
			}
		}
	}
	else if (g_bItem[ITEMTYPE_WINTER])
	{// �~���l��
		if (g_bItem[ITEMTYPE_SCHOOL])
		{// �w�Z
			if (g_bItem[ITEMTYPE_FOOD4])
			{// �݂�����l��
				if (g_bItem[ITEMTYPE_TALK])
				{// �b�p
					// �ԍ���Ԃ�
					nGetNumber = 2;
				}
			}
			else if (g_bItem[ITEMTYPE_FOOD2])
			{// �X�C�J
				// �ԍ���Ԃ�
				nGetNumber = 5;
			}
		}
		else if (g_bItem[ITEMTYPE_PARK])
		{// ����
			if (g_bItem[ITEMTYPE_FOOD1] || g_bItem[ITEMTYPE_HYO])
			{// �c�q �܂��� �\����
				// �ԍ���Ԃ�
				nGetNumber = 1;
			}
		}
	}

	return nGetNumber;
}
//============================
// �擾����
//============================
Item* GetItem()
{
	return &g_Item[0];
}
bool ItemGet1(void)
{
	return bItemGet1;
}
bool ItemGet2(void)
{
	return bItemGet2;
}
bool ItemGet3(void)
{
	return bItemGet3;
}
bool ItemGet4(void)
{
	return bItemGet4;
}
