//============================
//
// タイマー処理 [Timer.h]
// Author:TEAM_2
//
//============================
#ifndef _TIMER_H_
#define _TIMER_H_
//****************************
// インクルードファイル宣言
//****************************
#include "main.h"

//*******************************
// プロトタイプ宣言
//*******************************
void InitTimer(void);				// タイマーの初期化
void UninitTimer(void);				// タイマーの終了
void UpdateTimer(void);				// タイマーの更新
void DrawTimer(void);				// タイマーの描画
int GetTimer(void);					// タイマーの取得

#endif