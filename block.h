//==========================
//
// ブロック処理 [block.h]
// Author: TEAM_2
//
//==========================
#ifndef _BLOCK_H_
#define _BLOCK_H_

//***************************
// インクルードファイル宣言
//***************************
#include "main.h"

//***************************
// ブロックの種類の列挙型宣言
//***************************
typedef enum
{
	BLOCKTYPE_BOARD = 0,	// 看板タイプ
	BLOCKTYPE_BOARD2,		// 看板タイプ2
	BLOCKTYPE_BOARD3,		// 看板タイプ2
	BLOCKTYPE_MAX
}BLOCKTYPE;

//***************************
// ブロックのXファイルの宣言
//***************************
static const char* BLOCK_FILE[BLOCKTYPE_MAX] =
{
	"data\\MODEL\\kanban.x",	// 看板1
	"data\\MODEL\\kanban2.x",	// 看板2
	"data\\MODEL\\kanban3.x",	// 看板3
};

//***************************
// 構造体宣言
//***************************
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3 Vtxmax;		// 最大値を保持する変数
	D3DXVECTOR3 Vtxmin;		// 最小値を保持する変数
	D3DXVECTOR3 size;		// 大きさ
	LPD3DXMESH pMesh;		// メッシュのポインタ
	LPD3DXBUFFER pBuffMat;	// マテリアルのポインタ
	DWORD dwNumMat;			// マテリアル数
	bool bUse;				// 使用判定
	BLOCKTYPE nType;		// 種類
	D3DXVECTOR3 Scal;		// 大きさ
	LPDIRECT3DTEXTURE9 pTexture[10];	// テクスチャのポインタ
	int nidxshadow;			// 影設定用
}Block;

//**********************
// プロトタイプ宣言
//**********************
void InitBlock(void);		// ブロック初期化処理
void UninitBlock(void);		// ブロック終了処理
void UpdateBlock(void);		// ブロック更新処理
void DrawBlock(void);		// ブロック描画処理
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot, BLOCKTYPE nType);	// ブロックの設定
//void CollisionBlock(void);	// 当たり判定関数
Block* GetBlock();

#endif // !_BLOCK_H_