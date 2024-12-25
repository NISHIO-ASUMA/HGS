//=============================
//
// リザルト処理 [result.cpp]
// Author:TEAM_2
//
//=============================

//****************************
// インクルードファイル宣言
//****************************
#include "result.h"
#include "fade.h"
#include "player.h"
#include "Timer.h"
#include "sound.h"
#include "input.h"
#include "item.h"

//***************************
// グローバル変数宣言
//***************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL; // 頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureResult= NULL;		 // テクスチャのポインタ
int g_aCount;									 // カウント
int nNumResult;
//==================
// リザルトの初期化
//==================
void InitResult(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		

	// プレイヤーの取得
	Player* pPlayer = GetPlayer();

	// タイマー情報を取得
	int nTime = GetTimer();

	// 初期化
	g_aCount = 0;
	nNumResult = 0;

	// 取得
	nNumResult = GetResultNumber();

	const char* TextureName = {};

	switch (nNumResult)
	{
	case 0:
		TextureName = "data\\TEXTURE\\result_B.png";
		break;

	case 1:
		TextureName = "data\\TEXTURE\\result_D.png";
		break;

	case 2:
		TextureName = "data\\TEXTURE\\result_S.png";
		break;

	case 3:
		TextureName = "data\\TEXTURE\\result_A.png";
		break;

	case 4:
		TextureName = "data\\TEXTURE\\result_C.png";
		break;

	case 5:
		TextureName = "data\\TEXTURE\\result_hatena.png";
		break;

	default:
		TextureName = "data\\TEXTURE\\result_hatena.png";
		break;
	}

	// テクスチャ設定
	D3DXCreateTextureFromFile(pDevice,
		TextureName ,
		&g_pTextureResult);

	// 頂点情報のポインタ
	VERTEX_2D* pVtx;		

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	// 頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 1つ目の頂点情報
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);		// 2つ目の頂点情報
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);		// 3つ目の頂点情報
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);	// 4つ目の頂点情報

	// rhwの設定(1.0fで固定)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// アンロック
	g_pVtxBuffResult->Unlock();

	// 音楽を再生
	PlaySound(SOUND_LABLE_RESULTBGM);
}
//==================
// リザルトの終了
//==================
void UninitResult(void)
{
	// 音楽を止める
	StopSound();

	// テクスチャの破棄
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}
//==================
// リザルトの更新
//==================
void UpdateResult(void)
{
	// プレイヤーの取得
	Player* pPlayer = GetPlayer();

	// 現在のフェードの取得
	FADE g_fade = GetFade();

	// カウントを加算
	g_aCount++;

	if (g_fade == FADE_NONE && (g_aCount >= 380 || KeyboardTrigger(DIK_RETURN) == true || JoyPadTrigger(JOYKEY_A) == true))
	{
		// Enterキーが押された
		// モード設定(リザルトに移動)
		SetFade(MODE_TITLE);
	}
}
//==================
// リザルトの描画
//==================
void DrawResult(void)
{
	//プレイヤーの取得
	Player* pPlayer = GetPlayer();

	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResult);

	// リザルトポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
