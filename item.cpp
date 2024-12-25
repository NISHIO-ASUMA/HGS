//================================
// 
// アイテム処理 [item.cpp]
// Author : TEAM_2
// 
//================================

//*******************************
// インクルードファイル宣言
//*******************************
#include "item.h"
#include "shadow.h"
#include "player.h"
#include "input.h"

//*******************************
// マクロ定義
//*******************************
#define MAX_ITEM (20)	// 最大数

//*******************************
// グローバル変数宣言
//*******************************
Item g_Item[MAX_ITEM];		// 構造体変数
int nNumItem;				// アイテム数
int nGetNumber;				// 取得番号
bool g_bItem[ITEMTYPE_MAX];	// 取得	

//==============================
// 初期化
//==============================
void InitItem()
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// グローバル変数の初期化
	nGetNumber = 0;
	nNumItem = 0;

	// 構造体変数の初期化
	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	{
		g_Item[nCnt].bUse = false;						  // 未使用判定
		g_Item[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // 座標
		g_Item[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // 角度
		g_Item[nCnt].Type = ITEMTYPE_SPRING;			  // 種類
		g_Item[nCnt].nLife = 1;							  // 体力

		for (int nModel = 0; nModel < ITEMTYPE_MAX; nModel++)
		{// モデルの読み込み
			D3DXLoadMeshFromX(ITEM_MODEL[nModel],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Item[nCnt].aModel[nModel].pBuffMat,
				NULL,
				&g_Item[nCnt].aModel[nModel].dwNumMat,
				&g_Item[nCnt].aModel[nModel].pMesh);

			// マテリアルデータへのポインタ
			D3DXMATERIAL* pMat;

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Item[nCnt].aModel[nModel].pBuffMat->GetBufferPointer();

			// マテリアル数だけ回す
			for (int nCntMat = 0; nCntMat < (int)g_Item[nCnt].aModel[nModel].dwNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					// テクスチャの読み込み
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_Item[nCnt].aModel[nModel].pTexture[nCntMat]);
				}
			}
		}
	}
}
//==============================
// 終了
//==============================
void UninitItem()
{
	// テクスチャの破棄
	// TODO : モデルのテクスチャ枚数によるため,のちに変更

	// メッシュ,マテリアルの破棄
	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	{
		for (int nModel = 0; nModel < ITEMTYPE_MAX; nModel++)
		{
			if (g_Item[nCnt].aModel[nModel].pBuffMat != NULL)
			{
				g_Item[nCnt].aModel[nModel].pBuffMat->Release();
				g_Item[nCnt].aModel[nModel].pBuffMat = NULL;
			}

			if (g_Item[nCnt].aModel[nModel].pMesh != NULL)
			{
				g_Item[nCnt].aModel[nModel].pMesh->Release();
				g_Item[nCnt].aModel[nModel].pMesh = NULL;
			}
		}
	}
}
//==============================
// 更新
//==============================
void UpdateItem()
{
	// プレイヤーの取得
	Player* pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	{
		if (!g_Item[nCnt].bUse)
		{// 未使用状態の時
			continue;
		}

		// 種類を保存
		int nType = g_Item[nCnt].Type;

		// 影の座標更新設定
		SetPositionShadow(g_Item[nCnt].nIdxshadow, D3DXVECTOR3(g_Item[nCnt].pos.x, 0.0f, g_Item[nCnt].pos.z));

		// 半径を算出する変数
		D3DXVECTOR3 PlayerPos(6.0f, 0.0f, 6.0f);
		D3DXVECTOR3 ItemPos(6.0f, 0.0f, 6.0f);

		// プレイヤーとの距離の差を求める
		D3DXVECTOR3 diff = pPlayer->pos - g_Item[nCnt].pos;

		// 角度の算出
		float fAngle = atan2f(diff.x, diff.z);

		// 範囲計算===============================================
		// 距離を求める
		float fDisX = (pPlayer->pos.x - g_Item[nCnt].pos.x);
		float fDisY = (pPlayer->pos.y - g_Item[nCnt].pos.y);
		float fDisZ = (pPlayer->pos.z - g_Item[nCnt].pos.z);

		// 2つの半径
		float fRadX = (PlayerPos.x + ItemPos.x);
		float fRadY = (PlayerPos.y + ItemPos.y);
		float fRadZ = (PlayerPos.z + ItemPos.z);
		//========================================================

		// 範囲内にはいったとき
		if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX + fRadY + fRadZ) * (fRadX + fRadY + fRadZ))
		{
			if (KeyboardTrigger(DIK_RETURN) || JoyPadTrigger(JOYKEY_B))
			{// ENTER もしくはBボタンが押された
				// ヒット処理
				HitItem(nCnt, 1);
			}
		}

		g_Item[nCnt].rot.y += 0.02f;
	}	
}
//==============================
// 描画
//==============================
void DrawItem()
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxRot, mtxTrans;

	// 現在のマテリアルを保存
	D3DMATERIAL9 matDef;

	// マテリアルデータへのポインタ
	D3DXMATERIAL* pMat;

	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	{

		if (!g_Item[nCnt].bUse)
		{// 未使用状態なら
			continue;
		}

		// タイプを保存
		int nType = g_Item[nCnt].Type;

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Item[nCnt].mtxWorld);

		// 向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Item[nCnt].rot.y, g_Item[nCnt].rot.x, g_Item[nCnt].rot.z);
		D3DXMatrixMultiply(&g_Item[nCnt].mtxWorld, &g_Item[nCnt].mtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Item[nCnt].pos.x, g_Item[nCnt].pos.y, g_Item[nCnt].pos.z);
		D3DXMatrixMultiply(&g_Item[nCnt].mtxWorld, &g_Item[nCnt].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Item[nCnt].mtxWorld);

		// 現在のマトリックスの取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Item[nCnt].aModel[nType].pBuffMat->GetBufferPointer();

		// マテリアル数だけ回す
		for (int nCntMat = 0; nCntMat < (int)g_Item[nCnt].aModel[nType].dwNumMat; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// テクスチャ設定
			pDevice->SetTexture(0, g_Item[nCnt].aModel[nType].pTexture[nCntMat]);

			// ブロック(パーツ)の描画
			g_Item[nCnt].aModel[nType].pMesh->DrawSubset(nCntMat);
		}
		// マテリアルを戻す
		pDevice->SetMaterial(&matDef);


	}
}
//==============================
// 設定処理
//==============================
void SetItem(D3DXVECTOR3 pos, ITEMTYPE Type)
{
	for (int nCnt1 = 0; nCnt1 < MAX_ITEM; nCnt1++)
	{
		if (!g_Item[nCnt1].bUse)
		{
			// 未使用なら
			g_Item[nCnt1].pos = pos;		// 座標
			g_Item[nCnt1].Type = Type;		// 種類
			g_Item[nCnt1].bUse = true;		// 使用判定

			// 影の設定
			g_Item[nCnt1].nIdxshadow = SetShadow(D3DXVECTOR3(g_Item[nCnt1].pos.x, 0.0f, g_Item[nCnt1].pos.z), g_Item[nCnt1].rot);

			// アイテム数をカウント
			nNumItem++;

			break;
		}
	}
}
//============================
// ヒット処理
//============================
void HitItem(int nCnt, int nDamage)
{
	// ダメージを受けたら体力減少
	g_Item[nCnt].nLife -= nDamage;

	// Lifeが0以下の時
	if (g_Item[nCnt].nLife <= 0)
	{
		//	未使用判定
		g_Item[nCnt].bUse = false;

		// 影を消す
		ShadowFalse(g_Item[nCnt].nIdxshadow);

		// 取得した状態にする
		g_bItem[g_Item[nCnt].Type] = true;
	}
}
//============================
// リザルトへの番号を渡す
//============================
int GetResultNumber()
{
	// TODO : 取ったアイテムによってリザルトのテクスチャを変更させる処理
	return nGetNumber;
}
//============================
// 取得処理
//============================
Item* GetItem()
{
	return &g_Item[0];
}
