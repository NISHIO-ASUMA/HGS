//================================
//
// パーティクル処理 [particle.h]
// Author: TEAM_2
//
//================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//***************************
// インクルードファイル宣言
//***************************
#include "main.h"

//***************************
// 列挙型宣言
//***************************
typedef enum
{
	PARTICLETYPE_PLAYER = 0,	// プレイヤー
	PARTICLETYPE_BULLET,		// 弾
	PARTICLETYPE_ENEMY,			// 敵
	PARTICLETYPE_MAX
}PARTICLETYPE;

//***************************
// 構造体宣言
//***************************
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXCOLOR col;			// カラー
	bool bUse;				// 使用状態
	int nType;				// 種類
	int nLife;				// 体力
}Particle;

//**********************
// プロトタイプ宣言
//**********************
void InitParticle(void);				// パーティクル初期化処理
void UpdateParticle(void);				// パーティクル更新処理
void SetParticle(D3DXVECTOR3 pos,D3DXCOLOR col, int nLife, PARTICLETYPE type);    // パーティクル設定処理

#endif 


