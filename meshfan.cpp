//======================================
//
// ���b�V���̋��^�̏��� [mashFan.h]
// Author: TEAM_2
//
//======================================

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "meshfan.h"

//***************************
// �O���[�o���ϐ��錾
//***************************
//���b�V���t�B�[���h�̃e�N�X�`��
LPDIRECT3DTEXTURE9 g_pTexturemeshwall = NULL;
//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffmeshwall = NULL;
//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffmeshwall = NULL;
//���b�V���t�B�[���h�̈ʒu
D3DXVECTOR3 g_posmeshwall;
//���b�V���t�B�[���h�̌���
D3DXVECTOR3 g_rotmeshwall;
//���b�V���t�B�[���h�̃��[���h�}�g���b�N�X
D3DXMATRIX g_mtxWorldmeshwall;

//==================================
// ���b�V���t�@������������
//==================================
void InitmeshFan(void)
{
    LPDIRECT3DDEVICE9 pDevice = GetDevice();

    // �e�N�X�`���̓ǂݍ���
    D3DXCreateTextureFromFile(pDevice,
        "data\\TEXTURE\\sky.jpg",
        &g_pTexturemeshwall);

    // ���_�o�b�t�@�̐���
    pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * meshwall_VERTEX_NUM,
        D3DUSAGE_WRITEONLY,
        FVF_VERTEX_3D,
        D3DPOOL_MANAGED,
        &g_pVtxBuffmeshwall,
        NULL);

    // ���_�o�b�t�@�����b�N
    VERTEX_3D* pVtx = NULL;
    g_pVtxBuffmeshwall->Lock(0, 0, (void**)&pVtx, 0);

    // �����`�̒n��
    float hemisphereRadius = 710.0f; // �����̔��a

    for (int nCntV = 0; nCntV <= meshwall_Z_BLOCK; nCntV++) {
        for (int nCntH = 0; nCntH <= meshwall_X_BLOCK; nCntH++) {
            // nCntH�Ԗڂ̊p�x���v�Z (1��]�𕪊����Čv�Z)
            float angleH = (360.0f / meshwall_X_BLOCK) * nCntH;

            // nCntV�Ԗڂ̊p�x���v�Z (�����̍���������)
            float angleV = 90.0f * ((float)nCntV / meshwall_Z_BLOCK);

            // ���_�̈ʒu��ݒ�
            pVtx[nCntV * (meshwall_X_BLOCK + 1) + nCntH].pos = D3DXVECTOR3(
                sinf(D3DXToRadian(angleH)) * hemisphereRadius * cosf(D3DXToRadian(angleV)), // X���W
                 hemisphereRadius * sinf(D3DXToRadian(angleV)),                             // Y���W
                cosf(D3DXToRadian(angleH)) * hemisphereRadius * cosf(D3DXToRadian(angleV))  // Z���W
            );

            // �@�����v�Z (���_���W����̒P�ʃx�N�g��)
            D3DXVECTOR3 normal = D3DXVECTOR3(
                pVtx[nCntV * (meshwall_X_BLOCK + 1) + nCntH].pos.x / hemisphereRadius,
                pVtx[nCntV * (meshwall_X_BLOCK + 1) + nCntH].pos.y / hemisphereRadius,
                pVtx[nCntV * (meshwall_X_BLOCK + 1) + nCntH].pos.z / hemisphereRadius
            );
            D3DXVec3Normalize(&normal, &normal);
            pVtx[nCntV * (meshwall_X_BLOCK + 1) + nCntH].nor = normal;

            // ���_�J���[��ݒ�
            pVtx[nCntV * (meshwall_X_BLOCK + 1) + nCntH].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

            // �e�N�X�`�����W��ݒ�i���ʂɉ����ēW�J�j
            pVtx[nCntV * (meshwall_X_BLOCK + 1) + nCntH].tex = D3DXVECTOR2(
                (float)nCntH / meshwall_X_BLOCK,                           // U���W�i�~�������j
                1.0f - (float)nCntV / meshwall_Z_BLOCK                     // V���W�i���������j
            );
        }
    }
    // ���_�o�b�t�@���A�����b�N
    g_pVtxBuffmeshwall->Unlock();

    // �C���f�b�N�X�o�b�t�@�̐���
    pDevice->CreateIndexBuffer(sizeof(WORD) * meshwall_INDEX_NUM,
        D3DUSAGE_WRITEONLY,
        D3DFMT_INDEX16,
        D3DPOOL_MANAGED,
        &g_pIdxBuffmeshwall,
        NULL);

    // �C���f�b�N�X�o�b�t�@�����b�N
    WORD* pIdx = NULL;
    g_pIdxBuffmeshwall->Lock(0, 0, (void**)&pIdx, 0);

    // �C���f�b�N�X�̐ݒ�
    int idx = 0;
    for (int nCntV = 0; nCntV < meshwall_Z_BLOCK; nCntV++) {
        for (int x = 0; x < meshwall_X_BLOCK; x++) {
            int baseIndex = nCntV * (meshwall_X_BLOCK + 1) + x;

            // �O�p�`1
            pIdx[idx++] = baseIndex;
            pIdx[idx++] = baseIndex + meshwall_X_BLOCK + 1;
            pIdx[idx++] = baseIndex + 1;

            // �O�p�`2
            pIdx[idx++] = baseIndex + 1;
            pIdx[idx++] = baseIndex + meshwall_X_BLOCK + 1;
            pIdx[idx++] = baseIndex + meshwall_X_BLOCK + 2;
        }
    }

    // �C���f�b�N�X�o�b�t�@���A�����b�N
    g_pIdxBuffmeshwall->Unlock();

    // �ʒu�E�����̏�����
    g_posmeshwall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    g_rotmeshwall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//================================
// ���b�V���t�@���������
//================================
void UninitmeshFan(void)
{
    if (g_pTexturemeshwall != NULL) {

        g_pTexturemeshwall->Release();
        g_pTexturemeshwall = NULL;
    }
    if (g_pVtxBuffmeshwall != NULL) {
        g_pVtxBuffmeshwall->Release();
        g_pVtxBuffmeshwall = NULL;
    }
    if (g_pIdxBuffmeshwall != NULL) {
        g_pIdxBuffmeshwall->Release();
        g_pIdxBuffmeshwall = NULL;
    }
}
//=============================
// ���b�V���t�@���X�V����
//=============================
void UpdatemeshFan(void)
{
    //�K�v�ɉ����Ēǉ�
}
//=============================
// ���b�V���t�@���`�揈��
//=============================
void DrawmeshFan(void)
{
    LPDIRECT3DDEVICE9 pDevice = GetDevice();
    D3DXMATRIX mtxRot, mtxTrans;

    // ���[���h�}�g���b�N�X�̏�����
    D3DXMatrixIdentity(&g_mtxWorldmeshwall);

    // ��]�𔽉f
    D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotmeshwall.y, g_rotmeshwall.x, g_rotmeshwall.z);
    D3DXMatrixMultiply(&g_mtxWorldmeshwall, &g_mtxWorldmeshwall, &mtxRot);

    // �ړ��𔽉f
    D3DXMatrixTranslation(&mtxTrans, g_posmeshwall.x, g_posmeshwall.y, g_posmeshwall.z);
    D3DXMatrixMultiply(&g_mtxWorldmeshwall, &g_mtxWorldmeshwall, &mtxTrans);

    // ���[���h�}�g���b�N�X�̐ݒ�
    pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldmeshwall);

    // ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffmeshwall, 0, sizeof(VERTEX_3D));

    // �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetIndices(g_pIdxBuffmeshwall);

    // ���_�t�H�[�}�b�g�̐ݒ�
    pDevice->SetFVF(FVF_VERTEX_3D);

    // �e�N�X�`���̐ݒ�
    pDevice->SetTexture(0, g_pTexturemeshwall);

    // �|���S���̕`��
    pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0,
        meshwall_VERTEX_NUM, 0, meshwall_INDEX_NUM);
}