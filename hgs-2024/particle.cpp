//================================
//
// パーティクル処理 [particle.h]
// Author: TEAM_2
//
//================================

//***************************
// インクルードファイル宣言
//***************************
#include "particle.h"
#include "effect.h"

//***************************
// マクロ定義
//***************************
#define MAX_PARTICLE (24)    // 最大数

//***************************
// グローバル変数宣言
//***************************
Particle g_Particle[MAX_PARTICLE];		// 構造体変数

//============================
// パーティクルの初期化処理
//============================
void InitParticle(void)
{
	// 構造体の初期化
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		g_Particle[nCnt].bUse = false;								// 未使用状態
		g_Particle[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 色
		g_Particle[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 座標
		g_Particle[nCnt].nLife = 0;									// 体力
	}
}
//============================
// パーティクルの更新処理
//============================
void UpdateParticle(void)
{
	//ローカル変数
	D3DXVECTOR3 move;
	D3DXVECTOR3 pos;
	D3DXCOLOR col;
	D3DXVECTOR3 Scal;

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (!g_Particle[nCntParticle].bUse)
		{// 未使用状態なら
			continue;
		}

		//パーティクルの生成
		for (int nCntApper = 0; nCntApper < 30; nCntApper++)
		{
			if (g_Particle[nCntApper].nType == PARTICLETYPE_PLAYER)
			{// PLAYERに使用するパーティクル
				//位置の設定
				pos = g_Particle[nCntParticle].pos;

				//移動量の設定
				float fAngelX = (float)(rand() % 629 - 314) / 100.0f;
				float fAngelY = (float)(rand() % 629 - 314) / 100.0f;
				float fAngelZ = (float)(rand() % 629 - 314) / 100.0f;

				float fLength = ((float)(rand() % 60) / 10.0f + 0.9f);

				move.x = sinf(fAngelX) * fLength;
				move.y = sinf(fAngelY) * fLength;
				move.z = sinf(fAngelZ) * fLength;

				//カラーの設定
				col = g_Particle[nCntParticle].col;

				//半径の設定
				Scal.x = ((float)(rand() % 1) + 0.5f);
				Scal.y = ((float)(rand() % 1) + 0.5f);
				Scal.z = ((float)(rand() % 1) + 0.5f);

				//寿命の設定
				int nLife = ((float)(rand() % 800) / 10);

				//エフェクトの設定
				SetEffect(pos, move, col, Scal, nLife);
			}

			else if (g_Particle[nCntApper].nType == PARTICLETYPE_BULLET)
			{// 弾に使用するパーティクル
				//位置の設定
				pos = g_Particle[nCntParticle].pos;

				//移動量の設定
				float fAngelX = (float)(rand() % 629 - 314) / 100.0f;
				float fAngelY = (float)(rand() % 629 - 314) / 100.0f;
				float fAngelZ = (float)(rand() % 629 - 314) / 100.0f;

				float fLength = ((float)(rand() % 60) / 10.0f + 0.2f);

				move.x = sinf(fAngelX) * fLength;
				move.y = sinf(fAngelY) * fLength;
				move.z = sinf(fAngelZ) * fLength;

				//カラーの設定
				col = g_Particle[nCntParticle].col;

				//半径の設定
				Scal.x = ((float)(rand() % 1) + 0.5f);
				Scal.y = ((float)(rand() % 1) + 0.5f);
				Scal.z = ((float)(rand() % 1) + 0.5f);

				//寿命の設定
				int nLife = ((float)(rand() % 1000) / 10);

				//エフェクトの設定
				SetEffect(pos, move, col, Scal, nLife);

			}
			else if (g_Particle[nCntParticle].nType == PARTICLETYPE_ENEMY)
			{// エネミーに使用するパーティクル
				pos = g_Particle[nCntParticle].pos;

				//移動量の設定
				float fAngelX = (float)(rand() % 629 - 314) / 100.0f;
				float fAngelY = (float)(rand() % 629 - 314) / 100.0f;
				float fAngelZ = (float)(rand() % 629 - 314) / 100.0f;

				float fLength = ((float)(rand() % 80) / 10.0f + 0.9f);

				move.x = sinf(fAngelX) * fLength;
				move.y = sinf(fAngelY) * fLength;
				move.z = sinf(fAngelZ) * fLength;

				//カラーの設定
				col = g_Particle[nCntParticle].col;

				//半径の設定
				Scal.x = ((float)(rand() % 1) + 0.6f);
				Scal.y = ((float)(rand() % 1) + 0.6f);
				Scal.z = ((float)(rand() % 1) + 0.6f);

				//寿命の設定
				int nLife = ((float)(rand() % 1000) / 10);

				//エフェクトの設定
				SetEffect(pos, move, col, Scal, nLife);

			}
		}

		// 体力を減らす
		g_Particle[nCntParticle].nLife--;

		if (g_Particle[nCntParticle].nLife <= 0)
		{// 0以下になったとき
			//未使用状態
			g_Particle[nCntParticle].bUse = false;
		}
	}
}
//============================
// パーティクルの設定処理
//============================
void SetParticle(D3DXVECTOR3 pos, D3DXCOLOR col, int nLife,PARTICLETYPE type)
{
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_Particle[nCntParticle].bUse)
		{// 使用状態なら
			continue;
		}

		// 未使用状態の時
		g_Particle[nCntParticle].pos = pos;		// 座標
		g_Particle[nCntParticle].nLife = nLife;	// 体力
		g_Particle[nCntParticle].col = col;		// 色
		g_Particle[nCntParticle].nType = type;	// 種類
		g_Particle[nCntParticle].bUse = true;	// 使用判定

		break;
	}

}
