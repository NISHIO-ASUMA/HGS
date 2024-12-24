//=================================
//
// �G�̏��� [enemy.cpp]
// Author: TEAM_2
//	
//=================================

//********************************
// �C���N���[�h�t�@�C���錾
//********************************
#include "enemy.h"
#include "player.h"
#include "particle.h"
#include <stdio.h>
#include "effect.h"
#include "score.h"
#include "block.h"
#include "shadow.h"
#include "sound.h"
#include "meshwall.h"
#include "fade.h"

//********************************
// �O���[�o���ϐ��錾
//********************************
Enemy g_Enemy[MAX_ENEMY];								// �G�̍\���̏��

int g_nNumEnemy;										// �G�����擾����p�̕ϐ�
int g_FireCount;										// �t�@�C���J�E���g
bool g_bFinish;											// �e�L�X�g�I������
int g_nCntJumpCount;									// �W�����v�J�E���g

//================================
// �G�̏���������
//================================
void InitEnemy()
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	

	// �O���[�o���ϐ��̏�����-----------------------------
	g_nNumEnemy = 0;
	g_FireCount = 0;
	g_bFinish = false;
	g_nCntJumpCount = 0;
	//-----------------------------------------------------

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		g_Enemy[nCnt].bUse = false;							 // ���g�p����
		g_Enemy[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	 // ���W
		g_Enemy[nCnt].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// �ߋ��̍��W
		g_Enemy[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	 // �ړ���
		g_Enemy[nCnt].nLife = 0;							 // �̗�
		g_Enemy[nCnt].State = ENEMYSTATE_NORMAL;			 // ���
		g_Enemy[nCnt].nCntState = 0;						 // ��ԊǗ��J�E���^�[
		g_Enemy[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	 // �p�x
		g_Enemy[nCnt].nType = ENEMYTYPE_FIRE;				 // ���

		for (int nCntEn = 0; nCntEn < ENEMYTYPE_MAX; nCntEn++)
		{
			// X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(ENEMY_MODEL[nCntEn],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Enemy[nCnt].aModel[nCntEn].pBuffMatEnemy,
				NULL,
				&g_Enemy[nCnt].aModel[nCntEn].dwNumMatEnemy,
				&g_Enemy[nCnt].aModel[nCntEn].pMeshEnemy);

			// ���[�J���ϐ��錾-----------------------------
			int nNumVtx;		// ���_��
			DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
			BYTE* pVtxBuff;		// ���_�o�b�t�@�̃|�C���^
			//----------------------------------------------

			// ���_���̎擾
			nNumVtx = g_Enemy[nCnt].aModel[nCntEn].pMeshEnemy->GetNumVertices();

			// ���_�̃T�C�Y���擾
			sizeFVF = D3DXGetFVFVertexSize(g_Enemy[nCnt].aModel[nCntEn].pMeshEnemy->GetFVF());

			// ���_�o�b�t�@�����b�N
			g_Enemy[nCnt].aModel[nCntEn].pMeshEnemy->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			// ���_������
			for (int nCntEnemy = 0; nCntEnemy < nNumVtx; nCntEnemy++)
			{
				// ���_���W�̑��
				D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;

				// ���_���W�̔�r
				if (Vtx.x > g_Enemy[nCnt].Vtxmax.x)
				{// x���ő�l���傫��������
					// ���
					g_Enemy[nCnt].Vtxmax.x = Vtx.x;
				}
				if (Vtx.y > g_Enemy[nCnt].Vtxmax.y)
				{// y���ő�l���傫��������
					// ���
					g_Enemy[nCnt].Vtxmax.y = Vtx.y;
				}
				if (Vtx.z > g_Enemy[nCnt].Vtxmax.z)
				{// z���ő�l���傫��������
					// ���
					g_Enemy[nCnt].Vtxmax.z = Vtx.z;
				}

				if (Vtx.x < g_Enemy[nCnt].Vtxmin.x)
				{// x���ŏ��l��菬����������
					// ���
					g_Enemy[nCnt].Vtxmin.x = Vtx.x;
				}
				if (Vtx.y < g_Enemy[nCnt].Vtxmin.y)
				{// y���ŏ��l��菬����������
					// ���
					g_Enemy[nCnt].Vtxmin.y = Vtx.y;
				}
				if (Vtx.z < g_Enemy[nCnt].Vtxmin.z)
				{// z���ŏ��l��菬����������
					// ���
					g_Enemy[nCnt].Vtxmin.z = Vtx.z;
				}

				// ���_�t�H�[�}�b�g�̃T�C�Y���i�߂�
				pVtxBuff += sizeFVF;
			}

			// �T�C�Y��������
			g_Enemy[nCnt].size.x = g_Enemy[nCnt].Vtxmax.x - g_Enemy[nCnt].Vtxmin.x;	// size��x
			g_Enemy[nCnt].size.y = g_Enemy[nCnt].Vtxmax.y - g_Enemy[nCnt].Vtxmin.y;	// size��y
			g_Enemy[nCnt].size.z = g_Enemy[nCnt].Vtxmax.z - g_Enemy[nCnt].Vtxmin.z;	// size��z

			// �A�����b�N
			g_Enemy[nCnt].aModel[nCntEn].pMeshEnemy->UnlockVertexBuffer();

			// �}�e���A���f�[�^�ւ̃|�C���^
			D3DXMATERIAL* pMat;

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Enemy[nCnt].aModel[nCntEn].pBuffMatEnemy->GetBufferPointer();

			// �}�e���A����������
			for (int nCntMat = 0; nCntMat < (int)g_Enemy[nCnt].aModel[nCntEn].dwNumMatEnemy; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					// �e�N�X�`���̓ǂݍ���
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_Enemy[nCnt].aModel[nCntEn].pTexture[nCntMat]);
				}
			}
		}
	}
}
//===================================
// �G�̏I������
//===================================
void UninitEnemy(void)
{
	// ���y���~
	StopSound();

	// �e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		for (int nCntEn = 0; nCntEn < ENEMYTYPE_MAX; nCntEn++)
		{
			for (int nCntMat = 0; nCntMat < (int)g_Enemy[nCnt].aModel[nCntEn].dwNumMatEnemy; nCntMat++)
			{
				if (g_Enemy[nCnt].aModel[nCntEn].pTexture[nCntMat] != NULL)
				{
					g_Enemy[nCnt].aModel[nCntEn].pTexture[nCntMat]->Release();
					g_Enemy[nCnt].aModel[nCntEn].pTexture[nCntMat] = NULL;
				}
			}
		}
	}

	// ���b�V���̔j��,�}�e���A���̔j��
	for (int nCntEn = 0; nCntEn < MAX_ENEMY; nCntEn++)
	{// ���f���ő吔
		for (int nCnt = 0; nCnt < ENEMYTYPE_MAX; nCnt++)
		{
			if (g_Enemy[nCntEn].aModel[nCnt].pMeshEnemy != NULL)
			{
				g_Enemy[nCntEn].aModel[nCnt].pMeshEnemy->Release();
				g_Enemy[nCntEn].aModel[nCnt].pMeshEnemy = NULL;
			}

			if (g_Enemy[nCntEn].aModel[nCnt].pBuffMatEnemy != NULL)
			{
				g_Enemy[nCntEn].aModel[nCnt].pBuffMatEnemy->Release();
				g_Enemy[nCntEn].aModel[nCnt].pBuffMatEnemy = NULL;
			}
		}

	}
}
//====================================
// �G�̍X�V����
//====================================
void UpdateEnemy(void)
{
	// ���݂̃��[�h�̎擾
	MODE nMode = GetMode();

	// �v���C���[�̎擾
	PLAYER* pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{// �G�̐�

		if (!g_Enemy[nCnt].bUse)
		{// ���g�p�Ȃ�
			continue;
		}

		if (nMode == MODE_GAME)
		{// ���[�h���Q�[���Ȃ�
			// �e�̍��W�X�V�ݒ�
			SetPositionShadow(g_Enemy[nCnt].nIdxEnemy, D3DXVECTOR3(g_Enemy[nCnt].pos.x, 0.0f, g_Enemy[nCnt].pos.z));

			// ��ނ�ۑ�
			int nType = g_Enemy[nCnt].nType;

			// ���a���Z�o����ϐ�
			D3DXVECTOR3 PRadiusPos(50.0f, 0.0f, 50.0f);
			D3DXVECTOR3 ERadiusPos(50.0f, 0.0f, 50.0f);

			// ���a���Z�o����ϐ�2
			D3DXVECTOR3 Pradius(6.0f, 0.0f, 6.0f);
			D3DXVECTOR3 Eradius(6.0f, 0.0f, 6.0f);

			// ���a���Z�o����ϐ�3
			D3DXVECTOR3 radiusPlayer(10.0f, 0.0f, 10.0f);
			D3DXVECTOR3 radiusEnemy(10.0f, 0.0f, 10.0f);

			// ���x�v�Z�p�̕ϐ�
			float fspeed = 0.0f;

			// �v���C���[�̈ʒu���擾
			D3DXVECTOR3 playerPos = GetPlayer()->pos;

			// �v���C���[�Ƃ̋����̍������߂�
			D3DXVECTOR3 diff = playerPos - g_Enemy[nCnt].pos;

			// �p�x�̎Z�o
			float fAngle = atan2f(diff.x, diff.z);

			// �͈͌v�Z===============================================
			// ���������߂�
			float fDisX = (playerPos.x - g_Enemy[nCnt].pos.x);
			float fDisY = (playerPos.y - g_Enemy[nCnt].pos.y);
			float fDisZ = (playerPos.z - g_Enemy[nCnt].pos.z);

			// 2�̔��a
			float fRadX = (PRadiusPos.x + ERadiusPos.x);
			float fRadY = (PRadiusPos.y + ERadiusPos.y);
			float fRadZ = (PRadiusPos.z + ERadiusPos.z);
			//========================================================

			// �����蔻��p===========================================
			// ���������߂�
			float fdisX = (pPlayer->pos.x - g_Enemy[nCnt].pos.x);
			float fdisY = (pPlayer->pos.y - g_Enemy[nCnt].pos.y);
			float fdisZ = (pPlayer->pos.z - g_Enemy[nCnt].pos.z);

			// 2�̔��a
			float fradX = (Pradius.x + Eradius.x);
			float fradY = (Pradius.y + Eradius.y);
			float fradZ = (Pradius.z + Eradius.z);
			//=========================================================

			// �E��̓����蔻��p==================================
			// ���������߂�
			float fRightX = (pPlayer->aModel[4].mtxWorld._41 - g_Enemy[nCnt].pos.x);
			float fRightY = (pPlayer->aModel[4].mtxWorld._42 - g_Enemy[nCnt].pos.y);
			float fRightZ = (pPlayer->aModel[4].mtxWorld._43 - g_Enemy[nCnt].pos.z);

			// 2�̔��a
			float fX = (radiusPlayer.x + radiusEnemy.x);
			//================================================

#ifdef _DEBUG
			// �����蔻��m�F�p
			SetEffect(D3DXVECTOR3(pPlayer->aModel[4].mtxWorld._41, pPlayer->aModel[4].mtxWorld._42, pPlayer->aModel[4].mtxWorld._43), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), 10);
#endif
			switch (g_Enemy[nCnt].State)
			{
			case ENEMYSTATE_NORMAL:

				// �G�̊p�x
				g_Enemy[nCnt].rot.y = fAngle + D3DX_PI;

				// �e�^�C�v���Ƃ̒ǔ��X�s�[�h--------------------------------------
				if (g_Enemy[nCnt].nType == ENEMYTYPE_FIRE)
				{// ���ޖڂ̓G�Ȃ�
					fspeed = (float)(rand() % 3) + 0.01f;
				}
				else if (g_Enemy[nCnt].nType == ENEMYTYPE_NOFIRE)
				{// ���ޖڂ̓G�Ȃ�
					fspeed = (float)(rand() % 3) + 0.01f;
				}
				else if (g_Enemy[nCnt].nType == ENEMYTYPE_PURA)
				{// �O��ޖڂ̓G�Ȃ�
					fspeed = (float)(rand() % 3) + 0.03f;
				}
				else if (g_Enemy[nCnt].nType == ENEMYTYPE_KAN)
				{// �l��ޖڂ̓G�Ȃ�
					fspeed = (float)(rand() % 3) + 0.04f;
				}
				else if (g_Enemy[nCnt].nType == ENEMYTYPE_RECYCLE)
				{// �܎�ޖڂ̓G�Ȃ�
					fspeed = (float)(rand() % 3) + 0.06f;
				}
				//-------------------------------------------------------------------

				// �ǔ��V�X�e��
				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX + fRadY + fRadZ) * (fRadX + fRadY + fRadZ))
				{// �͈͓��ɂ͂������Ƃ�

					// �ړ��ʂ̍X�V
					g_Enemy[nCnt].move.x = sinf(g_Enemy[nCnt].rot.y + D3DX_PI) * fspeed;
					g_Enemy[nCnt].move.z = cosf(g_Enemy[nCnt].rot.y + D3DX_PI) * fspeed;
				}

				// �v���C���[���͂����Ƃ΂�
				if ((fdisX * fdisX) + (fdisY * fdisY) + (fdisZ * fdisZ) <= (fradX + fradY + fradZ) * (fradX + fradY + fradZ))
				{// �͈͓��ɂ͂������Ƃ�
					// ������΂�
					pPlayer->move.x = sinf(g_Enemy[nCnt].rot.y + D3DX_PI) * 25.0f;
					pPlayer->move.y = 5.0f;
					pPlayer->move.z = cosf(g_Enemy[nCnt].rot.y + D3DX_PI) * 25.0f;

					if (pPlayer->Pcon == PLAYERCONDITION_NORMAL)
					{// �v���C���[�̗̑͂����炷
						
						//DamageFade(MODE_DAMAGEFADE);
						HitPlayer(1);

						// ���y�Đ�
						PlaySound(SOUND_LABLE_PLAYERDAMAGE);
					}
				}

				//  �G���͂����Ƃ΂���������ꂽ��
				if ((fRightX * fRightX) + (fRightY * fRightY) + (fRightZ * fRightZ) <= (fX + fX) * (fX + fX))
				{
					if (g_Enemy[nCnt].State == ENEMYSTATE_NORMAL && pPlayer->state == PLAYERSTATE_ACTION)
					{// �U�����[�V����
						// �E��ɓ������Ă�����
						HitEnemy(nCnt, 2);

						// ���y�Đ�
						PlaySound(SOUND_LABLE_DAMAGESE);

						if (g_Enemy[nCnt].State == ENEMYSTATE_DAMAGE)
						{
							// �G�𐁂���΂�
							g_Enemy[nCnt].move.x = sinf(pPlayer->rot.y + D3DX_PI) * 70.0f;
							g_Enemy[nCnt].move.y = 8.0f;
							g_Enemy[nCnt].move.z = cosf(pPlayer->rot.y + D3DX_PI) * 70.0f;

							// �ʒu�X�V
							g_Enemy[nCnt].pos.x += g_Enemy[nCnt].move.x;
							g_Enemy[nCnt].pos.z += g_Enemy[nCnt].move.z;

						}
					}
				}

				break;

			case ENEMYSTATE_DAMAGE:
				// ��ԊǗ��J�E���^�[���f�N�������g����
				g_Enemy[nCnt].nCntState--;

				if (g_Enemy[nCnt].nCntState <= 0)
				{// �J�E���^�[��0�ȉ��ɂȂ�����
					// �ʏ��Ԃɖ߂�
					g_Enemy[nCnt].State = ENEMYSTATE_NORMAL;
				}

				break;

			default:
				break;
			}

			// �O��̈ʒu��ۑ�
			g_Enemy[nCnt].posOld = g_Enemy[nCnt].pos;

			// �ʒu�X�V
			if (g_Enemy[nCnt].State == ENEMYSTATE_NORMAL)
			{
				g_Enemy[nCnt].pos.x += g_Enemy[nCnt].move.x;
				g_Enemy[nCnt].pos.z += g_Enemy[nCnt].move.z;

			}
			g_Enemy[nCnt].pos.y += g_Enemy[nCnt].move.y;
		}

		// ���b�V���Ƃ̓����蔻��
		CollisionEnemyToWall(nCnt);
	}

	// �����蔻��
	CollisionBlock();
}
//====================================
// �G�̕`�揈��
//====================================
void DrawEnemy(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans;

	// ���݂̃}�e���A����ۑ�
	D3DMATERIAL9 matDef;

	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL* pMat;

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		// �^�C�v��ۑ�
		int nType = g_Enemy[nCnt].nType;

		if (!g_Enemy[nCnt].bUse)
		{// ���g�p��ԂȂ�
			continue;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Enemy[nCnt].mtxWorld);

		// �����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nCnt].rot.y, g_Enemy[nCnt].rot.x, g_Enemy[nCnt].rot.z);
		D3DXMatrixMultiply(&g_Enemy[nCnt].mtxWorld, &g_Enemy[nCnt].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Enemy[nCnt].pos.x, g_Enemy[nCnt].pos.y, g_Enemy[nCnt].pos.z);
		D3DXMatrixMultiply(&g_Enemy[nCnt].mtxWorld, &g_Enemy[nCnt].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCnt].mtxWorld);

		// ���݂̃}�g���b�N�X�̎擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A����������
		for (int nCntMat = 0; nCntMat < (int)g_Enemy[nCnt].aModel[nType].dwNumMatEnemy; nCntMat++)
		{
			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Enemy[nCnt].aModel[nType].pBuffMatEnemy->GetBufferPointer();

			// �}�e���A��
			D3DXMATERIAL mat;

			switch (g_Enemy[nCnt].State)
			{
			case ENEMYSTATE_NORMAL:
				// �}�e���A���ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				break;

			case ENEMYSTATE_DAMAGE:

				mat = pMat[nCntMat];

				mat.MatD3D.Diffuse.r = 1.0f;
				mat.MatD3D.Diffuse.g = 0.0f;
				mat.MatD3D.Diffuse.b = 0.0f;
				mat.MatD3D.Diffuse.a = 1.0f;

				// �}�e���A���ݒ�
				pDevice->SetMaterial(&mat.MatD3D);

				break;
			}

			// �e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_Enemy[nCnt].aModel[nType].pTexture[nCntMat]);

			// �u���b�N(�p�[�c)�̕`��
			g_Enemy[nCnt].aModel[nType].pMeshEnemy->DrawSubset(nCntMat);
		}

		// �}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}

#ifdef _DEBUG
	// �G�̑����\��
	DrawEnemySet(g_nNumEnemy);
#endif

}
//====================================
// �G�̐ݒ菈��
//====================================
void SetEnemy(ENEMYTYPE nType, D3DXVECTOR3 pos)
{
	for (int nCnt1 = 0; nCnt1 < MAX_ENEMY; nCnt1++)
	{
		if (!g_Enemy[nCnt1].bUse)
		{
			// ���g�p�Ȃ�
			g_Enemy[nCnt1].pos = pos;								// ���W
			g_Enemy[nCnt1].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ���
			g_Enemy[nCnt1].nType = nType;							// ���
			g_Enemy[nCnt1].bUse = true;								// �g�p����
			g_Enemy[nCnt1].nIdxEnemy = SetShadow(D3DXVECTOR3(g_Enemy[nCnt1].pos.x, 0.0f, g_Enemy[nCnt1].pos.z), g_Enemy[nCnt1].rot, D3DXVECTOR3(0.5f, 0.0f, 0.5f));

			// �G�����J�E���g
			g_nNumEnemy++;					

			break;
		}
	}
}
//====================================
// �G�̑����̒l��Ԃ�
//====================================
int GetNumEnemy()
{
	return g_nNumEnemy;
}
//====================================
// �G�̃q�b�g����
//====================================
void HitEnemy(int nCntEnemy,int nDamage)
{	
	// ���݂̃��[�h�̎擾
	MODE nMode = GetMode();

	// �_���[�W�󂯂���̗͌��炷
	g_Enemy[nCntEnemy].nLife -= nDamage;		

	if (g_Enemy[nCntEnemy].nLife <= 0)
	{// �̗͂�0�ȉ��Ȃ�
		// ���g�p���
		g_Enemy[nCntEnemy].bUse = false;

		// �e�̏���
		DeleteShadow(g_Enemy[nCntEnemy].nIdxEnemy);

		// �p�[�e�B�N��
		SetParticle(g_Enemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.7f), 20, PARTICLETYPE_ENEMY);

		// �G�̑������f�N�������g
		g_nNumEnemy--;
	}
	else
	{
		// �p�[�e�B�N��
		SetParticle(g_Enemy[nCntEnemy].pos, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 15, PARTICLETYPE_ENEMY);

		g_Enemy[nCntEnemy].State = ENEMYSTATE_DAMAGE;	// �_���[�W��ԂɕύX
		g_Enemy[nCntEnemy].nCntState = 10;				// �_���[�W��Ԃ̎���
	}
}
//==========================
// �G�̎擾
//==========================
Enemy* GetEnemy()
{
	return &g_Enemy[0];
}
// TODO : �e�L�X�g��肽��������ǂ���