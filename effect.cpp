//==========================
//
// �G�t�F�N�g���� [effect.cpp]
// Author: TEAM_2
//
//==========================

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "effect.h"

//***************************
// �O���[�o���ϐ��錾
//***************************
Effect g_Effect[MAX_EFFECT];					// �\���̕ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;// ���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_apTextureEffect = NULL;	// �e�N�X�`���̃|�C���^

//============================
// �G�t�F�N�g�̏���������
//============================
void InitEffect(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.png",
		&g_apTextureEffect);

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{// �O���[�o���ϐ��̏�����
		g_Effect[nCnt].bUse = false;							  // ���g�p����
		g_Effect[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		  // ���W
		g_Effect[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		  // �p�x
		g_Effect[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	  // �ړ���
		g_Effect[nCnt].Scall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	  // �傫��
		g_Effect[nCnt].nLife = 0;								  // �̗�
		g_Effect[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f,0.0f);	  // �J���[
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	// ���_���̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos.x = -MAX_SIZE;
		pVtx[0].pos.y = MAX_SIZE;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = MAX_SIZE;
		pVtx[1].pos.y = MAX_SIZE;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = -MAX_SIZE;
		pVtx[2].pos.y = -MAX_SIZE;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = MAX_SIZE;
		pVtx[3].pos.y = -MAX_SIZE;
		pVtx[3].pos.z = 0.0f;

		// �e���_�̖@��(�x�N�g��)�̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	 // 1�ڂ̖@�����
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	 // 2�ڂ̖@�����
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	 // 3�ڂ̖@�����
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	 // 4�ڂ̖@�����

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

		// ���_��񕪂��炷
		pVtx += 4;
	}

	// �A�����b�N
	g_pVtxBuffEffect->Unlock();
}
//============================
// �G�t�F�N�g�̏I������
//============================
void UninitEffect(void)
{
	// �e�N�X�`���̔j��
	if (g_apTextureEffect != NULL)
	{
		g_apTextureEffect->Release();
		g_apTextureEffect = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}

}
//============================
// �G�t�F�N�g�̍X�V����
//============================
void UpdateEffect(void)
{
	// ���_���̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (!g_Effect[nCnt].bUse)
		{// ���g�p��Ԃ̎�
			pVtx += 4;
			continue;
		}

		// �g�p��Ԃ̎�
		// �ړ��ʂ̍X�V
		g_Effect[nCnt].pos += g_Effect[nCnt].move;

		// �̗͌��炷
		g_Effect[nCnt].nLife--;

		if (g_Effect[nCnt].nLife <= 0)
		{// �̗͂�0�ȉ��Ȃ�
			g_Effect[nCnt].bUse = false;
		}

		// ���_�J���[�̐ݒ�
		pVtx[0].col = g_Effect[nCnt].col;
		pVtx[1].col = g_Effect[nCnt].col;
		pVtx[2].col = g_Effect[nCnt].col;
		pVtx[3].col = g_Effect[nCnt].col;

		// ���_��񕪂��炷
		pVtx += 4;

	}

	// �A�����b�N
	g_pVtxBuffEffect->Unlock();
}
//============================
// �G�t�F�N�g�̕`�揈��
//============================
void DrawEffect(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���u�����f�B���O�̉��Z����
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxTrans, mtxScall;

	// ���e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// Z�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_Effect[nCnt].bUse)
		{// �g���Ă���Ƃ�

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Effect[nCnt].mtxWorld);

			// �r���[�}�g���b�N�X��錾
			D3DXMATRIX mtxView;

			// �r���[�}�g���b�N�X�̎擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// �J�����̋t�s���ݒ�
			g_Effect[nCnt].mtxWorld._11 = mtxView._11;
			g_Effect[nCnt].mtxWorld._12 = mtxView._21;
			g_Effect[nCnt].mtxWorld._13 = mtxView._31;
			g_Effect[nCnt].mtxWorld._21 = mtxView._12;
			g_Effect[nCnt].mtxWorld._22 = mtxView._22;
			g_Effect[nCnt].mtxWorld._23 = mtxView._32;
			g_Effect[nCnt].mtxWorld._31 = mtxView._13;
			g_Effect[nCnt].mtxWorld._32 = mtxView._23;
			g_Effect[nCnt].mtxWorld._33 = mtxView._33;

			// �傫���𔽉f
			D3DXMatrixScaling(&mtxScall, g_Effect[nCnt].Scall.x, g_Effect[nCnt].Scall.y, g_Effect[nCnt].Scall.z);
			D3DXMatrixMultiply(&g_Effect[nCnt].mtxWorld, &g_Effect[nCnt].mtxWorld, &mtxScall);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Effect[nCnt].pos.x, g_Effect[nCnt].pos.y, g_Effect[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Effect[nCnt].mtxWorld, &g_Effect[nCnt].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Effect[nCnt].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEffect);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}

	// ���e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//���u�����f�B���O��߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Z�e�X�g��߂�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}
//============================
// �G�t�F�N�g�̐ݒ菈��
//============================
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, D3DXVECTOR3 Scall, int nLife)
{
	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (!g_Effect[nCnt].bUse)
		{// ���g�p��Ԃ�������
			g_Effect[nCnt].pos = pos;	// ���W
			g_Effect[nCnt].move = move; // �ړ���
			g_Effect[nCnt].col = col;	// �J���[
			g_Effect[nCnt].Scall = Scall;// �g�嗦
			g_Effect[nCnt].nLife = nLife;// �̗�
			g_Effect[nCnt].bUse = true;	 // �g�p���

			break;
		}
	}
}
