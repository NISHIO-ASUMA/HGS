//==========================
//
// エフェクト処理 [effect.cpp]
// Author: TEAM_2
//
//==========================

//***************************
// インクルードファイル宣言
//***************************
#include "effect.h"

//***************************
// グローバル変数宣言
//***************************
Effect g_Effect[MAX_EFFECT];					// 構造体変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;// 頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_apTextureEffect = NULL;	// テクスチャのポインタ

//============================
// エフェクトの初期化処理
//============================
void InitEffect(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.png",
		&g_apTextureEffect);

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{// グローバル変数の初期化
		g_Effect[nCnt].bUse = false;							  // 未使用判定
		g_Effect[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		  // 座標
		g_Effect[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		  // 角度
		g_Effect[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	  // 移動量
		g_Effect[nCnt].Scall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	  // 大きさ
		g_Effect[nCnt].nLife = 0;								  // 体力
		g_Effect[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f,0.0f);	  // カラー
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	// 頂点情報のポインタ
	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		// 頂点座標の設定
		pVtx[0].pos.x = -MAX_SIZE;
		pVtx[0].pos.y = MAX_SIZE;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = MAX_SIZE;
		pVtx[1].pos.y = MAX_SIZE;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = -MAX_SIZE;
		pVtx[2].pos.y = -MAX_SIZE;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = MAX_SIZE;
		pVtx[3].pos.y = -MAX_SIZE;
		pVtx[3].pos.z = 0.0f;

		// 各頂点の法線(ベクトル)の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	 // 1つ目の法線情報
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	 // 2つ目の法線情報
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	 // 3つ目の法線情報
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	 // 4つ目の法線情報

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

		// 頂点情報分ずらす
		pVtx += 4;
	}

	// アンロック
	g_pVtxBuffEffect->Unlock();
}
//============================
// エフェクトの終了処理
//============================
void UninitEffect(void)
{
	// テクスチャの破棄
	if (g_apTextureEffect != NULL)
	{
		g_apTextureEffect->Release();
		g_apTextureEffect = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}

}
//============================
// エフェクトの更新処理
//============================
void UpdateEffect(void)
{
	// 頂点情報のポインタ
	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (!g_Effect[nCnt].bUse)
		{// 未使用状態の時
			pVtx += 4;
			continue;
		}

		// 使用状態の時
		// 移動量の更新
		g_Effect[nCnt].pos += g_Effect[nCnt].move;

		// 体力減らす
		g_Effect[nCnt].nLife--;

		if (g_Effect[nCnt].nLife <= 0)
		{// 体力が0以下なら
			g_Effect[nCnt].bUse = false;
		}

		// 頂点カラーの設定
		pVtx[0].col = g_Effect[nCnt].col;
		pVtx[1].col = g_Effect[nCnt].col;
		pVtx[2].col = g_Effect[nCnt].col;
		pVtx[3].col = g_Effect[nCnt].col;

		// 頂点情報分ずらす
		pVtx += 4;

	}

	// アンロック
	g_pVtxBuffEffect->Unlock();
}
//============================
// エフェクトの描画処理
//============================
void DrawEffect(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//αブレンディングの加算合成
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxTrans, mtxScall;

	// αテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// Zテストを有効
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_Effect[nCnt].bUse)
		{// 使われているとき

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Effect[nCnt].mtxWorld);

			// ビューマトリックスを宣言
			D3DXMATRIX mtxView;

			// ビューマトリックスの取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// カメラの逆行列を設定
			g_Effect[nCnt].mtxWorld._11 = mtxView._11;
			g_Effect[nCnt].mtxWorld._12 = mtxView._21;
			g_Effect[nCnt].mtxWorld._13 = mtxView._31;
			g_Effect[nCnt].mtxWorld._21 = mtxView._12;
			g_Effect[nCnt].mtxWorld._22 = mtxView._22;
			g_Effect[nCnt].mtxWorld._23 = mtxView._32;
			g_Effect[nCnt].mtxWorld._31 = mtxView._13;
			g_Effect[nCnt].mtxWorld._32 = mtxView._23;
			g_Effect[nCnt].mtxWorld._33 = mtxView._33;

			// 大きさを反映
			D3DXMatrixScaling(&mtxScall, g_Effect[nCnt].Scall.x, g_Effect[nCnt].Scall.y, g_Effect[nCnt].Scall.z);
			D3DXMatrixMultiply(&g_Effect[nCnt].mtxWorld, &g_Effect[nCnt].mtxWorld, &mtxScall);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Effect[nCnt].pos.x, g_Effect[nCnt].pos.y, g_Effect[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Effect[nCnt].mtxWorld, &g_Effect[nCnt].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Effect[nCnt].mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureEffect);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}

	// αテストを無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//αブレンディングを戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Zテストを戻す
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}
//============================
// エフェクトの設定処理
//============================
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, D3DXVECTOR3 Scall, int nLife)
{
	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (!g_Effect[nCnt].bUse)
		{// 未使用状態だったら
			g_Effect[nCnt].pos = pos;	// 座標
			g_Effect[nCnt].move = move; // 移動量
			g_Effect[nCnt].col = col;	// カラー
			g_Effect[nCnt].Scall = Scall;// 拡大率
			g_Effect[nCnt].nLife = nLife;// 体力
			g_Effect[nCnt].bUse = true;	 // 使用状態

			break;
		}
	}
}
