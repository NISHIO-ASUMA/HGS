//=================================
//
// タイトル処理 [title.cpp]
// Author: TEAM_2
//
//=================================

//***************************
// インクルードファイル宣言
//***************************
#include "Title.h"
#include "sound.h"

//***************************
// プロトタイプ宣言
//***************************
void SetTitle(int nType, D3DXVECTOR3 pos);	// タイトルの設定
void TitleFlash(int nType);					// タイトルの点滅

//***************************
// グローバル変数宣言
//***************************
Title g_Title[TITLE_MAX];								// 構造体変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;			// 頂点バッファのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleback = NULL;		// タイトル背景
														   
LPDIRECT3DTEXTURE9 g_pTextureTitle[TITLE_MAX] = {};		// テクスチャのポインタ
LPDIRECT3DTEXTURE9 g_pTextureTitleback = NULL;			// タイトル背景テクスチャのポインタ

int g_nCntTitleAnim;				// タイトル状態
int g_nPatternAnim;					// 状態パターン
int g_aTimeCount;					// タイムカウント
int g_aSelect;						// 選択用の変数

//===========================
// タイトル初期化処理
//===========================
void InitTitle(void)
{
	// デバイスへのポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点情報のポインタ
	VERTEX_2D* pVtx;				

	// 背景テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Title0.png",
		&g_pTextureTitleback);

	for (int nCnt = 0; nCnt < TITLE_MAX; nCnt++)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			TITLE_TEXTURE[nCnt],
			&g_pTextureTitle[nCnt]);
	}

	// 構造体変数の初期化
	for (int nCnt = 0; nCnt < TITLE_MAX; nCnt++)
	{
		g_Title[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// 座標
		g_Title[nCnt].nType = 0;						  // 種類
		g_Title[nCnt].fHeight = 0.0f;					  // 高さ
		g_Title[nCnt].fWidth = 0.0f;					  // 横幅
		g_Title[nCnt].state = TITLESTATE_NORMAL;		  // 状態
		g_Title[nCnt].bUse = false;						  // 未使用判定
	}

	g_nCntTitleAnim = 0;		// タイトル状態用
	g_nPatternAnim = 0;			// 状態パターン用
	g_aTimeCount = 0;			// タイムカウント用
	g_aSelect = TITLE_FIRST;	// 初期の選択状態

	//==================
	//タイトル背景
	//==================
	
	// 頂点バッファの生成 背景
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitleback,
		NULL);

	// 頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffTitleback->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// アンロック
	g_pVtxBuffTitleback->Unlock();

	//==================
	//タイトル描画
	//==================

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TITLE_MAX,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	// 頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < TITLE_MAX; nCntTitle++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 1つ目の頂点情報
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 2つ目の頂点情報
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 3つ目の頂点情報
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 4つ目の頂点情報

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

		// 頂点情報をずらす
		pVtx += 4;
	}

	// セット
	SetTitle(TITLE_FIRST, D3DXVECTOR3(650.0f, 400.0f, 0.0f));	// タイトル1
	SetTitle(TITLE_SECOND, D3DXVECTOR3(650.0f, 550.0f, 0.0f));	// タイトル2

	//アンロック
	g_pVtxBuffTitle->Unlock();

	// 音楽再生
	PlaySound(SOUND_LABEL_TITLEBGM);
}
//===================
// タイトルの終了処理
//===================
void UninitTitle(void)
{
	// サウンドの破棄
	StopSound();

	//=======================
	// タイトルの背景終了処理
	//=======================

	// テクスチャの破棄
	if (g_pTextureTitleback != NULL)
	{
		g_pTextureTitleback->Release();
		g_pTextureTitleback = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffTitleback != NULL)
	{
		g_pVtxBuffTitleback->Release();
		g_pVtxBuffTitleback = NULL;
	}

	//==================
	// タイトルの終了
	//==================

	for (int nCntTitle = 0; nCntTitle < TITLE_MAX; nCntTitle++)
	{
		// テクスチャの破棄
		if (g_pTextureTitle[nCntTitle] != NULL)
		{
			g_pTextureTitle[nCntTitle]->Release();
			g_pTextureTitle[nCntTitle] = NULL;
		}
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

}
//=======================
// タイトルの更新処理
//=======================
void UpdateTitle(void)
{
	// 現在の状態のフェードを取得
	FADE g_fade = GetFade();		

	// 頂点情報のポインタ
	VERTEX_2D* pVtx;

	g_aTimeCount++;//カウント加算

	if (g_aTimeCount >= 600)
	{// タイマーカウントが上限に達したら
		// 画面遷移
		SetFade(MODE_RANKING);
	}

	// 頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < TITLE_MAX; nCount++)
	{
		// 頂点カラーを設定(白)
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// 頂点情報をずらす
		pVtx += 4;
	}

	// pVtxを戻す
	pVtx -= 4 * TITLE_MAX;		

	// メニューの選択
	if (KeyboardTrigger(DIK_UP) == true || JoypadTrigger(JOYKEY_UP) == true || KeyboardTrigger(DIK_W) == true)
	{// UPキー or パッドの上キー or Wキーが押された
		
		g_aSelect--;//　デクリメント

		if (g_aSelect < TITLE_FIRST)
		{//　TITLE_FIRSTがセレクトより小さかったら
			// 選択状態を2個目に設定
			g_aSelect = TITLE_SECOND;
		}
	}

	else if (KeyboardTrigger(DIK_DOWN) == true || JoypadTrigger(JOYKEY_DOWN) == true || KeyboardTrigger(DIK_S) == true)
	{// DOWNキー or パッドの下キー or Sキーが押された
		
		g_aSelect++;// インクリメント

		if (g_aSelect >= TITLE_MAX)
		{//　TITLE_MAXがセレクトより小さかったら
			// 選択状態を1個目に設定	
			g_aSelect = TITLE_FIRST;
		}
	}

	// 選択肢
	pVtx += 4 * g_aSelect;							

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

	// アンロック
	g_pVtxBuffTitle->Unlock();

	if (g_fade == FADE_NONE && (KeyboardTrigger(DIK_RETURN) == true || JoypadTrigger(JOYKEY_A) == true))
	{
		// 音楽を再生
		PlaySound(SOUND_LABLE_ENTERSE);

		// エンターキーが押された or Aボタンが押された
		// 各画面に移動
		switch (g_aSelect)
		{
		case TITLE_FIRST:

			//チュートリアルに移行
			SetFade(MODE_TUTORIAL);

			// Enterキーが押された
			for (int nCntTitle = 0; nCntTitle < TITLE_MAX; nCntTitle++)
			{
				if (g_Title[nCntTitle].bUse == true && g_Title[nCntTitle].nType == TITLE_FIRST)
				{// 使用状態かつ一個目のタイトル
					// 点滅させる
					g_Title[nCntTitle].state = TITLESTATE_FLASH;
				}
			}
			break;

		case TITLE_SECOND:

			// ゲーム画面に移行
			SetFade(MODE_GAME);
			for (int nCntTitle = 0; nCntTitle < TITLE_MAX; nCntTitle++)
			{
				if (g_Title[nCntTitle].bUse == true && g_Title[nCntTitle].nType == TITLE_SECOND)
				{// 使用状態かつ二個目のタイトル
					// 点滅させる
					g_Title[nCntTitle].state = TITLESTATE_FLASH;
				}
			}

			break;

		}
	}

	TitleFlash(TITLE_FIRST);	// タイトルの点滅
	TitleFlash(TITLE_SECOND);	// タイトルの点滅
}
//===================
// タイトルの描画処理
//===================
void DrawTitle(void)
{
	// デバイスへのポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	

	//=====================
	// タイトル背景の描画
	//=====================

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitleback, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitleback);

	// タイトルポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//==================
	// タイトルの描画
	//==================

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < TITLE_MAX; nCntTitle++)
	{
		// テクスチャの設定(タイプ分設定)
		pDevice->SetTexture(0, g_pTextureTitle[g_Title[nCntTitle].nType]);

		// タイトルポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);
	}

}
//======================
// タイトルの設定処理
//======================
void SetTitle(int nType, D3DXVECTOR3 pos)
{
	// 頂点情報のポインタ
	VERTEX_2D* pVtx;		

	// 頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < TITLE_MAX; nCnt++)
	{
		if (!g_Title[nCnt].bUse)
		{// 使われていたら
			g_Title[nCnt].nType = nType;
			g_Title[nCnt].pos = pos;
			g_Title[nCnt].bUse = true;

			//場合分け
			switch (nType)
			{
			case TITLE_FIRST:
				// 高さ,横幅を設定
				g_Title[nCnt].fHeight = 100.0f;	// 高さ
				g_Title[nCnt].fWidth = 450.0f;	// 横幅
				break;

			case TITLE_SECOND:
				// 高さ,横幅を設定
				g_Title[nCnt].fHeight = 100.0f;	// 高さ
				g_Title[nCnt].fWidth = 400.0f;	// 横幅
				break;
			}

			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_Title[nCnt].pos.x - g_Title[nCnt].fWidth * 0.5f, g_Title[nCnt].pos.y - g_Title[nCnt].fHeight * 0.5f, 0.0f);		//1つ目の頂点情報
			pVtx[1].pos = D3DXVECTOR3(g_Title[nCnt].pos.x + g_Title[nCnt].fWidth * 0.5f, g_Title[nCnt].pos.y - g_Title[nCnt].fHeight * 0.5f, 0.0f);		//2つ目の頂点情報
			pVtx[2].pos = D3DXVECTOR3(g_Title[nCnt].pos.x - g_Title[nCnt].fWidth * 0.5f, g_Title[nCnt].pos.y + g_Title[nCnt].fHeight * 0.5f, 0.0f);		//3つ目の頂点情報
			pVtx[3].pos = D3DXVECTOR3(g_Title[nCnt].pos.x + g_Title[nCnt].fWidth * 0.5f, g_Title[nCnt].pos.y + g_Title[nCnt].fHeight * 0.5f, 0.0f);		//4つ目の頂点情報

			break;

		}

		// 頂点情報分ずらす
		pVtx += 4;

	}
	// アンロック
	g_pVtxBuffTitle->Unlock();

}
//==============================
// タイトルの点滅
//==============================
void TitleFlash(int nType)
{
	//頂点情報のポインタ
	VERTEX_2D* pVtx = 0;		

	// 頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < TITLE_MAX; nCntTitle++)
	{
		if (g_Title[nCntTitle].bUse == true && g_Title[nCntTitle].state == TITLESTATE_FLASH)
		{// タイトルが使われていて状態が点滅状態の時

			// カウンターを加算
			g_nCntTitleAnim++;				

			if (g_nCntTitleAnim == 5)		
			{// 5の時
				// 頂点カラーの設定(透明)
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);

			}

			else if (g_nCntTitleAnim == 10)	
			{// 10の時
				// 頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// 初期値に戻す
				g_nCntTitleAnim = 0;		
			}
		}

		// 頂点情報分ずらす
		pVtx += 4;
	}
	// アンロック
	g_pVtxBuffTitle->Unlock();

}
