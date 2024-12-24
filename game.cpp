//===============================
//
// ゲーム全般処理 [game.cpp]
// Author:TEAM_2
// 
//===============================

//**********************************
// インクルードファイル宣言
//**********************************
#include "game.h"
#include "Player.h"
#include "input.h"
#include "fade.h"
#include "title.h"
#include "effect.h"
#include "pause.h"
#include "particle.h"
#include "camera.h"
#include "Timer.h"
#include "shadow.h"
#include "block.h"
#include "light.h"
#include "meshfield.h"
#include "meshwall.h"
#include "meshfan.h"
#include "enemy.h"
#include "score.h"
#include "rankscore.h"
#include "sound.h"

//**********************************
// グローバル変数宣言
//**********************************
GAMESTATE g_gameState = GAMESTATE_NONE;		// ゲーム状態
int g_nCounterGameState = 0;				// 状態管理カウンター
bool g_bPause = false;						// ポーズ中かどうか
bool isSelect = false;						// セレクト画面かどうか

//========================
// ゲーム画面の初期化処理
//========================
void InitGame(void)
{
	// カメラの初期化
	InitCamera();

	// メッシュフィールドの初期化
	InitMeshField();

	// メッシュのシリンダー形の初期化
	InitMeshWall();

	// メッシュドームの初期化
	InitmeshFan();

	// ライトの初期化
	InitLight();

	// 影の初期化
	InitShadow();

	// エフェクトの初期化
	InitEffect();			

	// パーティクルの初期化
	InitParticle();			

	// プレイヤーの初期化
	InitPlayer();

	// ポーズ画面の初期化
	InitPause();			

	// タイマーの初期化
	InitTimer();

	// 敵の初期化
	InitEnemy();

	// ブロックの初期化
	InitBlock();

	// スコアの初期化
	InitScore();

	g_gameState = GAMESTATE_NORMAL;	//　通常状態の設定
	g_nCounterGameState = 0;		//	カウンターの初期化
	g_bPause = false;				//	ポーズ画面の初期化(ポーズ解除)

	// 音楽を再生
	PlaySound(SOUND_LABLE_GAMEBGM);
}
//===================
//ゲームの終了
//===================
void UninitGame(void)
{
	// 音楽を止める
	StopSound();

	// スコアの保存
	SaveScore();

	// カメラの終了
	UninitCamera();

	// ライトの終了
	UninitLight();

	// 影の終了
	UninitShadow();

	// メッシュフィールドの終了
	UninitMeshField();

	 // メッシュのシリンダー形の終了
	UninitMeshWall();

	 // メッシュドームの終了
	UninitmeshFan();

	// ブロックの終了
	UninitBlock();

	// 敵の終了
	UninitEnemy();

	// プレイヤーの終了
	UninitPlayer();

	// プレイヤーの終了
	UninitPlayer();			

	// エフェクトの終了
	UninitEffect();			

	// ポーズ画面の終了
	UninitPause();			

	// タイマーの終了
	UninitTimer();

	// スコアの終了
	UninitScore();
}
//===================
// ゲームの更新
//===================
void UpdateGame(void)
{
	if (KeyboardTrigger(DIK_RETURN))
	{
		// 画面遷移
		SetFade(MODE_RESULT);
	}

	// モードの取得
	MODE nMode = GetMode();

	// プレイヤーの取得
	PLAYER* pPlayer = GetPlayer();

	// 敵の取得
	int nNum = GetNumEnemy();

	// タイマーを取得
	int nTime = GetTimer();

	if ( (nTime <= 0 || pPlayer->bDisp == false) && g_gameState != GAMESTATE_NONE)
	{
		g_gameState = GAMESTATE_END;  //終了状態
	}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL: // 通常状態
		break;

	case GAMESTATE_END:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			// カウンターを初期化
			g_nCounterGameState = 0;

			// 1秒経過
			g_gameState = GAMESTATE_NONE;		// 何もしていない状態

			// 画面遷移
			SetFade(MODE_RESULT);

			//読み込み
			ResetRanking();

			//ランキングの設定
			SetRanking(GetScore());
		}
		break;

	case GAMESTATE_PAUSE:
		//ポーズ中
		//ポーズの更新処理
		UpdatePause();
		break;

	}

	// ポーズ画面
	if (nMode == MODE_GAME)
	{
		if (KeyboardTrigger(DIK_P) == true || JoypadTrigger(JOYKEY_START))
		{// pが押された or startボタン
			// 有効か無効か判定
			g_bPause = g_bPause ? false : true;

			// 音楽再生
			PlaySound(SOUND_LABLE_PAUSEMENU);
		}
	}

	if (g_bPause == true)
	{// g_bPauseがtrueの時
		g_gameState = GAMESTATE_PAUSE;
	}
	else if (!g_bPause && g_gameState != GAMESTATE_SELECT)
	{
		g_gameState = GAMESTATE_NORMAL;
	}

	if (g_gameState == GAMESTATE_NORMAL)
	{//ポーズ中で無ければ
		
		// カメラの更新
		UpdateCamera();

		// ブロックの更新
		UpdateBlock();

		// ライトの更新
		UpdateLight();

		// メッシュフィールドの更新
		UpdateMeshField();

		// メッシュのシリンダー形の更新
		UpdateMeshWall();

		// メッシュドームの更新
		UpdatemeshFan();

		// 影の更新
		UpdateShadow();

		// 敵の更新
		UpdateEnemy();

		// プレイヤーの更新
		UpdatePlayer();

		// エフェクトの更新
		UpdateEffect();		

		// パーティクルの更新
		UpdateParticle();	

		// タイマーの更新
		UpdateTimer();

		// スコアの更新
		UpdateScore();
	}
}
//===================
//ゲーム画面の描画処理
//===================
void DrawGame(void)
{
	// カメラのセット
	SetCamera();

	// メッシュフィールドの描画
	DrawMeshField();

	// メッシュドームの描画
	DrawmeshFan();

	// メッシュのシリンダー形の描画
	DrawMeshWall();

	// 影の描画
	DrawShadow();

	// ブロックの描画
	DrawBlock();

	// 敵の描画
	DrawEnemy();

	// プレイヤーの描画
	DrawPlayer();

	// エフェクトの描画
	DrawEffect();

	//タイマー
	DrawTimer();

	// スコアの描画
	DrawScore();

	if (g_gameState == GAMESTATE_PAUSE)
	{
		//ポーズ中
		//ポーズの描画
		DrawPause();
	}

}
//=====================
// ポーズの有効無効設定
//=====================
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}
//=====================
// セレクトの有効無効設定
//=====================
void SetEnableSelect(bool isSelectMenu)
{
	isSelect = isSelectMenu;
}
//=====================
// ゲームの状態設定処理
//=====================
void SetGamestate(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}
//=====================
// ゲームの状態取得処理
//=====================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}