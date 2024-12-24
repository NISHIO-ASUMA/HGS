//===========================
//
// 爆発処理 [explosion.cpp]
// Author:TEAM_2
//
//===========================

//***************************
// インクルードファイル宣言
//***************************
#include "explosion.h"

//*******************************
// グローバル変数宣言
//*******************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	// 頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;		// テクスチャのポインタ
Explosion g_Explosion[MAX_EXPLOSION];				// 爆発の情報

//============================
// 爆発の初期化処理
//============================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;// デバイスへのポインタ

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&g_pTextureExplosion);

	// 爆発情報の初期化
	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_Explosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 座標
		g_Explosion[nCntExplosion].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 角度
		g_Explosion[nCntExplosion].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// 移動量
		g_Explosion[nCntExplosion].nCounterAnimExplosion = 0;			// カウンターの初期化
		g_Explosion[nCntExplosion].nPatternAnimExplosion = 0;			// パターンの初期化
		g_Explosion[nCntExplosion].bUse = false;						// 未使用状態
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	// 頂点情報のポインタ
	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		// 頂点座標の設定
		pVtx[0].pos.x = g_Explosion[nCnt].pos.x - 30.0f;
		pVtx[0].pos.y = g_Explosion[nCnt].pos.y - 30.0f;
		pVtx[0].pos.z = g_Explosion[nCnt].pos.z;

		pVtx[1].pos.x = g_Explosion[nCnt].pos.x - 30.0f;
		pVtx[1].pos.y = g_Explosion[nCnt].pos.y + 30.0f;
		pVtx[1].pos.z = g_Explosion[nCnt].pos.z;

		pVtx[2].pos.x = g_Explosion[nCnt].pos.x + 30.0f;
		pVtx[2].pos.y = g_Explosion[nCnt].pos.y - 30.0f;
		pVtx[2].pos.z = g_Explosion[nCnt].pos.z;

		pVtx[3].pos.x = g_Explosion[nCnt].pos.x + 30.0f;
		pVtx[3].pos.y = g_Explosion[nCnt].pos.y + 30.0f;
		pVtx[3].pos.z = g_Explosion[nCnt].pos.z;

		// 各頂点の法線(ベクトル)の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);			// 1つ目の法線情報
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);			// 2つ目の法線情報
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);			// 3つ目の法線情報
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);			// 4つ目の法線情報

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;	//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロック
	g_pVtxBuffExplosion->Unlock();

}
//============================
// 爆発の終了処理
//============================
void UninitExplosion(void)
{
	// テクスチャの破棄
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}

}
//============================
// 爆発の更新処理
//============================
void UpdateExplosion(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点情報のポインタ
	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		// アニメーションカウントを加算
		g_Explosion[nCnt].nCounterAnimExplosion++;

		if (g_Explosion[nCnt].bUse)
		{
			if (g_Explosion[nCnt].nCounterAnimExplosion >= 2)
			{// カウントが最大値になったら
				g_Explosion[nCnt].nCounterAnimExplosion = NULL;		// カウンターを初期値に戻す

				g_Explosion[nCnt].nPatternAnimExplosion++;			// パターンナンバーを更新

				//頂点座標の更新
				pVtx[0].tex = D3DXVECTOR2(0.0f + g_Explosion[nCnt].nPatternAnimExplosion * 0.125f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.125f + g_Explosion[nCnt].nPatternAnimExplosion * 0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + g_Explosion[nCnt].nPatternAnimExplosion * 0.125f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f + g_Explosion[nCnt].nPatternAnimExplosion * 0.125f, 1.0f);

			}

			if (g_Explosion[nCnt].nPatternAnimExplosion > 8)
			{// パターン数が上限に達したら
				g_Explosion[nCnt].nPatternAnimExplosion = 0;	// パターンナンバーを初期値に戻す
				g_Explosion[nCnt].bUse = false;					// 未使用判定
			}

		}
		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffExplosion->Unlock();

}
//============================
// 爆発の描画処理
//============================
void DrawExplosion(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxRot, mtxTrans;

	// ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		if (g_Explosion[nCnt].bUse == true)
		{// 使われているとき

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Explosion[nCnt].mtxWorld);

			// ビューマトリックスを宣言
			D3DXMATRIX mtxView;

			// ビューマトリックスの取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// カメラの逆行列を設定
			g_Explosion[nCnt].mtxWorld._11 = mtxView._11;
			g_Explosion[nCnt].mtxWorld._12 = mtxView._21;
			g_Explosion[nCnt].mtxWorld._13 = mtxView._31;
			g_Explosion[nCnt].mtxWorld._21 = mtxView._12;
			g_Explosion[nCnt].mtxWorld._22 = mtxView._22;
			g_Explosion[nCnt].mtxWorld._23 = mtxView._32;
			g_Explosion[nCnt].mtxWorld._31 = mtxView._13;
			g_Explosion[nCnt].mtxWorld._32 = mtxView._23;
			g_Explosion[nCnt].mtxWorld._33 = mtxView._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Explosion[nCnt].pos.x, g_Explosion[nCnt].pos.y, g_Explosion[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Explosion[nCnt].mtxWorld, &g_Explosion[nCnt].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Explosion[nCnt].mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureExplosion);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);

		}
	}
	// ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}
//============================
// 爆発の設定処理
//============================
void SetExplosion(D3DXVECTOR3 pos)
{	
	for (int nCnt = 0; nCnt < MAX_EXPLOSION; nCnt++)
	{
		if (g_Explosion[nCnt].bUse == false)
		{// 未使用状態なら
			g_Explosion[nCnt].pos = pos;	// 座標
			g_Explosion[nCnt].bUse = true;	// 使用判定

			break;
		}
	}
}
