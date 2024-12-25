//================================
// 
// アイテム処理 [item.h]
// Author : TEAM_2
// 
//================================
#ifndef _ITEM_H_
#define _ITEM_H_

//*********************************
// インクルードファイル宣言
//*********************************
#include "main.h"

//*********************************
// 種類の構造体宣言
//*********************************
typedef enum
{
	ITEMTYPE_SPRING = 0,	// 春
	ITEMTYPE_SUMMER,		// 夏
	ITEMTYPE_AUTUMN,		// 秋
	ITEMTYPE_WINTER,		// 冬
	ITEMTYPE_MAX
}ITEMTYPE;

//*********************************
// モデルの種類情報
//*********************************
static const char* ITEM_MODEL[ITEMTYPE_MAX] =
{

};

//*********************************
// モデル設定情報
//*********************************
typedef struct
{
	LPD3DXMESH pMeshEnemy;					   // メッシュのポインタ
	LPD3DXBUFFER pBuffMatEnemy;				   // マテリアルのポインタ
	DWORD dwNumMatEnemy;					   // マテリアル数
	LPDIRECT3DTEXTURE9 pTexture[ITEMTYPE_MAX]; // テクスチャのポインタ
}ItemModel;

//*********************************
// アイテムの構造体宣言
//*********************************
typedef struct
{
	D3DXVECTOR3 pos; // 座標
	D3DXVECTOR3 rot; // 角度
	bool bUse;       // 使用判定
	ITEMTYPE Type;	 // 種類
	ItemModel aModel[ITEMTYPE_MAX]; // モデル情報
}Item;

//*********************************
// プロトタイプ宣言
//*********************************
void InitItem();				// 初期化処理
void UninitItem();				// 終了処理
void UpdateItem();				// 更新処理
void DrawItem();				// 描画処理
void SetItem(D3DXVECTOR3 pos, ITEMTYPE Type);	// 設定処理
void LoadItem();				// 読み込み

#endif