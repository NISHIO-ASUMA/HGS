//================================
//
// �p�[�e�B�N������ [particle.h]
// Author: TEAM_2
//
//================================

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "particle.h"
#include "effect.h"

//***************************
// �}�N����`
//***************************
#define MAX_PARTICLE (24)    // �ő吔

//***************************
// �O���[�o���ϐ��錾
//***************************
Particle g_Particle[MAX_PARTICLE];		// �\���̕ϐ�

//============================
// �p�[�e�B�N���̏���������
//============================
void InitParticle(void)
{
	// �\���̂̏�����
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		g_Particle[nCnt].bUse = false;								// ���g�p���
		g_Particle[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �F
		g_Particle[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���W
		g_Particle[nCnt].nLife = 0;									// �̗�
	}
}
//============================
// �p�[�e�B�N���̍X�V����
//============================
void UpdateParticle(void)
{
	//���[�J���ϐ�
	D3DXVECTOR3 move;
	D3DXVECTOR3 pos;
	D3DXCOLOR col;
	D3DXVECTOR3 Scal;

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (!g_Particle[nCntParticle].bUse)
		{// ���g�p��ԂȂ�
			continue;
		}

		//�p�[�e�B�N���̐���
		for (int nCntApper = 0; nCntApper < 30; nCntApper++)
		{
			if (g_Particle[nCntApper].nType == PARTICLETYPE_PLAYER)
			{// PLAYER�Ɏg�p����p�[�e�B�N��
				//�ʒu�̐ݒ�
				pos = g_Particle[nCntParticle].pos;

				//�ړ��ʂ̐ݒ�
				float fAngelX = (float)(rand() % 629 - 314) / 100.0f;
				float fAngelY = (float)(rand() % 629 - 314) / 100.0f;
				float fAngelZ = (float)(rand() % 629 - 314) / 100.0f;

				float fLength = ((float)(rand() % 60) / 10.0f + 0.9f);

				move.x = sinf(fAngelX) * fLength;
				move.y = sinf(fAngelY) * fLength;
				move.z = sinf(fAngelZ) * fLength;

				//�J���[�̐ݒ�
				col = g_Particle[nCntParticle].col;

				//���a�̐ݒ�
				Scal.x = ((float)(rand() % 1) + 0.5f);
				Scal.y = ((float)(rand() % 1) + 0.5f);
				Scal.z = ((float)(rand() % 1) + 0.5f);

				//�����̐ݒ�
				int nLife = ((float)(rand() % 800) / 10);

				//�G�t�F�N�g�̐ݒ�
				SetEffect(pos, move, col, Scal, nLife);
			}

			else if (g_Particle[nCntApper].nType == PARTICLETYPE_BULLET)
			{// �e�Ɏg�p����p�[�e�B�N��
				//�ʒu�̐ݒ�
				pos = g_Particle[nCntParticle].pos;

				//�ړ��ʂ̐ݒ�
				float fAngelX = (float)(rand() % 629 - 314) / 100.0f;
				float fAngelY = (float)(rand() % 629 - 314) / 100.0f;
				float fAngelZ = (float)(rand() % 629 - 314) / 100.0f;

				float fLength = ((float)(rand() % 60) / 10.0f + 0.2f);

				move.x = sinf(fAngelX) * fLength;
				move.y = sinf(fAngelY) * fLength;
				move.z = sinf(fAngelZ) * fLength;

				//�J���[�̐ݒ�
				col = g_Particle[nCntParticle].col;

				//���a�̐ݒ�
				Scal.x = ((float)(rand() % 1) + 0.5f);
				Scal.y = ((float)(rand() % 1) + 0.5f);
				Scal.z = ((float)(rand() % 1) + 0.5f);

				//�����̐ݒ�
				int nLife = ((float)(rand() % 1000) / 10);

				//�G�t�F�N�g�̐ݒ�
				SetEffect(pos, move, col, Scal, nLife);

			}
			else if (g_Particle[nCntParticle].nType == PARTICLETYPE_ENEMY)
			{// �G�l�~�[�Ɏg�p����p�[�e�B�N��
				pos = g_Particle[nCntParticle].pos;

				//�ړ��ʂ̐ݒ�
				float fAngelX = (float)(rand() % 629 - 314) / 100.0f;
				float fAngelY = (float)(rand() % 629 - 314) / 100.0f;
				float fAngelZ = (float)(rand() % 629 - 314) / 100.0f;

				float fLength = ((float)(rand() % 80) / 10.0f + 0.9f);

				move.x = sinf(fAngelX) * fLength;
				move.y = sinf(fAngelY) * fLength;
				move.z = sinf(fAngelZ) * fLength;

				//�J���[�̐ݒ�
				col = g_Particle[nCntParticle].col;

				//���a�̐ݒ�
				Scal.x = ((float)(rand() % 1) + 0.6f);
				Scal.y = ((float)(rand() % 1) + 0.6f);
				Scal.z = ((float)(rand() % 1) + 0.6f);

				//�����̐ݒ�
				int nLife = ((float)(rand() % 1000) / 10);

				//�G�t�F�N�g�̐ݒ�
				SetEffect(pos, move, col, Scal, nLife);

			}
		}

		// �̗͂����炷
		g_Particle[nCntParticle].nLife--;

		if (g_Particle[nCntParticle].nLife <= 0)
		{// 0�ȉ��ɂȂ����Ƃ�
			//���g�p���
			g_Particle[nCntParticle].bUse = false;
		}
	}
}
//============================
// �p�[�e�B�N���̐ݒ菈��
//============================
void SetParticle(D3DXVECTOR3 pos, D3DXCOLOR col, int nLife,PARTICLETYPE type)
{
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_Particle[nCntParticle].bUse)
		{// �g�p��ԂȂ�
			continue;
		}

		// ���g�p��Ԃ̎�
		g_Particle[nCntParticle].pos = pos;		// ���W
		g_Particle[nCntParticle].nLife = nLife;	// �̗�
		g_Particle[nCntParticle].col = col;		// �F
		g_Particle[nCntParticle].nType = type;	// ���
		g_Particle[nCntParticle].bUse = true;	// �g�p����

		break;
	}

}
