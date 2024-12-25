//======================================
//
// メッシュの壁の処理 [mashwall.cpp]
// Author: TEAM_2
//
//======================================

//****************************
// インクルードファイル宣言
//****************************
#include "meshwall.h"
#include "player.h"
#include "enemy.h"

//*****************************
// グローバル変数宣言
//*****************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;	// 頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_apTextureMeshWall = NULL;		// テクスチャのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;	// インデックスバッファへのポインタ
MeshWall g_MeshWall;

//==============================
// メッシュフィールド初期化処理
//==============================
void InitMeshWall(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\sky.jpg",
		&g_apTextureMeshWall);

	// 初期化
	g_MeshWall.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshWall.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ローカル変数宣言------------------------
	int nRadius = 680;		// 半径
	int nIndex = 0;

	float TexX = 1.0f / XVTX;
	float TexZ = 1.0f / ZVTX;
	float fAngle;
	D3DXVECTOR3 nor;
	//------------------------------------------

	// 頂点バッファ(三角形は意識しない)
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * ALLVTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * INDEXBUFF,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall,
		NULL);

	// 頂点情報のポインタ
	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntV = 0; nCntV < ZVTX + 1; nCntV++)
	{// 高さの分割数

		for (int nCntH = 0; nCntH < XVTX + 1; nCntH++)
		{// 水平方向の分割数
			// 角度の設定
			fAngle = (D3DX_PI * 2.0f) / XVTX * nCntH;

			// 頂点座標の設定
			pVtx[nIndex].pos = D3DXVECTOR3(sinf((fAngle)) * nRadius, nCntV * 100.0f, cosf((fAngle)) * nRadius);

			// 法線ベクトルの設定
			nor = pVtx[nIndex].pos - g_MeshWall.pos;	// 各頂点から原点の値を引く
			D3DXVec3Normalize(&pVtx[nIndex].nor, &nor);	// 法線の正規化

			// カラー
			pVtx[nIndex].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ
			pVtx[nIndex].tex = D3DXVECTOR2(TexX * nCntH, TexZ * nCntV);

			nIndex++;
		}
	}

	// アンロック
	g_pVtxBuffMeshWall->Unlock();

	// インデックスバッファのポインタ
	WORD* pIdx;

	int nIdxNumber = 0;				// ローカル変数
	int nCntIdx3 = XVTX + 1;	// Xの値
	int nNum = 0;

	//インデックスバッファをロック
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	//インデックスを設定
	for (int nCntIdx = 0; nCntIdx < ZVTX; nCntIdx++)
	{// MAX_ZVTXの数だけ回す
		for (int nCntIdx2 = 0; nCntIdx2 <= XVTX; nCntIdx2++, nCntIdx3++, nNum++)
		{// MAX_XVTXの数だけ回す
			pIdx[nIdxNumber] = nCntIdx3;	// 数字を代入
			pIdx[nIdxNumber + 1] = nNum;	// 数字を代入
			nIdxNumber += 2;
		}

		// NOTE: 最後の行に縮退ポリゴンがない
		if (nCntIdx != ZVTX - 1)
		{
			pIdx[nIdxNumber] = nNum - 1;	// for文に入るため
			pIdx[nIdxNumber + 1] = nCntIdx3;	// 数字を代入
			nIdxNumber += 2;

		}
	}

	// アンロック
	g_pIdxBuffMeshWall->Unlock();

}
//==============================
// メッシュフィールド終了処理
//==============================
void UninitMeshWall(void)
{
	// テクスチャの破棄
	if (g_apTextureMeshWall != NULL)
	{
		g_apTextureMeshWall->Release();
		g_apTextureMeshWall = NULL;
	}
	// 頂点バッファの破棄
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}

	// インデックスバッファの破棄
	if (g_pIdxBuffMeshWall != NULL)
	{
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}
}
//==============================
// メッシュフィールド更新処理
//==============================
void UpdateMeshWall(void)
{
	// 無し
}
//==============================
// メッシュフィールド描画処理
//==============================
void DrawMeshWall(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxRot, mtxTrans;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_MeshWall.mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshWall.rot.y, g_MeshWall.rot.x, g_MeshWall.rot.z);
	D3DXMatrixMultiply(&g_MeshWall.mtxWorld, &g_MeshWall.mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_MeshWall.pos.x, g_MeshWall.pos.y, g_MeshWall.pos.z);
	D3DXMatrixMultiply(&g_MeshWall.mtxWorld, &g_MeshWall.mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshWall.mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshWall);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_apTextureMeshWall);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		ALLVTX,
		0,
		NUMPOLYGON);
}
//=========================
// 当たり判定
//=========================
void CollisionMeshWall()
{
	// ロ－カル
	int nRadius = 680;		// 半径
	int nCntVtx, nCntVtx2 = 0;
	D3DXVECTOR3 VecA[XVTX], VecB[XVTX], Cross[XVTX];

	// プレイヤーの取得
	Player* pPlayer = GetPlayer();

	// XVTX分
	for (int nCnt = 0; nCnt < XVTX; nCnt++)
	{
		// 角度の設定
		float fAngle = (D3DX_PI * 2.0f) / XVTX * nCnt;

		// 頂点座標の設定
		g_MeshWall.Vtxpos[nCnt] = D3DXVECTOR3(sinf((fAngle)) * nRadius, nCnt * 50.0f, cosf((fAngle)) * nRadius);

		// 頂点
		nCntVtx = nCnt % XVTX;
		nCntVtx2 = (nCnt + 1) % XVTX;

		// 2つのベクトル
		VecA[nCnt] = g_MeshWall.Vtxpos[nCntVtx2] - g_MeshWall.Vtxpos[nCntVtx];
		VecB[nCnt] = pPlayer->pos - g_MeshWall.Vtxpos[nCnt];

		// 外積関数
		D3DXVec3Cross(&Cross[nCnt], &VecA[nCnt], &VecB[nCnt]);

		// 正規化
		D3DXVec3Normalize(&Cross[nCnt], &Cross[nCnt]);

		if (Cross[nCnt].y < 0.0f)
		{
			pPlayer->pos.x = pPlayer->posOld.x;
			pPlayer->pos.z = pPlayer->posOld.z;
		}
	}
}
//==================================
// 敵との当たり判定
//==================================
void CollisionEnemyToWall(int nCnt)
{
	// 敵の取得
	Enemy* pEnemy = GetEnemy();

	// ローカル変数-----------------------------
	D3DXVECTOR3 Vec1[XVTX], Vec2[XVTX], CrossEnemy[XVTX];
	int nRadius = 680;		// 半径
	int nCntVtx1, nCntVtx2 = 0;

	// XVTX分
	for (int nCntVec = 0; nCntVec < XVTX; nCntVec++)
	{
		if (pEnemy[nCnt].bUse)
		{
			// 角度の設定
			float fAngle = (D3DX_PI * 2.0f) / XVTX * nCntVec;

			// 頂点座標の設定
			g_MeshWall.Vtxpos[nCntVec] = D3DXVECTOR3(sinf((fAngle)) * nRadius, nCntVec * 100.0f, cosf((fAngle)) * nRadius);

			// 頂点
			nCntVtx1 = nCntVec % XVTX;
			nCntVtx2 = (nCntVec + 1) % XVTX;

			// 2つのベクトル
			Vec1[nCntVec] = g_MeshWall.Vtxpos[nCntVtx2] - g_MeshWall.Vtxpos[nCntVtx1];
			Vec2[nCntVec] = pEnemy[nCnt].pos - g_MeshWall.Vtxpos[nCntVec];

			// 外積関数
			D3DXVec3Cross(&CrossEnemy[nCntVec], &Vec1[nCntVec], &Vec2[nCntVec]);

			// 正規化
			D3DXVec3Normalize(&CrossEnemy[nCntVec], &CrossEnemy[nCntVec]);

			if (CrossEnemy[nCntVec].y < 0.0f)
			{// pos戻す
				pEnemy[nCnt].pos.x = pEnemy[nCnt].posOld.x;
				pEnemy[nCnt].pos.z = pEnemy[nCnt].posOld.z;
			}
		}
	}
}
