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
bool bItemGet1 = false; //アイテム取得判定
bool bItemGet2 = false; //アイテム取得判定
bool bItemGet3 = false; //アイテム取得判定
bool bItemGet4 = false; //アイテム取得判定

bool bGet;
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
	bGet = false;

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

		// 半径を算出する変数
		D3DXVECTOR3 PlayerPos(15.0f, 0.0f, 15.0f);
		D3DXVECTOR3 ItemPos(15.0f, 0.0f, 15.0f);

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
			if (KeyboardTrigger(DIK_RETURN) || JoyPadTrigger(JOYKEY_A))
			{// ENTER もしくはBボタンが押された
				// ヒット処理
				HitItem(nCnt, 1);

				bGet = true;

				//エリア1
				if (bGet && g_Item[nCnt].Type == ITEMTYPE_SPRING)
				{
					g_Item[ITEMTYPE_SUMMER].bUse = false;
					g_Item[ITEMTYPE_AUTUMN].bUse = false;
					g_Item[ITEMTYPE_WINTER].bUse = false;

					g_bItem[ITEMTYPE_SPRING] = true;

					bGet = false;
				}
				else if (bGet && g_Item[nCnt].Type == ITEMTYPE_SUMMER)
				{
					g_Item[ITEMTYPE_SPRING].bUse = false;
					g_Item[ITEMTYPE_AUTUMN].bUse = false;
					g_Item[ITEMTYPE_WINTER].bUse = false;

					g_bItem[ITEMTYPE_SUMMER] = true;

					bGet = false;
				}
				else if (bGet && g_Item[nCnt].Type == ITEMTYPE_AUTUMN)
				{
					g_Item[ITEMTYPE_SPRING].bUse = false;
					g_Item[ITEMTYPE_SUMMER].bUse = false;
					g_Item[ITEMTYPE_WINTER].bUse = false;

					g_bItem[ITEMTYPE_AUTUMN] = true;

					bGet = false;
				}
				else if (bGet && g_Item[nCnt].Type == ITEMTYPE_WINTER)
				{
					g_Item[ITEMTYPE_SPRING].bUse = false;
					g_Item[ITEMTYPE_SUMMER].bUse = false;
					g_Item[ITEMTYPE_AUTUMN].bUse = false;

					g_bItem[ITEMTYPE_WINTER] = true;

					bGet = false;
				}

				//エリア2
				if (bGet && g_Item[nCnt].Type == ITEMTYPE_SHOP)
				{
					g_Item[ITEMTYPE_PARK].bUse = false;
					g_Item[ITEMTYPE_SCHOOL].bUse = false;

					g_bItem[ITEMTYPE_SHOP] = true;

					bGet = false;
				}
				else if (bGet && g_Item[nCnt].Type == ITEMTYPE_PARK)
				{
					g_Item[ITEMTYPE_SHOP].bUse = false;
					g_Item[ITEMTYPE_SCHOOL].bUse = false;

					g_bItem[ITEMTYPE_PARK] = true;

					bGet = false;
				}
				else if (bGet && g_Item[nCnt].Type == ITEMTYPE_SCHOOL)
				{
					g_Item[ITEMTYPE_SHOP].bUse = false;
					g_Item[ITEMTYPE_PARK].bUse = false;

					g_bItem[ITEMTYPE_SCHOOL] = true;

					bGet = false;
				}

				//エリア3
				if (bGet && g_Item[nCnt].Type == ITEMTYPE_FOOD1)
				{
					g_Item[ITEMTYPE_FOOD2].bUse = false;
					g_Item[ITEMTYPE_FOOD3].bUse = false;
					g_Item[ITEMTYPE_FOOD4].bUse = false;

					g_bItem[ITEMTYPE_FOOD1] = true;

					bGet = false;
				}
				else if (bGet && g_Item[nCnt].Type == ITEMTYPE_FOOD2)
				{
					g_Item[ITEMTYPE_FOOD1].bUse = false;
					g_Item[ITEMTYPE_FOOD3].bUse = false;
					g_Item[ITEMTYPE_FOOD4].bUse = false;

					g_bItem[ITEMTYPE_FOOD2] = true;

					bGet = false;
				}
				else if (bGet && g_Item[nCnt].Type == ITEMTYPE_FOOD3)
				{
					g_Item[ITEMTYPE_FOOD1].bUse = false;
					g_Item[ITEMTYPE_FOOD2].bUse = false;
					g_Item[ITEMTYPE_FOOD4].bUse = false;

					g_bItem[ITEMTYPE_FOOD3] = true;

					bGet = false;
				}
				else if (bGet && g_Item[nCnt].Type == ITEMTYPE_FOOD4)
				{
					g_Item[ITEMTYPE_FOOD1].bUse = false;
					g_Item[ITEMTYPE_FOOD2].bUse = false;
					g_Item[ITEMTYPE_FOOD3].bUse = false;

					g_bItem[ITEMTYPE_FOOD4] = true;

					bGet = false;
				}

				//エリア4
				if (bGet && g_Item[nCnt].Type == ITEMTYPE_TALK)
				{
					g_Item[ITEMTYPE_KIKAKU].bUse = false;
					g_Item[ITEMTYPE_KARISUMA].bUse = false;
					g_Item[ITEMTYPE_HYO].bUse = false;

					g_bItem[ITEMTYPE_TALK] = true;

					bGet = false;
				}
				else if (bGet && g_Item[nCnt].Type == ITEMTYPE_KIKAKU)
				{
					g_Item[ITEMTYPE_TALK].bUse = false;
					g_Item[ITEMTYPE_KARISUMA].bUse = false;
					g_Item[ITEMTYPE_HYO].bUse = false;

					g_bItem[ITEMTYPE_KIKAKU] = true;

					bGet = false;
				}
				else if (bGet && g_Item[nCnt].Type == ITEMTYPE_KARISUMA)
				{
					g_Item[ITEMTYPE_TALK].bUse = false;
					g_Item[ITEMTYPE_KIKAKU].bUse = false;
					g_Item[ITEMTYPE_HYO].bUse = false;

					g_bItem[ITEMTYPE_KARISUMA] = true;

					bGet = false;
				}
				else if (bGet && g_Item[nCnt].Type == ITEMTYPE_HYO)
				{
					g_Item[ITEMTYPE_TALK].bUse = false;
					g_Item[ITEMTYPE_KARISUMA].bUse = false;
					g_Item[ITEMTYPE_KIKAKU].bUse = false;

					g_bItem[ITEMTYPE_HYO] = true;

					bGet = false;
				}

			}
		}

		//エリア1
		if (g_Item[nCnt].Type == ITEMTYPE_SPRING && g_Item[nCnt].bUse == false)
		{
			bItemGet1 = true;
		}
		else if (g_Item[nCnt].Type == ITEMTYPE_SUMMER && g_Item[nCnt].bUse == false)
		{
			bItemGet1 = true;
		}
		else if (g_Item[nCnt].Type == ITEMTYPE_AUTUMN && g_Item[nCnt].bUse == false)
		{
			bItemGet1 = true;
		}
		else if (g_Item[nCnt].Type == ITEMTYPE_WINTER && g_Item[nCnt].bUse == false)
		{
			bItemGet1 = true;
		}

		//エリア2
		if (g_Item[nCnt].Type == ITEMTYPE_SHOP && g_Item[nCnt].bUse == false)
		{
			bItemGet2 = true;
		}
		else if (g_Item[nCnt].Type == ITEMTYPE_PARK && g_Item[nCnt].bUse == false)
		{
			bItemGet2 = true;
		}
		else if (g_Item[nCnt].Type == ITEMTYPE_SCHOOL && g_Item[nCnt].bUse == false)
		{
			bItemGet2 = true;
		}

		//エリア3
		if (g_Item[nCnt].Type == ITEMTYPE_FOOD1 && g_Item[nCnt].bUse == false)
		{
			bItemGet3 = true;
		}
		else if (g_Item[nCnt].Type == ITEMTYPE_FOOD2 && g_Item[nCnt].bUse == false)
		{
			bItemGet3 = true;
		}
		else if (g_Item[nCnt].Type == ITEMTYPE_FOOD3 && g_Item[nCnt].bUse == false)
		{
			bItemGet3 = true;
		}
		else if (g_Item[nCnt].Type == ITEMTYPE_FOOD4 && g_Item[nCnt].bUse == false)
		{
			bItemGet3 = true;
		}

		//エリア4
		if (g_Item[nCnt].Type == ITEMTYPE_TALK && g_Item[nCnt].bUse == false)
		{
			bItemGet4 = true;
		}
		else if (g_Item[nCnt].Type == ITEMTYPE_KIKAKU && g_Item[nCnt].bUse == false)
		{
			bItemGet4 = true;
		}
		else if (g_Item[nCnt].Type == ITEMTYPE_KARISUMA && g_Item[nCnt].bUse == false)
		{
			bItemGet4 = true;
		}
		else if (g_Item[nCnt].Type == ITEMTYPE_HYO && g_Item[nCnt].bUse == false)
		{
			bItemGet4 = true;
		}

		// 回転
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

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		// Lifeが0以下の時
		if (g_Item[nCntItem].nLife <= 0)
		{
			//	未使用判定
			g_Item[nCntItem].bUse = false;

			// 影を消す
			ShadowFalse(g_Item[nCntItem].nIdxshadow);

			// 取得した状態にする
			g_bItem[g_Item[nCntItem].Type] = true;
		}
	}
}
//============================
// リザルトへの番号を渡す
//============================
int GetResultNumber()
{
	// 取ったアイテムによってリザルトのテクスチャを変更させる処理
	if (g_bItem[ITEMTYPE_SPRING])
	{// 春を獲得
		if (g_bItem[ITEMTYPE_SHOP])
		{// 店
			if (g_bItem[ITEMTYPE_FOOD1])
			{// 団子を獲得
				if (g_bItem[ITEMTYPE_HYO])
				{// 表現
					// 番号を返す
					nGetNumber = 2;
				}
			}
			else if (g_bItem[ITEMTYPE_FOOD3])
			{// サツマイモ
				// 番号を返す
				nGetNumber = 5;
			}
		}
		else
		{// 条件式に入らないとき
			// 番号を返す
			nGetNumber = 5;
		}

	}
	else if (g_bItem[ITEMTYPE_SUMMER])
	{// 夏を獲得
		if (g_bItem[ITEMTYPE_PARK])
		{// 公園
			if (g_bItem[ITEMTYPE_FOOD2])
			{// スイカを獲得
				if (g_bItem[ITEMTYPE_KARISUMA])
				{
					// 番号を返す
					nGetNumber = 2;
				}
			}
			else if (g_bItem[ITEMTYPE_FOOD4])
			{// みかん
				// 番号を返す
				nGetNumber = 5;
			}

		}
		else if (g_bItem[ITEMTYPE_SHOP])
		{// 店
			if (g_bItem[ITEMTYPE_FOOD2])
			{// スイカを獲得
				if (g_bItem[ITEMTYPE_TALK])
				{
					// 番号を返す
					nGetNumber = 3;
				}
			}
		}

	}
	else if (g_bItem[ITEMTYPE_AUTUMN])
	{// 秋を獲得
		if (g_bItem[ITEMTYPE_SCHOOL])
		{// 学校
			if (g_bItem[ITEMTYPE_FOOD3])
			{// サツマイモを獲得
				if (g_bItem[ITEMTYPE_KIKAKU])
				{
					// 番号を返す
					nGetNumber = 2;
				}
			}
			else if (g_bItem[ITEMTYPE_FOOD1])
			{// 団子
				// 番号を返す
				nGetNumber = 5;
			}
		}
		else if (g_bItem[ITEMTYPE_SHOP])
		{// 店
			if (g_bItem[ITEMTYPE_FOOD3])
			{// サツマイモを獲得
				if (g_bItem[ITEMTYPE_TALK])
				{
					// 番号を返す
					nGetNumber = 0;
				}
			}
		}
	}
	else if (g_bItem[ITEMTYPE_WINTER])
	{// 冬を獲得
		if (g_bItem[ITEMTYPE_SCHOOL])
		{// 学校
			if (g_bItem[ITEMTYPE_FOOD4])
			{// みかんを獲得
				if (g_bItem[ITEMTYPE_TALK])
				{// 話術
					// 番号を返す
					nGetNumber = 2;
				}
			}
			else if (g_bItem[ITEMTYPE_FOOD2])
			{// スイカ
				// 番号を返す
				nGetNumber = 5;
			}
		}
		else if (g_bItem[ITEMTYPE_PARK])
		{// 公園
			if (g_bItem[ITEMTYPE_FOOD1] || g_bItem[ITEMTYPE_HYO])
			{// 団子 または 表現力
				// 番号を返す
				nGetNumber = 1;
			}
		}
	}

	return nGetNumber;
}
//============================
// 取得処理
//============================
Item* GetItem()
{
	return &g_Item[0];
}
bool ItemGet1(void)
{
	return bItemGet1;
}
bool ItemGet2(void)
{
	return bItemGet2;
}
bool ItemGet3(void)
{
	return bItemGet3;
}
bool ItemGet4(void)
{
	return bItemGet4;
}
