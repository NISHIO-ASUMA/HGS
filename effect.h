//==========================
//
// エフェクト処理 [effect.h]
// Author: TEAM_2
//
//==========================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//***************************
// インクルードファイル宣言
//***************************
#include "main.h"

//***************************
// マクロ定義
//***************************
#define MAX_EFFECT (16)    // 最大数
#define MAX_SIZE (10.0f)

//***************************
// 列挙型宣言
//***************************
typedef enum
{
	EFECTTYPE_PLAYER = 0,	// プレイヤー
	EFFECTTYPE_BULLET,		// 弾
	EFFECTTYPE_ENEMY,		// 敵
	EFFECTTYPE_MAX
}EFFECTTYPE;

//***************************
// 構造体宣言
//***************************
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き
	D3DXVECTOR3 move;		// 移動量
	D3DXMATRIX  mtxWorld;	// ワールドマトリックス
	D3DXCOLOR col;			// カラー
	D3DXVECTOR3 Scall;		// 大きさ
	float fRadius;			// 半径
	bool bUse;				// 使用状態
	int nIdxeffect;			// インデックス
	int nLife;				// 体力
	EFFECTTYPE Type;		// 種類
}Effect;

//**********************
// プロトタイプ宣言
//**********************
void InitEffect(void);				// エフェクト初期化処理
void UninitEffect(void);			// エフェクト終了処理
void UpdateEffect(void);			// エフェクト更新処理
void DrawEffect(void);				// エフェクト描画処理
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXCOLOR col,D3DXVECTOR3 Scall,int nLife);    // エフェクト設定処理
#endif 


