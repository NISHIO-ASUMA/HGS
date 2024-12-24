//======================================
//
// チュートリアル処理 [tutorial.cpp]
// Author: TEAM_2
//
//======================================

//****************************
// インクルードファイル宣言
//****************************
#include "tutorial.h"
#include "fade.h"
#include "input.h"

//****************************
// グローバル変数宣言
//****************************
Tutorial g_Tutorial;										// 構造体変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;			// 頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureTutorial[TUTORIAL_MAX] = {};	// テクスチャのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorialBG = NULL;		// 背景用の頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureTutorialBG = NULL;				// 背景用のテクスチャのポインタ

//============================
// チュートリアル初期化処理
//============================
void InitTutorial(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < TUTORIAL_MAX; nCnt++)
	{// 列挙型の数の分
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			TUTORIAL_TEXTURE[nCnt],
			&g_pTextureTutorial[nCnt]);
	}

	// 背景のテクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\start.png",
		&g_pTextureTutorialBG);

	// 構造体変数の初期化
	g_Tutorial.fHeight = 0.0f;					 // 高さ
	g_Tutorial.fWidth = 0.0f;					 // 横幅
	g_Tutorial.nType = 0;						 // 種類
	g_Tutorial.pos = D3DXVECTOR3(0.0f,0.0f,0.0f);// 座標
	g_Tutorial.state = TUTORIALSTATE_NORMAL;	 // 初期状態

	// 頂点情報のポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorialBG,
		NULL);

	// 頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffTutorialBG->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	1つ目の頂点情報
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);		//	2つ目の頂点情報
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);		//	3つ目の頂点情報
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);	//	4つ目の頂点情報

	// rhwの設定(1.0fで固定)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 配置
	SetTutorial(D3DXVECTOR3(600.0f, 360.0f, 0.0f));

	// アンロック
	g_pVtxBuffTutorialBG->Unlock();
}
//============================
// チュートリアル終了処理
//============================
void UninitTutorial(void)
{
	// テクスチャの破棄
	for (int nCnt = 0; nCnt < TUTORIAL_MAX; nCnt++)
	{
		if (g_pTextureTutorial[nCnt] != NULL)
		{// NULLじゃなかったら
			g_pTextureTutorial[nCnt]->Release();
			g_pTextureTutorial[nCnt] = NULL;
		}
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffTutorial != NULL)
	{// NULLじゃなかったら
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

	// 背景テクスチャの破棄
	if (g_pTextureTutorialBG != NULL)
	{// NULLじゃなかったら
		g_pTextureTutorialBG->Release();
		g_pTextureTutorialBG = NULL;
	}
	
	// 背景頂点バッファの破棄
	if (g_pVtxBuffTutorial != NULL)
	{// NULLじゃなかったら
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}
}
//============================
// チュートリアル更新処理
//============================
void UpdateTutorial(void)
{
	if (KeyboardTrigger(DIK_RETURN))
	{
		// 画面遷移
		SetFade(MODE_GAME);
	}
}
//============================
// チュートリアル描画処理
//============================
void DrawTutorial(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorialBG, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTutorialBG);

	// チュートリアルポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);// 1個目のプレイヤーの始点(0番目～3番目)

}
//============================
// チュートリアル設定処理
//============================
void SetTutorial(D3DXVECTOR3 pos)
{
	g_Tutorial.pos = pos;		// 座標を設定
}
