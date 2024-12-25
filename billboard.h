//================================
//
// ビルボード処理 [billboard.h]
// Author: TEAM_2
//
//================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//***************************
// インクルードファイル宣言
//***************************
#include "main.h"

//***************************
// マクロ定義
//***************************
#define MAX_BILLBOARD (24)    // 最大数

//*****************************
// ビルボードの種類の列挙型宣言
//*****************************
typedef enum
{
	BILLBOARDTYPE_SPRING = 0,
	BILLBOARDTYPE_SUMMER,
	BILLBOARDTYPE_AUTUMN,
	BILLBOARDTYPE_WINTER,

	BILLBOARDTYPE_SHOP,
	BILLBOARDTYPE_PARK,
	BILLBOARDTYPE_SCHOOL,

	BILLBOARDTYPE_FOOD1,
	BILLBOARDTYPE_FOOD2,
	BILLBOARDTYPE_FOOD3,
	BILLBOARDTYPE_FOOD4,

	BILLBOARDTYPE_MAX
}BILLBOARDTYPE;

//************************************
// ビルボードのテクスチャの列挙型宣言
//************************************
static const char* BILLBOARD_TEXTURE[BILLBOARDTYPE_MAX] = 
{
	"data\\TEXTURE\\00_Spring.png",
	"data\\TEXTURE\\01_Summer.png",
	"data\\TEXTURE\\02_Autumn.png",
	"data\\TEXTURE\\03_Winter.png",

	"data\\TEXTURE\\04_Shop.png",
	"data\\TEXTURE\\05_Park.png",
	"data\\TEXTURE\\06_School.png",

};

//***************************
// 構造体宣言
//***************************
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き
	D3DXVECTOR3 move;		// 移動量
	D3DXVECTOR3 dir;		// 方向ベクトル
	D3DXMATRIX  mtxWorld;	// ワールドマトリックス
	bool bUse;				// 使用判定
	int nIdxshadow;			// 影
	BILLBOARDTYPE Type;		// 種類
}Billboard;

//**********************
// プロトタイプ宣言
//**********************
void InitBillboard(void);		// ビルボード初期化処理
void UninitBillboard(void);		// ビルボード終了処理
void UpdateBillboard(void);		// ビルボード更新処理
void DrawBillboard(void);		// ビルボード描画処理
void SetBillboard(D3DXVECTOR3 pos, BILLBOARDTYPE Type, D3DXVECTOR3 rot); // ビルボード設定処理(処理によって引数追加)
#endif 

