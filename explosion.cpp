//===========================
//
// �������� [explosion.cpp]
// Author:TEAM_2
//
//===========================

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "explosion.h"

//*******************************
// �O���[�o���ϐ��錾
//*******************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	// ���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;		// �e�N�X�`���̃|�C���^
Explosion g_Explosion[MAX_EXPLOSION];				// �����̏��

//============================
// �����̏���������
//============================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;// �f�o�C�X�ւ̃|�C���^

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&g_pTextureExplosion);

	// �������̏�����
	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_Explosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���W
		g_Explosion[nCntExplosion].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �p�x
		g_Explosion[nCntExplosion].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// �ړ���
		g_Explosion[nCntExplosion].nCounterAnimExplosion = 0;			// �J�E���^�[�̏�����
		g_Explosion[nCntExplosion].nPatternAnimExplosion = 0;			// �p�^�[���̏�����
		g_Explosion[nCntExplosion].bUse = false;						// ���g�p���
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	// ���_���̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos.x = g_Explosion[nCnt].pos.x - 30.0f;
		pVtx[0].pos.y = g_Explosion[nCnt].pos.y - 30.0f;
		pVtx[0].pos.z = g_Explosion[nCnt].pos.z;

		pVtx[1].pos.x = g_Explosion[nCnt].pos.x - 30.0f;
		pVtx[1].pos.y = g_Explosion[nCnt].pos.y + 30.0f;
		pVtx[1].pos.z = g_Explosion[nCnt].pos.z;

		pVtx[2].pos.x = g_Explosion[nCnt].pos.x + 30.0f;
		pVtx[2].pos.y = g_Explosion[nCnt].pos.y - 30.0f;
		pVtx[2].pos.z = g_Explosion[nCnt].pos.z;

		pVtx[3].pos.x = g_Explosion[nCnt].pos.x + 30.0f;
		pVtx[3].pos.y = g_Explosion[nCnt].pos.y + 30.0f;
		pVtx[3].pos.z = g_Explosion[nCnt].pos.z;

		// �e���_�̖@��(�x�N�g��)�̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);			// 1�ڂ̖@�����
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);			// 2�ڂ̖@�����
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);			// 3�ڂ̖@�����
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);			// 4�ڂ̖@�����

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();

}
//============================
// �����̏I������
//============================
void UninitExplosion(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}

}
//============================
// �����̍X�V����
//============================
void UpdateExplosion(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		// �A�j���[�V�����J�E���g�����Z
		g_Explosion[nCnt].nCounterAnimExplosion++;

		if (g_Explosion[nCnt].bUse)
		{
			if (g_Explosion[nCnt].nCounterAnimExplosion >= 2)
			{// �J�E���g���ő�l�ɂȂ�����
				g_Explosion[nCnt].nCounterAnimExplosion = NULL;		// �J�E���^�[�������l�ɖ߂�

				g_Explosion[nCnt].nPatternAnimExplosion++;			// �p�^�[���i���o�[���X�V

				//���_���W�̍X�V
				pVtx[0].tex = D3DXVECTOR2(0.0f + g_Explosion[nCnt].nPatternAnimExplosion * 0.125f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.125f + g_Explosion[nCnt].nPatternAnimExplosion * 0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + g_Explosion[nCnt].nPatternAnimExplosion * 0.125f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f + g_Explosion[nCnt].nPatternAnimExplosion * 0.125f, 1.0f);

			}

			if (g_Explosion[nCnt].nPatternAnimExplosion > 8)
			{// �p�^�[����������ɒB������
				g_Explosion[nCnt].nPatternAnimExplosion = 0;	// �p�^�[���i���o�[�������l�ɖ߂�
				g_Explosion[nCnt].bUse = false;					// ���g�p����
			}

		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();

}
//============================
// �����̕`�揈��
//============================
void DrawExplosion(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans;

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		if (g_Explosion[nCnt].bUse == true)
		{// �g���Ă���Ƃ�

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Explosion[nCnt].mtxWorld);

			// �r���[�}�g���b�N�X��錾
			D3DXMATRIX mtxView;

			// �r���[�}�g���b�N�X�̎擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// �J�����̋t�s���ݒ�
			g_Explosion[nCnt].mtxWorld._11 = mtxView._11;
			g_Explosion[nCnt].mtxWorld._12 = mtxView._21;
			g_Explosion[nCnt].mtxWorld._13 = mtxView._31;
			g_Explosion[nCnt].mtxWorld._21 = mtxView._12;
			g_Explosion[nCnt].mtxWorld._22 = mtxView._22;
			g_Explosion[nCnt].mtxWorld._23 = mtxView._32;
			g_Explosion[nCnt].mtxWorld._31 = mtxView._13;
			g_Explosion[nCnt].mtxWorld._32 = mtxView._23;
			g_Explosion[nCnt].mtxWorld._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Explosion[nCnt].pos.x, g_Explosion[nCnt].pos.y, g_Explosion[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Explosion[nCnt].mtxWorld, &g_Explosion[nCnt].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Explosion[nCnt].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureExplosion);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);

		}
	}
	// ���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}
//============================
// �����̐ݒ菈��
//============================
void SetExplosion(D3DXVECTOR3 pos)
{	
	for (int nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		if (g_Explosion[nCnt].bUse == false)
		{// ���g�p��ԂȂ�
			g_Explosion[nCnt].pos = pos;	// ���W
			g_Explosion[nCnt].bUse = true;	// �g�p����

			break;
		}
	}
}
