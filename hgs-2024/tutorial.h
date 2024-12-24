//=================================
//
// チュートリアル処理 [tutorial.h]
// Author: TEAM_2
//
//=================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//****************************
// インクルードファイル宣言
//****************************
#include "main.h"

//********************************
// チュートリアルの状態列挙型宣言
//********************************
typedef enum
{
	TUTORIALSTATE_NORMAL = 0,	// 通常状態
	TUTORIALSTATE_FLASH,		// 点滅状態
	TUTORIALSTATE_MAX			
}TUTORIALSTATE;

//*************************************
// チュートリアルのテクスチャ列挙型宣言
//*************************************
typedef enum
{
	TUTORIALTEX_ONE = 0,
	TUTORIALTEX_TWO,
	TUTORIAL_MAX
}TUTORIALTEX;

static const char* TUTORIAL_TEXTURE[TUTORIAL_MAX] =
{
	"data\\TEXTURE\\reef.jpeg",
	"data\\TEXTURE\\reef.jpeg",
};
//****************************
// チュートリアル構造体宣言
//****************************
typedef struct
{
	D3DXVECTOR3 pos;			// 座標
	int nType;					// 種類
	float fWidth;				// 横幅
	float fHeight;				// 高さ
	TUTORIALSTATE state;		// 状態変数
}Tutorial;

//**********************
// プロトタイプ宣言
//**********************
void InitTutorial(void);		// チュートリアルの初期化
void UninitTutorial(void);		// チュートリアルの終了
void UpdateTutorial(void);		// チュートリアルの更新
void DrawTutorial(void);		// チュートリアルの描画
void SetTutorial(D3DXVECTOR3 pos); // チュートリアルの設定
#endif