//==========================
//
// �o���b�h���� [bullet.cpp]
// Author: TEAM_2
//
//==========================

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "bullet.h"
#include "shadow.h"
#include "explosion.h"
#include "particle.h"

//*****************************
// �O���[�o���ϐ��錾
//*****************************
Bullet g_Bullet[MAX_BULLET];						// �\���̕ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// ���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_apTextureBullet = NULL;		// �e�N�X�`���̃|�C���^

//=========================
//�@�o���b�g����������
//=========================
void InitBullet(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X���擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_apTextureBullet);


	// �O���[�o���ϐ��̏�����
	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		g_Bullet[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCnt].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCnt].dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCnt].bUse = false;
		g_Bullet[nCnt].nLife = 10;
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	// ���_���̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos.x = g_Bullet[nCntBullet].pos.x - 3.0f;
		pVtx[0].pos.y = g_Bullet[nCntBullet].pos.y - 3.0f;
		pVtx[0].pos.z = g_Bullet[nCntBullet].pos.z;

		pVtx[1].pos.x = g_Bullet[nCntBullet].pos.x - 3.0f;
		pVtx[1].pos.y = g_Bullet[nCntBullet].pos.y + 3.0f;
		pVtx[1].pos.z = g_Bullet[nCntBullet].pos.z;

		pVtx[2].pos.x = g_Bullet[nCntBullet].pos.x + 3.0f;
		pVtx[2].pos.y = g_Bullet[nCntBullet].pos.y - 3.0f;
		pVtx[2].pos.z = g_Bullet[nCntBullet].pos.z;

		pVtx[3].pos.x = g_Bullet[nCntBullet].pos.x + 3.0f;
		pVtx[3].pos.y = g_Bullet[nCntBullet].pos.y + 3.0f;
		pVtx[3].pos.z = g_Bullet[nCntBullet].pos.z;

		// �e���_�̖@��(�x�N�g��)�̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);		// 1�ڂ̖@�����
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);		// 2�ڂ̖@�����
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);		// 3�ڂ̖@�����
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);		// 4�ڂ̖@�����

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

		pVtx += 4;
	}

	// �A�����b�N
	g_pVtxBuffBullet->Unlock();

}
//=========================
//�@�o���b�g�I������
//=========================
void UninitBullet(void)
{
	// �e�N�X�`���̔j��
	if (g_apTextureBullet != NULL)
	{
		g_apTextureBullet->Release();
		g_apTextureBullet = NULL;

	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

}
//=========================
//�@�o���b�g�X�V����
//=========================
void UpdateBullet(void)
{

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		if (g_Bullet[nCnt].bUse)
		{
			// ���W
			g_Bullet[nCnt].posOld = g_Bullet[nCnt].pos ;

			// �ʒu�̍X�V
			g_Bullet[nCnt].pos += g_Bullet[nCnt].move;

			// �e�̍��W�X�V�ݒ�
			SetPositionShadow(g_Bullet[nCnt].nIdxBullet, D3DXVECTOR3(g_Bullet[nCnt].pos.x, 0.0f, g_Bullet[nCnt].pos.z));

			// �̗͂����炷
			g_Bullet[nCnt].nLife--;

			if (g_Bullet[nCnt].nLife <= 0)
			{// �̗͂�0�ȉ��Ȃ�
				g_Bullet[nCnt].bUse = false;		// ���g�p
				SetParticle(D3DXVECTOR3(g_Bullet[nCnt].pos.x, g_Bullet[nCnt].pos.y + 10.0f, g_Bullet[nCnt].pos.z),D3DXCOLOR (1.0f,1.0f,0.0f,1.0f),15,PARTICLETYPE_BULLET);
				DeleteShadow(g_Bullet[nCnt].nIdxBullet);	// �e�̏���
			}
		}
	}
}

//=========================
//�@�o���b�g�`�揈��
//=========================
void DrawBullet(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans;

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		if (g_Bullet[nCnt].bUse == true)
		{// �g���Ă���Ƃ�

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Bullet[nCnt].mtxWorld);

			// �r���[�}�g���b�N�X��錾
			D3DXMATRIX mtxView;

			// �r���[�}�g���b�N�X�̎擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// �J�����̋t�s���ݒ�
			g_Bullet[nCnt].mtxWorld._11 = mtxView._11;
			g_Bullet[nCnt].mtxWorld._12 = mtxView._21;
			g_Bullet[nCnt].mtxWorld._13 = mtxView._31;
			g_Bullet[nCnt].mtxWorld._21 = mtxView._12;
			g_Bullet[nCnt].mtxWorld._22 = mtxView._22;
			g_Bullet[nCnt].mtxWorld._23 = mtxView._32;
			g_Bullet[nCnt].mtxWorld._31 = mtxView._13;
			g_Bullet[nCnt].mtxWorld._32 = mtxView._23;
			g_Bullet[nCnt].mtxWorld._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Bullet[nCnt].pos.x, g_Bullet[nCnt].pos.y, g_Bullet[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Bullet[nCnt].mtxWorld, &g_Bullet[nCnt].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Bullet[nCnt].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureBullet);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);

		}
	}

	// ���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}
//=========================
//�@�o���b�g�ݒ菈��
//=========================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 dir,int nLife,D3DXVECTOR3 move)
{
	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		if (!g_Bullet[nCnt].bUse)
		{// false��������
			g_Bullet[nCnt].bUse = true;	// �g�p����
			g_Bullet[nCnt].pos = pos;	// ���W
			g_Bullet[nCnt].dir = dir;	// �����x�N�g��
			g_Bullet[nCnt].move = move;
			g_Bullet[nCnt].nLife = nLife;
			g_Bullet[nCnt].nIdxBullet = SetShadow(D3DXVECTOR3(g_Bullet[nCnt].pos.x, 0.0f, g_Bullet[nCnt].pos.z), g_Bullet[nCnt].rot, D3DXVECTOR3(0.5f,0.0f,0.5f));

			break;
		}
	}
}
