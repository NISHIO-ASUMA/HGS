//===========================
//
// 爆発処理 [explosion.h]
// Author:TEAM_2
//
//===========================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//**************************
// インクルードファイル宣言
//**************************
#include "main.h"

//***************************
// マクロ定義
//***************************
#define MAX_EXPLOSION (128)			// 爆発の最大数
#define MAX_EXPLOSIONSIZE_X (30)	// 爆発のサイズ
#define MAX_EXPLOSIONSIZE_Y (30)	// 爆発のサイズ

//***************************
// 爆発構造体の定義
//***************************
typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3 rot;			// 角度
	D3DXVECTOR3 move;			// 移動量
	D3DXMATRIX mtxWorld;		// ワールドマトリックス
	int nCounterAnimExplosion;	// アニメーションカウンター
	int nPatternAnimExplosion;	// アニメーションパターン
	bool bUse;					// 使用しているか
}Explosion;

//***********************
// プロトタイプ宣言
//***********************
void InitExplosion(void);			// 爆発の初期化
void UninitExplosion(void);			// 爆発の終了
void UpdateExplosion(void);			// 爆発の更新
void DrawExplosion(void);			// 爆発の描画
void SetExplosion(D3DXVECTOR3 pos);	//爆発の設定処理

#endif
