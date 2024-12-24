//===============================
//
// �r���{�[�h���� [billboard.cpp]
// Author: TEAM_2
//
//===============================

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "billboard.h"
#include "input.h"
#include "shadow.h"

//*****************************
// �O���[�o���ϐ��錾
//*****************************
Billboard g_Billboard[MAX_BILLBOARD];				// �\���̕ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;	// ���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_apTextureBillboard[BILLBOARDTYPE_MAX] = {};		// �e�N�X�`���̃|�C���^

//=========================
//�@�r���{�[�h����������
//=========================
void InitBillboard(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < BILLBOARDTYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			BILLBOARD_TEXTURE[nCnt],
			&g_apTextureBillboard[nCnt]);
	}

	// �O���[�o���ϐ��̏�����
	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		g_Billboard[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���W
		g_Billboard[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �p�x
		g_Billboard[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ���
		g_Billboard[nCnt].dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �x�N�g��
		g_Billboard[nCnt].Type = BILLBOARDTYPE_FIRST;			// ���
		g_Billboard[nCnt].bUse = false;							// �g�p����
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	// ���_���̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos.x = g_Billboard[nCntBillboard].pos.x - 70.0f;
		pVtx[0].pos.y = g_Billboard[nCntBillboard].pos.y + 70.0f;
		pVtx[0].pos.z = g_Billboard[nCntBillboard].pos.z;  
														   
		pVtx[1].pos.x = g_Billboard[nCntBillboard].pos.x + 70.0f;
		pVtx[1].pos.y = g_Billboard[nCntBillboard].pos.y + 70.0f;
		pVtx[1].pos.z = g_Billboard[nCntBillboard].pos.z;  
														   
		pVtx[2].pos.x = g_Billboard[nCntBillboard].pos.x - 70.0f;
		pVtx[2].pos.y = g_Billboard[nCntBillboard].pos.y - 70.0f;
		pVtx[2].pos.z = g_Billboard[nCntBillboard].pos.z;  
														   
		pVtx[3].pos.x = g_Billboard[nCntBillboard].pos.x + 70.0f;
		pVtx[3].pos.y = g_Billboard[nCntBillboard].pos.y - 70.0f;
		pVtx[3].pos.z = g_Billboard[nCntBillboard].pos.z;

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

		// ���_���̃|�C���^��i�߂�
		pVtx += 4;
	}

	// �A�����b�N
	g_pVtxBuffBillboard->Unlock();

}
//=========================
//�@�r���{�[�h�I������
//=========================
void UninitBillboard(void)
{
	// �e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < BILLBOARDTYPE_MAX; nCnt++)
	{
		if (g_apTextureBillboard[nCnt] != NULL)
		{
			g_apTextureBillboard[nCnt]->Release();
			g_apTextureBillboard[nCnt] = NULL;

		}
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffBillboard != NULL)
	{			 
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}

}
//=========================
//�@�r���{�[�h�X�V����
//=========================
void UpdateBillboard(void)
{
}
//=========================
//�@�r���{�[�h�`�揈��
//=========================
void DrawBillboard(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans;

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		if (g_Billboard[nCnt].bUse)
		{// �g���Ă���Ƃ�

			if (g_Billboard[nCnt].Type == BILLBOARDTYPE_FIRST)
			{
				// Z�e�X�g
				pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
				pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			}

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Billboard[nCnt].mtxWorld);

			// �r���[�}�g���b�N�X��錾
			D3DXMATRIX mtxView;

			// �r���[�}�g���b�N�X�̎擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// �J�����̋t�s���ݒ�
			g_Billboard[nCnt].mtxWorld._11 = mtxView._11;
			g_Billboard[nCnt].mtxWorld._12 = mtxView._21;
			g_Billboard[nCnt].mtxWorld._13 = mtxView._31;
			g_Billboard[nCnt].mtxWorld._21 = mtxView._12;
			g_Billboard[nCnt].mtxWorld._22 = mtxView._22;
			g_Billboard[nCnt].mtxWorld._23 = mtxView._32;
			g_Billboard[nCnt].mtxWorld._31 = mtxView._13;
			g_Billboard[nCnt].mtxWorld._32 = mtxView._23;
			g_Billboard[nCnt].mtxWorld._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Billboard[nCnt].pos.x, g_Billboard[nCnt].pos.y, g_Billboard[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Billboard[nCnt].mtxWorld, &g_Billboard[nCnt].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Billboard[nCnt].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureBillboard[g_Billboard[nCnt].Type]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);

			if (g_Billboard[nCnt].Type == BILLBOARDTYPE_FIRST)
			{
				// Z�e�X�g
				pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
				pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
			}
		}
	}


	// ���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//=========================
//�@�r���{�[�h�ݒ菈��
//=========================
void SetBillboard(D3DXVECTOR3 pos, BILLBOARDTYPE Type,D3DXVECTOR3 rot)
{
	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		if (!g_Billboard[nCnt].bUse)
		{// false��������

			g_Billboard[nCnt].pos = pos;	// ���W
			g_Billboard[nCnt].Type = Type;	// ���
			g_Billboard[nCnt].rot = rot;	// �p�x
			g_Billboard[nCnt].bUse = true;	// �g�p����
			break;
		}
	}
}
