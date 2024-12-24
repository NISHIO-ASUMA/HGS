//======================================
//
// ���b�V���̋��^�̏��� [mashfan.h]
// Author: TEAM_2
//
//======================================
#ifndef _MESHFAN_H_
#define _MESHFAN_H_

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "main.h"

//***************************
// �}�N����`
//***************************
// ���b�V���t�B�[���h�̃u���b�N��
#define meshwall_X_BLOCK (10) // X�����̃u���b�N��
#define meshwall_Z_BLOCK (10) // Z�����̃u���b�N��

// ���b�V���t�B�[���h�̒��_��
#define meshwall_VERTEX_NUM ((meshwall_X_BLOCK + 1) * (meshwall_Z_BLOCK + 1))

// ���b�V���t�B�[���h�̃C���f�b�N�X��
#define meshwall_INDEX_NUM (meshwall_X_BLOCK * meshwall_Z_BLOCK * 6)

// ���b�V���t�B�[���h�̃v���~�e�B�u��
#define meshwall_PRIMITIVE_NUM ((meshwall_X_BLOCK * meshwall_Z_BLOCK * 2) + ((meshwall_Z_BLOCK - 1) * 2))

//***************************
// �v���g�^�C�v�錾
//***************************
void InitmeshFan(void);
void UninitmeshFan(void);
void UpdatemeshFan(void);
void DrawmeshFan(void);

#endif // !_MESHFAN_H_

