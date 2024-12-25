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

	ITEMTYPE_SHOP,			// お店
	ITEMTYPE_PARK,			// 公園
	ITEMTYPE_SCHOOL,		// 学校

	ITEMTYPE_FOOD1,			// 三色団子
	ITEMTYPE_FOOD2,			// スイカ
	ITEMTYPE_FOOD3,			// サツマイモ
	ITEMTYPE_FOOD4,			// みかん

	ITEMTYPE_TALK,			// トーク
	ITEMTYPE_KIKAKU,		// 企画
	ITEMTYPE_KARISUMA,		// カリスマ
	ITEMTYPE_HYO,			// 表現

	ITEMTYPE_MAX
}ITEMTYPE;

//*********************************
// モデルの種類情報
//*********************************
static const char* ITEM_MODEL[ITEMTYPE_MAX] =
{
	"data\\MODEL\\present_box.x",
	"data\\MODEL\\present_box.x",
	"data\\MODEL\\present_box.x",
	"data\\MODEL\\present_box.x",
	"data\\MODEL\\present_box.x",
	"data\\MODEL\\present_box.x",
	"data\\MODEL\\present_box.x",
	"data\\MODEL\\present_box.x",
	"data\\MODEL\\present_box.x",
	"data\\MODEL\\present_box.x",
	"data\\MODEL\\present_box.x",
	"data\\MODEL\\present_box.x",
	"data\\MODEL\\present_box.x",
	"data\\MODEL\\present_box.x",
	"data\\MODEL\\present_box.x",

};

//*********************************
// モデル設定情報
//*********************************
typedef struct
{
	LPD3DXMESH pMesh;					   // メッシュのポインタ
	LPD3DXBUFFER pBuffMat;				   // マテリアルのポインタ
	DWORD dwNumMat;					       // マテリアル数
	LPDIRECT3DTEXTURE9 pTexture[ITEMTYPE_MAX]; // テクスチャのポインタ
}ItemModel;

//*********************************
// アイテムの構造体宣言
//*********************************
typedef struct
{
	D3DXVECTOR3 pos; // 座標
	D3DXVECTOR3 rot; // 角度
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
	ITEMTYPE Type;	 // 種類
	ItemModel aModel[ITEMTYPE_MAX]; // モデル情報
	bool bUse;       // 使用判定
	int nIdxshadow;  // 影
	int nLife;		 // 体力
}Item;

//*********************************
// プロトタイプ宣言
//*********************************
void InitItem();				// 初期化処理
void UninitItem();				// 終了処理
void UpdateItem();				// 更新処理
void DrawItem();				// 描画処理
void SetItem(D3DXVECTOR3 pos, ITEMTYPE Type);	// 設定処理
void HitItem(int nCnt, int nDamage); // ヒット処理
int GetResultNumber();			// リザルト番号
Item* GetItem();				// 取得処理
bool ItemGet1(void);
bool ItemGet2(void);
bool ItemGet3(void);
bool ItemGet4(void);

#endif