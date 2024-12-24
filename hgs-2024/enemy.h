//=================================
//
// 敵の処理 [enemy.h]
// Author: TEAM_2
//
//=================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//****************************
// インクルードファイル宣言
//****************************
#include "main.h"
#include "model.h"

//****************************
// マクロ定義
//****************************
#define MAX_ENEMY (100)			// 敵の出す最大数
#define HALFSIZE (0.5f)			// 半分のサイズ分の値

//********************************
// 敵の状態列挙型宣言
//********************************
typedef enum
{
	ENEMYSTATE_NORMAL = 0,	// 通常状態
	ENEMYSTATE_DAMAGE,		// ダメージ状態
	ENEMYSTATE_MAX
}ENEMYSTATE;

//*************************************
// 敵の種類の列挙型宣言
//*************************************
typedef enum
{
	ENEMYTYPE_FIRE = 0,	// 1つ目の敵
	ENEMYTYPE_NOFIRE,	// 2つ目の敵
	ENEMYTYPE_PURA,		// 3つ目の敵
	ENEMYTYPE_KAN,		// 4つ目の敵
	ENEMYTYPE_RECYCLE,	// 5つ目の敵
	ENEMYTYPE_MAX
}ENEMYTYPE;

//*************************************
// 敵のモデルの列挙型宣言
// TODO : ここのモデルは各自変更可能
//*************************************
static const char* ENEMY_MODEL[ENEMYTYPE_MAX] =
{
	"data\\MODEL\\Enemy001.x",	// 1
	"data\\MODEL\\Enemy002.x",	// 2
	"data\\MODEL\\Enemy003.x",	// 3
	"data\\MODEL\\Enemy004.x",	// 4
	"data\\MODEL\\Enemy005.x",	// 5
};

//****************************
// 敵のモデルの構造体宣言
//****************************
typedef struct
{
	LPD3DXMESH pMeshEnemy;					   // メッシュのポインタ
	LPD3DXBUFFER pBuffMatEnemy;				   // マテリアルのポインタ
	DWORD dwNumMatEnemy;					   // マテリアル数
	LPDIRECT3DTEXTURE9 pTexture[ENEMYTYPE_MAX];// テクスチャのポインタ
	D3DCOLORVALUE DiffUse, FirstDiffUse;	   // モデルのカラー
}EnemyModel;

//****************************
// 敵の構造体宣言
//****************************
typedef struct
{
	EnemyModel aModel[ENEMYTYPE_MAX];	// モデル情報
	D3DXVECTOR3 pos;					// 座標
	D3DXVECTOR3 posOld;					// 過去座標
	D3DXVECTOR3 rot;					// 角度
	D3DXVECTOR3 move;					// 移動量
	D3DXMATRIX  mtxWorld;				// ワールドマトリックス
	D3DXVECTOR3 Vtxmax, Vtxmin;			// 頂点情報
	D3DXVECTOR3 size;					// サイズ
	ENEMYSTATE State;					// 状態
	ENEMYTYPE nType;					// 種類
	int nCntState;						// 状態管理カウンター
	int nLife;							// 体力
	int nIdxEnemy;						// 影
	bool bUse;							// 使用状態
}Enemy;

//**********************
// プロトタイプ宣言
//**********************
void InitEnemy(void);							// 敵の初期化
void UninitEnemy(void);							// 敵の終了
void UpdateEnemy(void);							// 敵の更新
void DrawEnemy(void);							// 敵の描画
void SetEnemy(ENEMYTYPE nType, D3DXVECTOR3 pos);// 敵の設定
void HitEnemy(int nCntEnemy, int nDamage);		// 敵の当たり判定
Enemy* GetEnemy();								// 敵の取得
int GetNumEnemy();								// 敵の総数の取得

#endif
