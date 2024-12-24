//==========================
//
// バレッド処理 [bullet.cpp]
// Author: TEAM_2
//
//==========================

//***************************
// インクルードファイル宣言
//***************************
#include "bullet.h"
#include "shadow.h"
#include "explosion.h"
#include "particle.h"

//*****************************
// グローバル変数宣言
//*****************************
Bullet g_Bullet[MAX_BULLET];						// 構造体変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// 頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_apTextureBullet = NULL;		// テクスチャのポインタ

//=========================
//　バレット初期化処理
//=========================
void InitBullet(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスを取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_apTextureBullet);


	// グローバル変数の初期化
	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		g_Bullet[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCnt].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCnt].dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCnt].bUse = false;
		g_Bullet[nCnt].nLife = 10;
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	// 頂点情報のポインタ
	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		// 頂点座標の設定
		pVtx[0].pos.x = g_Bullet[nCntBullet].pos.x - 3.0f;
		pVtx[0].pos.y = g_Bullet[nCntBullet].pos.y - 3.0f;
		pVtx[0].pos.z = g_Bullet[nCntBullet].pos.z;

		pVtx[1].pos.x = g_Bullet[nCntBullet].pos.x - 3.0f;
		pVtx[1].pos.y = g_Bullet[nCntBullet].pos.y + 3.0f;
		pVtx[1].pos.z = g_Bullet[nCntBullet].pos.z;

		pVtx[2].pos.x = g_Bullet[nCntBullet].pos.x + 3.0f;
		pVtx[2].pos.y = g_Bullet[nCntBullet].pos.y - 3.0f;
		pVtx[2].pos.z = g_Bullet[nCntBullet].pos.z;

		pVtx[3].pos.x = g_Bullet[nCntBullet].pos.x + 3.0f;
		pVtx[3].pos.y = g_Bullet[nCntBullet].pos.y + 3.0f;
		pVtx[3].pos.z = g_Bullet[nCntBullet].pos.z;

		// 各頂点の法線(ベクトル)の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);		// 1つ目の法線情報
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);		// 2つ目の法線情報
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);		// 3つ目の法線情報
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);		// 4つ目の法線情報

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

		pVtx += 4;
	}

	// アンロック
	g_pVtxBuffBullet->Unlock();

}
//=========================
//　バレット終了処理
//=========================
void UninitBullet(void)
{
	// テクスチャの破棄
	if (g_apTextureBullet != NULL)
	{
		g_apTextureBullet->Release();
		g_apTextureBullet = NULL;

	}
	// 頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

}
//=========================
//　バレット更新処理
//=========================
void UpdateBullet(void)
{

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		if (g_Bullet[nCnt].bUse)
		{
			// 座標
			g_Bullet[nCnt].posOld = g_Bullet[nCnt].pos ;

			// 位置の更新
			g_Bullet[nCnt].pos += g_Bullet[nCnt].move;

			// 影の座標更新設定
			SetPositionShadow(g_Bullet[nCnt].nIdxBullet, D3DXVECTOR3(g_Bullet[nCnt].pos.x, 0.0f, g_Bullet[nCnt].pos.z));

			// 体力を減らす
			g_Bullet[nCnt].nLife--;

			if (g_Bullet[nCnt].nLife <= 0)
			{// 体力が0以下なら
				g_Bullet[nCnt].bUse = false;		// 未使用
				SetParticle(D3DXVECTOR3(g_Bullet[nCnt].pos.x, g_Bullet[nCnt].pos.y + 10.0f, g_Bullet[nCnt].pos.z),D3DXCOLOR (1.0f,1.0f,0.0f,1.0f),15,PARTICLETYPE_BULLET);
				DeleteShadow(g_Bullet[nCnt].nIdxBullet);	// 影の消去
			}
		}
	}
}

//=========================
//　バレット描画処理
//=========================
void DrawBullet(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxRot, mtxTrans;

	// ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		if (g_Bullet[nCnt].bUse == true)
		{// 使われているとき

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Bullet[nCnt].mtxWorld);

			// ビューマトリックスを宣言
			D3DXMATRIX mtxView;

			// ビューマトリックスの取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// カメラの逆行列を設定
			g_Bullet[nCnt].mtxWorld._11 = mtxView._11;
			g_Bullet[nCnt].mtxWorld._12 = mtxView._21;
			g_Bullet[nCnt].mtxWorld._13 = mtxView._31;
			g_Bullet[nCnt].mtxWorld._21 = mtxView._12;
			g_Bullet[nCnt].mtxWorld._22 = mtxView._22;
			g_Bullet[nCnt].mtxWorld._23 = mtxView._32;
			g_Bullet[nCnt].mtxWorld._31 = mtxView._13;
			g_Bullet[nCnt].mtxWorld._32 = mtxView._23;
			g_Bullet[nCnt].mtxWorld._33 = mtxView._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Bullet[nCnt].pos.x, g_Bullet[nCnt].pos.y, g_Bullet[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Bullet[nCnt].mtxWorld, &g_Bullet[nCnt].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Bullet[nCnt].mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureBullet);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);

		}
	}

	// ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}
//=========================
//　バレット設定処理
//=========================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 dir,int nLife,D3DXVECTOR3 move)
{
	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		if (!g_Bullet[nCnt].bUse)
		{// falseだったら
			g_Bullet[nCnt].bUse = true;	// 使用判定
			g_Bullet[nCnt].pos = pos;	// 座標
			g_Bullet[nCnt].dir = dir;	// 方向ベクトル
			g_Bullet[nCnt].move = move;
			g_Bullet[nCnt].nLife = nLife;
			g_Bullet[nCnt].nIdxBullet = SetShadow(D3DXVECTOR3(g_Bullet[nCnt].pos.x, 0.0f, g_Bullet[nCnt].pos.z), g_Bullet[nCnt].rot, D3DXVECTOR3(0.5f,0.0f,0.5f));

			break;
		}
	}
}
