//======================================
//
// メッシュの壁の処理 [mashwall.h]
// Author: TEAM_2
//
//======================================
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

//***************************
// インクルードファイル宣言
//***************************
#include "main.h"

//***************************
// マクロ定義
//***************************
#define XVTX (30)	// Xの値
#define ZVTX (1)	// Zの値

#define ALLVTX ((XVTX + 1) * (ZVTX + 1))	// 頂点数
#define NUMPOLYGON (((XVTX * ZVTX) * 2)) + (4 * (ZVTX - 1))	// ポリゴン数
#define INDEXBUFF (NUMPOLYGON + 2)		// インデックスバッファ数

#define MAX_WALLX (300.0f)	// フィールドのX
#define MAX_WALLZ (300.0f)	// フィールドのZ

//***************************
// 構造体宣言
//***************************
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 Vtxpos[XVTX];
	D3DXVECTOR3 rot;		// 向き
	D3DXMATRIX  mtxWorld;	// ワールドマトリックス
}MeshWall;

//**********************
// プロトタイプ宣言
//**********************
void InitMeshWall(void);		// メッシュの壁初期化処理
void UninitMeshWall(void);		// メッシュの壁終了処理
void UpdateMeshWall(void);		// メッシュの壁更新処理
void DrawMeshWall(void);		// メッシュの壁描画処理
void CollisionMeshWall();		// 当たり判定
void CollisionEnemyToWall(int nCnt);// 敵との判定

#endif // !_MESHWALL_H_
