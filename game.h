//=============================
//
// ゲーム全般処理 [game.h]
// Author:TEAM_2
//
//============================
#ifndef _GAME_H_
#define _GAME_H_

//**********************************
// インクルードファイル宣言
//**********************************
#include "main.h"

//**********************************
// ゲームの状態列挙型宣言
//**********************************
typedef enum
{
	GAMESTATE_NONE = 0,		// 何もしていない状態
	GAMESTATE_NORMAL,		// 通常状態
	GAMESTATE_END,			// 終了状態
	GAMESTATE_PAUSE,		// ポーズ状態
	GAMESTATE_SELECT,		// セレクト画面状態
	GAMESTATE_MAX
}GAMESTATE;

//**********************************
// プロトタイプ宣言
//**********************************

void InitGame(void);					// ゲームの初期化
void UninitGame(void);					// ゲームの終了
void UpdateGame(void);					// ゲームの更新
void DrawGame(void);					// ゲームの描画
void SetGamestate(GAMESTATE state);		// ゲームの状態の設定
GAMESTATE GetGameState(void);			// ゲームの状態の取得
void SetEnablePause(bool bPause);		// ポーズメニューの設定
void SetEnableSelect(bool isSelectMenu);// セレクトメニューの設定

#endif