//=================================
//
// タイトル処理 [title.h]
// Author: TEAM_2
//
//=================================
#ifndef _TITLE_H_
#define _TITLE_H_

//****************************
// インクルードファイル宣言
//****************************
#include "main.h"
#include "input.h"
#include "fade.h"

//********************************
// タイトルの状態列挙型宣言
//********************************
typedef enum
{
	TITLESTATE_NORMAL = 0,	// 通常状態
	TITLESTATE_FLASH,		// 点滅状態
	TITLESTATE_MAX
}TITLESTATE;

//*************************************
// タイトルのテクスチャ列挙型宣言
//*************************************
typedef enum
{
	TITLE_FIRST = 0,					//1つ目のタイトル
	TITLE_SECOND,						//2つ目のタイトル
	TITLE_MAX
}TITLE;

static const char* TITLE_TEXTURE[TITLE_MAX] =
{
	"data\\TEXTURE\\tutorial101.png",
	"data\\TEXTURE\\Gamestart.png",
};
//****************************
// タイトル構造体宣言
//****************************
typedef struct
{
	D3DXVECTOR3 pos;			// 座標
	int nType;					// 種類
	float fWidth;				// 横幅
	float fHeight;				// 高さ
	TITLESTATE state;			// 状態変数
	bool bUse;					// 使用状態
}Title;

//**********************
// プロトタイプ宣言
//**********************
void InitTitle(void);						// タイトルの初期化
void UninitTitle(void);						// タイトルの終了
void UpdateTitle(void);						// タイトルの更新
void DrawTitle(void);						// タイトルの描画
#endif