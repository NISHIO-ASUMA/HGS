//======================================
//
// ���b�V���̕ǂ̏��� [mashwall.cpp]
// Author: TEAM_2
//
//======================================

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "meshwall.h"
#include "player.h"
#include "enemy.h"

//*****************************
// �O���[�o���ϐ��錾
//*****************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;	// ���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_apTextureMeshWall = NULL;		// �e�N�X�`���̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
MeshWall g_MeshWall;

//==============================
// ���b�V���t�B�[���h����������
//==============================
void InitMeshWall(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\sky.jpg",
		&g_apTextureMeshWall);

	// ������
	g_MeshWall.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshWall.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���[�J���ϐ��錾------------------------
	int nRadius = 680;		// ���a
	int nIndex = 0;

	float TexX = 1.0f / XVTX;
	float TexZ = 1.0f / ZVTX;
	float fAngle;
	D3DXVECTOR3 nor;
	//------------------------------------------

	// ���_�o�b�t�@(�O�p�`�͈ӎ����Ȃ�)
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * ALLVTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * INDEXBUFF,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall,
		NULL);

	// ���_���̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntV = 0; nCntV < ZVTX + 1; nCntV++)
	{// �����̕�����

		for (int nCntH = 0; nCntH < XVTX + 1; nCntH++)
		{// ���������̕�����
			// �p�x�̐ݒ�
			fAngle = (D3DX_PI * 2.0f) / XVTX * nCntH;

			// ���_���W�̐ݒ�
			pVtx[nIndex].pos = D3DXVECTOR3(sinf((fAngle)) * nRadius, nCntV * 100.0f, cosf((fAngle)) * nRadius);

			// �@���x�N�g���̐ݒ�
			nor = pVtx[nIndex].pos - g_MeshWall.pos;	// �e���_���猴�_�̒l������
			D3DXVec3Normalize(&pVtx[nIndex].nor, &nor);	// �@���̐��K��

			// �J���[
			pVtx[nIndex].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`��
			pVtx[nIndex].tex = D3DXVECTOR2(TexX * nCntH, TexZ * nCntV);

			nIndex++;
		}
	}

	// �A�����b�N
	g_pVtxBuffMeshWall->Unlock();

	// �C���f�b�N�X�o�b�t�@�̃|�C���^
	WORD* pIdx;

	int nIdxNumber = 0;				// ���[�J���ϐ�
	int nCntIdx3 = XVTX + 1;	// X�̒l
	int nNum = 0;

	//�C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	//�C���f�b�N�X��ݒ�
	for (int nCntIdx = 0; nCntIdx < ZVTX; nCntIdx++)
	{// MAX_ZVTX�̐�������
		for (int nCntIdx2 = 0; nCntIdx2 <= XVTX; nCntIdx2++, nCntIdx3++, nNum++)
		{// MAX_XVTX�̐�������
			pIdx[nIdxNumber] = nCntIdx3;	// ��������
			pIdx[nIdxNumber + 1] = nNum;	// ��������
			nIdxNumber += 2;
		}

		// NOTE: �Ō�̍s�ɏk�ރ|���S�����Ȃ�
		if (nCntIdx != ZVTX - 1)
		{
			pIdx[nIdxNumber] = nNum - 1;	// for���ɓ��邽��
			pIdx[nIdxNumber + 1] = nCntIdx3;	// ��������
			nIdxNumber += 2;

		}
	}

	// �A�����b�N
	g_pIdxBuffMeshWall->Unlock();

}
//==============================
// ���b�V���t�B�[���h�I������
//==============================
void UninitMeshWall(void)
{
	// �e�N�X�`���̔j��
	if (g_apTextureMeshWall != NULL)
	{
		g_apTextureMeshWall->Release();
		g_apTextureMeshWall = NULL;
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffMeshWall != NULL)
	{
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}
}
//==============================
// ���b�V���t�B�[���h�X�V����
//==============================
void UpdateMeshWall(void)
{
	// ����
}
//==============================
// ���b�V���t�B�[���h�`�揈��
//==============================
void DrawMeshWall(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_MeshWall.mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshWall.rot.y, g_MeshWall.rot.x, g_MeshWall.rot.z);
	D3DXMatrixMultiply(&g_MeshWall.mtxWorld, &g_MeshWall.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_MeshWall.pos.x, g_MeshWall.pos.y, g_MeshWall.pos.z);
	D3DXMatrixMultiply(&g_MeshWall.mtxWorld, &g_MeshWall.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshWall.mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshWall);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureMeshWall);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		ALLVTX,
		0,
		NUMPOLYGON);
}
//=========================
// �����蔻��
//=========================
void CollisionMeshWall()
{
	// ���|�J��
	int nRadius = 680;		// ���a
	int nCntVtx, nCntVtx2 = 0;
	D3DXVECTOR3 VecA[XVTX], VecB[XVTX], Cross[XVTX];

	// �v���C���[�̎擾
	Player* pPlayer = GetPlayer();

	// XVTX��
	for (int nCnt = 0; nCnt < XVTX; nCnt++)
	{
		// �p�x�̐ݒ�
		float fAngle = (D3DX_PI * 2.0f) / XVTX * nCnt;

		// ���_���W�̐ݒ�
		g_MeshWall.Vtxpos[nCnt] = D3DXVECTOR3(sinf((fAngle)) * nRadius, nCnt * 50.0f, cosf((fAngle)) * nRadius);

		// ���_
		nCntVtx = nCnt % XVTX;
		nCntVtx2 = (nCnt + 1) % XVTX;

		// 2�̃x�N�g��
		VecA[nCnt] = g_MeshWall.Vtxpos[nCntVtx2] - g_MeshWall.Vtxpos[nCntVtx];
		VecB[nCnt] = pPlayer->pos - g_MeshWall.Vtxpos[nCnt];

		// �O�ϊ֐�
		D3DXVec3Cross(&Cross[nCnt], &VecA[nCnt], &VecB[nCnt]);

		// ���K��
		D3DXVec3Normalize(&Cross[nCnt], &Cross[nCnt]);

		if (Cross[nCnt].y < 0.0f)
		{
			pPlayer->pos.x = pPlayer->posOld.x;
			pPlayer->pos.z = pPlayer->posOld.z;
		}
	}
}
//==================================
// �G�Ƃ̓����蔻��
//==================================
void CollisionEnemyToWall(int nCnt)
{
	// �G�̎擾
	Enemy* pEnemy = GetEnemy();

	// ���[�J���ϐ�-----------------------------
	D3DXVECTOR3 Vec1[XVTX], Vec2[XVTX], CrossEnemy[XVTX];
	int nRadius = 680;		// ���a
	int nCntVtx1, nCntVtx2 = 0;

	// XVTX��
	for (int nCntVec = 0; nCntVec < XVTX; nCntVec++)
	{
		if (pEnemy[nCnt].bUse)
		{
			// �p�x�̐ݒ�
			float fAngle = (D3DX_PI * 2.0f) / XVTX * nCntVec;

			// ���_���W�̐ݒ�
			g_MeshWall.Vtxpos[nCntVec] = D3DXVECTOR3(sinf((fAngle)) * nRadius, nCntVec * 100.0f, cosf((fAngle)) * nRadius);

			// ���_
			nCntVtx1 = nCntVec % XVTX;
			nCntVtx2 = (nCntVec + 1) % XVTX;

			// 2�̃x�N�g��
			Vec1[nCntVec] = g_MeshWall.Vtxpos[nCntVtx2] - g_MeshWall.Vtxpos[nCntVtx1];
			Vec2[nCntVec] = pEnemy[nCnt].pos - g_MeshWall.Vtxpos[nCntVec];

			// �O�ϊ֐�
			D3DXVec3Cross(&CrossEnemy[nCntVec], &Vec1[nCntVec], &Vec2[nCntVec]);

			// ���K��
			D3DXVec3Normalize(&CrossEnemy[nCntVec], &CrossEnemy[nCntVec]);

			if (CrossEnemy[nCntVec].y < 0.0f)
			{// pos�߂�
				pEnemy[nCnt].pos.x = pEnemy[nCnt].posOld.x;
				pEnemy[nCnt].pos.z = pEnemy[nCnt].posOld.z;
			}
		}
	}
}
