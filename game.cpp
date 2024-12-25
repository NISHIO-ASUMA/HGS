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
#include "bullet.h"

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
	//モデルの初期化処理
	InitModel();


	//モデル
	SetModel(D3DXVECTOR3(-220.0f, 0.0f, 385.0f), WALLTYPE_OKU);		//	ルーム1の奥壁
	SetModel(D3DXVECTOR3(-560.0f, 0.0f, 60.0f), WALLTYPE_HIDARI);	//	ルーム1の左壁
	SetModel(D3DXVECTOR3(-220.0f, 0.0f, -305.0f), WALLTYPE_TEMAE);	//	ルーム1の手前壁
	SetModel(D3DXVECTOR3(120.0f, 0.0f, 230.0f), WALLTYPE_MIGI);		//	ルーム1の右壁奥
	SetModel(D3DXVECTOR3(120.0f, 0.0f, -150.0f), WALLTYPE_MIGI);	//	ルーム1の右壁手前

	SetModel(D3DXVECTOR3(460.0f, 0.0f, 385.0f), WALLTYPE_OKU);		//	ルーム2の奥壁
	SetModel(D3DXVECTOR3(460.0f, 0.0f, -305.0f), WALLTYPE_TEMAE);	//	ルーム2の手前壁
	SetModel(D3DXVECTOR3(800.0f, 0.0f, 230.0f), WALLTYPE_MIGI);		//	ルーム2の右壁奥
	SetModel(D3DXVECTOR3(800.0f, 0.0f, -150.0f), WALLTYPE_MIGI);	//	ルーム2の右壁手前

	SetModel(D3DXVECTOR3(1140.0f, 0.0f, 385.0f), WALLTYPE_OKU);		//	ルーム3の奥壁
	SetModel(D3DXVECTOR3(1140.0f, 0.0f, -305.0f), WALLTYPE_TEMAE);	//	ルーム3の手前壁
	SetModel(D3DXVECTOR3(1480.0f, 0.0f, 230.0f), WALLTYPE_MIGI);	//	ルーム3の右壁奥
	SetModel(D3DXVECTOR3(1480.0f, 0.0f, -150.0f), WALLTYPE_MIGI);	//	ルーム3の右壁手前

	SetModel(D3DXVECTOR3(1820.0f, 0.0f, 385.0f), WALLTYPE_OKU);		//	ルーム4の奥壁
	SetModel(D3DXVECTOR3(1820.0f, 0.0f, -305.0f), WALLTYPE_TEMAE);	//	ルーム4の手前壁
	SetModel(D3DXVECTOR3(2160.0f, 0.0f, 230.0f), WALLTYPE_MIGI);	//	ルーム4の右壁奥
	SetModel(D3DXVECTOR3(2160.0f, 0.0f, -150.0f), WALLTYPE_MIGI);	//	ルーム4の右壁手前

	SetModel(D3DXVECTOR3(120.0f, 0.0f, 40.0f), WALLTYPE_DOOR1);		//	ルーム1のドア
	SetModel(D3DXVECTOR3(800.0f, 0.0f, 40.0f), WALLTYPE_DOOR2);		//	ルーム2のドア
	SetModel(D3DXVECTOR3(1480.0f, 0.0f, 40.0f), WALLTYPE_DOOR3);	//	ルーム3のドア
	SetModel(D3DXVECTOR3(2160.0f, 0.0f, 40.0f), WALLTYPE_DOOR4);	//	ルーム4のドア

	SetModel(D3DXVECTOR3(2260.0f, 0.0f, 140.0f), WALLTYPE_GOALOKU);		//	ゴールの奥壁
	SetModel(D3DXVECTOR3(2260.0f, 0.0f, -60.0f), WALLTYPE_GOALTEMAE);	//	ゴールの手前壁
	SetModel(D3DXVECTOR3(2370.0f, 0.0f, 30.0f), WALLTYPE_GOALMIGI);		//	ゴールの右壁

	// カメラの初期化
	InitCamera();

	// メッシュフィールドの初期化
	InitMeshfield();

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

	//// 敵の初期化
	//InitEnemy();

	//// ブロックの初期化
	//InitBlock();

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
	UninitMeshfield();

	 // メッシュのシリンダー形の終了
	UninitMeshWall();

	 // メッシュドームの終了
	UninitmeshFan();

	//モデルの終了処理
	UninitModel();

	//// ブロックの終了
	//UninitBlock();

	//// 敵の終了
	//UninitEnemy();

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
	int nNum = GetScore();
	//int nTime = GetTime();
	//bool bExit = GetExit();

	Player* pPlayer = GetPlayer();//プレイヤーの情報へのポインタにプレイヤーの先頭アドレスが代入される

	if (KeyboardTrigger(DIK_P) == true || JoyPadTrigger(JOYKEY_START) == true)
	{//ESCAPE(ポーズ)キーが押された
		g_bPause = g_bPause ? false : true;

		//PlaySound(SOUND_LABEL_PAUSE);

	}

	if (g_bPause == true)
	{//ポーズ中

		//ポーズの更新処理
		UpdatePause();

	}
	else
	{

		//プレイヤーの更新処理
		UpdatePlayer();


		////敵の更新処理
		//UpdateEnemy();


		////メッシュフィールドの更新処理
		//UpdateMeshfield();


		////メッシュシリンダーの更新処理
		//UpdateMeshcylinder();


		//カメラの更新処理
		UpdateCamera();


		//ライトの更新処理
		UpdateLight();


		//モデルの更新処理
		UpdateModel();


		//影の更新処理
		UpdateShadow();


		//弾の更新処理
		UpdateBullet();


		////ビルボードの更新処理
		//UpdateBillboard();


		////壁の更新処理
		//UpdateWall();


		//エフェクトの更新処理
		UpdateEffect();


		////タイムの更新処理
		//UpdateTime();


		//スコアの更新処理
		UpdateScore();


		////リザルトスコアの更新処理
		//UpdateResultScore();


		//パーティクルの更新処理
		UpdateParticle();

		//if (KeyboardTrigger(DIK_F5) == true)
		//{
		//	onWireFrame();
		//}
		//else if (KeyboardTrigger(DIK_F6) == true)
		//{
		//	offWireFrame();
		//}
	}

	//bool bEnd = GetEnd();

	if ((pPlayer->bDisp == false /*|| bExit == true*/ /*|| nTime <= 0*/ /*|| bEnd == true*/) && g_gameState != GAMESTATE_NONE)
	{

		//モード設定(リザルト画面に移行)
		g_gameState = GAMESTATE_END;

	}

	int nResultScore;
	nResultScore = GetScore();
	//nTime = GetTime();

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL://通常状態
		break;

	case GAMESTATE_END://終了状態
		g_nCounterGameState++;

		if (g_nCounterGameState >= 60)
		{

			g_nCounterGameState = 0;

			g_gameState = GAMESTATE_NONE;

			//モード設定(リザルト画面に移行)
			SetFade(MODE_RESULT);

			//if (bExit == true)
			//{

				////タイムに応じてスコア加算
				//AddScore((nTime * GetScore()) * 0.2f);


				////リザルトスコアの設定
				//SetResultScore(GetScore());


				//ランキングのリセット
				ResetRanking();


				//ランキングの設定
				SetRanking(GetScore());

			//}

		}
		break;
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
	DrawMeshfield();

	//// メッシュドームの描画
	//DrawmeshFan();

	//// メッシュのシリンダー形の描画
	//DrawMeshWall();

	// 影の描画
	DrawShadow();

	//モデルの描画処理
	DrawModel();

	//// ブロックの描画
	//DrawBlock();

	//// 敵の描画
	//DrawEnemy();

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