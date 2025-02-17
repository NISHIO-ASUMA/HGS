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
#include "item.h"
#include "billboard.h"

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

	//ビルボードの初期化
	InitBillboard();

	//ビルボード
	SetBillboard(D3DXVECTOR3(-80.0f, 85.0f, 160.0f), BILLBOARDTYPE_SPRING, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetBillboard(D3DXVECTOR3(-400.0f, 85.0f, 160.0f), BILLBOARDTYPE_SUMMER, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetBillboard(D3DXVECTOR3(-400.0f, 85.0f, -160.0f), BILLBOARDTYPE_AUTUMN, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetBillboard(D3DXVECTOR3(-80.0f, 85.0f, -160.0f), BILLBOARDTYPE_WINTER, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetBillboard(D3DXVECTOR3(600.0f, 85.0f, 160.0f), BILLBOARDTYPE_SHOP, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetBillboard(D3DXVECTOR3(280.0f, 85.0f, 160.0f), BILLBOARDTYPE_PARK, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetBillboard(D3DXVECTOR3(450.0f, 85.0f, -160.0f), BILLBOARDTYPE_SCHOOL, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetBillboard(D3DXVECTOR3(1300.0f, 85.0f, 160.0f), BILLBOARDTYPE_FOOD1, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetBillboard(D3DXVECTOR3(980.0f, 85.0f, 160.0f), BILLBOARDTYPE_FOOD2, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetBillboard(D3DXVECTOR3(980.0f, 85.0f, -160.0f), BILLBOARDTYPE_FOOD3, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetBillboard(D3DXVECTOR3(1300.0f, 85.0f, -160.0f), BILLBOARDTYPE_FOOD4, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetBillboard(D3DXVECTOR3(2000.0f, 85.0f, 160.0f), BILLBOARDTYPE_TALK, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetBillboard(D3DXVECTOR3(1680.0f, 85.0f, 160.0f), BILLBOARDTYPE_KIKAKU, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetBillboard(D3DXVECTOR3(1680.0f, 85.0f, -160.0f), BILLBOARDTYPE_KARISUMA, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetBillboard(D3DXVECTOR3(2000.0f, 85.0f, -160.0f), BILLBOARDTYPE_HYO, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

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

	SetModel(D3DXVECTOR3(2300.0f, 0.0f, 30.0f), WALLTYPE_CLEAR);		//	ゴールのプレゼント

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

	// アイテムの初期化
	InitItem();

	// プレゼントセット
	SetItem(D3DXVECTOR3(-80.0f, 20.0f, 160.0f), ITEMTYPE_SPRING);
	SetItem(D3DXVECTOR3(-400.0f, 20.0f, 160.0f), ITEMTYPE_SUMMER);
	SetItem(D3DXVECTOR3(-400.0f, 20.0f, -160.0f), ITEMTYPE_AUTUMN);
	SetItem(D3DXVECTOR3(-80.0f, 20.0f, -160.0f), ITEMTYPE_WINTER);

	SetItem(D3DXVECTOR3(600.0f, 20.0f, 160.0f), ITEMTYPE_SHOP);
	SetItem(D3DXVECTOR3(280.0f, 20.0f, 160.0f), ITEMTYPE_PARK);
	SetItem(D3DXVECTOR3(450.0f, 20.0f, -160.0f), ITEMTYPE_SCHOOL);

	SetItem(D3DXVECTOR3(1300.0f, 20.0f, 160.0f), ITEMTYPE_FOOD1);
	SetItem(D3DXVECTOR3(980.0f, 20.0f, 160.0f), ITEMTYPE_FOOD2);
	SetItem(D3DXVECTOR3(980.0f, 20.0f, -160.0f), ITEMTYPE_FOOD3);
	SetItem(D3DXVECTOR3(1300.0f, 20.0f, -160.0f), ITEMTYPE_FOOD4);

	SetItem(D3DXVECTOR3(2000.0f, 20.0f, 160.0f), ITEMTYPE_TALK);
	SetItem(D3DXVECTOR3(1680.0f, 20.0f, 160.0f), ITEMTYPE_KIKAKU);
	SetItem(D3DXVECTOR3(1680.0f, 20.0f, -160.0f), ITEMTYPE_KARISUMA);
	SetItem(D3DXVECTOR3(2000.0f, 20.0f, -160.0f), ITEMTYPE_HYO);

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

	//ビルボードの終了
	UninitBillboard();

	// プレイヤーの終了
	UninitPlayer();

	// アイテムの終了
	UninitItem();

	// エフェクトの終了
	UninitEffect();			

	// ポーズ画面の終了
	UninitPause();			

	// タイマーの終了
	UninitTimer();
}
//===================
// ゲームの更新
//===================
void UpdateGame(void)
{
	int nNum = GetScore();
	int nTime = GetTimer();
	bool bExit = GetExit();

	//プレイヤーの情報へのポインタにプレイヤーの先頭アドレスが代入される
	Player* pPlayer = GetPlayer();

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

		// アイテムの更新
		UpdateItem();


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

		//エフェクトの更新処理
		UpdateEffect();


		//タイムの更新処理
		UpdateTimer();


		//スコアの更新処理
		UpdateScore();

		//パーティクルの更新処理
		UpdateParticle();
	}

	if ((pPlayer->bDisp == false || bExit == true || nTime <= 0 ) && g_gameState != GAMESTATE_NONE)
	{
		//モード設定(リザルト画面に移行)
		g_gameState = GAMESTATE_END;
	}

	int nResultScore;
	nResultScore = GetScore();

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

	// アイテムの描画
	DrawItem();

	// メッシュフィールドの描画
	DrawMeshfield();

	// 影の描画
	DrawShadow();

	//モデルの描画処理
	DrawModel();

	//ビルボードの描画処理
	DrawBillboard();

	// プレイヤーの描画
	DrawPlayer();

	// エフェクトの描画
	DrawEffect();

	//タイマー
	DrawTimer();

	if (g_bPause == true)
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