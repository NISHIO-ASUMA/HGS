//==========================
//
// バレッド処理 [bullet.h]
// Author: TEAM_2
//
//==========================
#ifndef _BULLET_H_
#define _BULLET_H_

//***************************
// インクルードファイル宣言
//***************************
#include "main.h"

//***************************
// マクロ定義
//***************************
#define MAX_BULLET (128)    // 最大数

//***************************
// 列挙型宣言
//***************************
typedef enum
{
	BULLETTYPE_PLAYER = 0,	// プレイヤー
	BULLETTYPE_ENEMY,		// 敵
	BULLETTYPE_MAX
}BULLETTYPE;

//***************************
// 構造体宣言
//***************************
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 posOld;		// 過去の位置
	D3DXVECTOR3 rot;		// 向き
	D3DXVECTOR3 move;		// 移動量
	D3DXVECTOR3 dir;		// 方向ベクトル
	D3DXMATRIX  mtxWorld;	// ワールドマトリックス
	bool bUse;				// 使用状態
	int nIdxBullet;			// インデックス
	int nLife;				// 体力
}Bullet;

//**********************
// プロトタイプ宣言
//**********************
void InitBullet(void);		// バレッド初期化処理
void UninitBullet(void);	// バレッド終了処理
void UpdateBullet(void);	// バレッド更新処理
void DrawBullet(void);		// バレッド描画処理
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 dir, int nLife, D3DXVECTOR3 move); // バレッド設定処理(処理によって引数追加)

#endif 


