//=================================
//
// 敵の処理 [enemy.cpp]
// Author: TEAM_2
//	
//=================================

//********************************
// インクルードファイル宣言
//********************************
#include "enemy.h"
#include "player.h"
#include "particle.h"
#include <stdio.h>
#include "effect.h"
#include "score.h"
#include "block.h"
#include "shadow.h"
#include "sound.h"
#include "meshwall.h"
#include "fade.h"

//********************************
// グローバル変数宣言
//********************************
Enemy g_Enemy[MAX_ENEMY];								// 敵の構造体情報

int g_nNumEnemy;										// 敵数を取得する用の変数
int g_FireCount;										// ファイルカウント
bool g_bFinish;											// テキスト終了判定
int g_nCntJumpCount;									// ジャンプカウント

//================================
// 敵の初期化処理
//================================
void InitEnemy()
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	

	// グローバル変数の初期化-----------------------------
	g_nNumEnemy = 0;
	g_FireCount = 0;
	g_bFinish = false;
	g_nCntJumpCount = 0;
	//-----------------------------------------------------

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		g_Enemy[nCnt].bUse = false;							 // 未使用判定
		g_Enemy[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	 // 座標
		g_Enemy[nCnt].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// 過去の座標
		g_Enemy[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	 // 移動量
		g_Enemy[nCnt].nLife = 0;							 // 体力
		g_Enemy[nCnt].State = ENEMYSTATE_NORMAL;			 // 状態
		g_Enemy[nCnt].nCntState = 0;						 // 状態管理カウンター
		g_Enemy[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	 // 角度
		g_Enemy[nCnt].nType = ENEMYTYPE_FIRE;				 // 種類

		for (int nCntEn = 0; nCntEn < ENEMYTYPE_MAX; nCntEn++)
		{
			// Xファイルの読み込み
			D3DXLoadMeshFromX(ENEMY_MODEL[nCntEn],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Enemy[nCnt].aModel[nCntEn].pBuffMatEnemy,
				NULL,
				&g_Enemy[nCnt].aModel[nCntEn].dwNumMatEnemy,
				&g_Enemy[nCnt].aModel[nCntEn].pMeshEnemy);

			// ローカル変数宣言-----------------------------
			int nNumVtx;		// 頂点数
			DWORD sizeFVF;		// 頂点フォーマットのサイズ
			BYTE* pVtxBuff;		// 頂点バッファのポインタ
			//----------------------------------------------

			// 頂点数の取得
			nNumVtx = g_Enemy[nCnt].aModel[nCntEn].pMeshEnemy->GetNumVertices();

			// 頂点のサイズを取得
			sizeFVF = D3DXGetFVFVertexSize(g_Enemy[nCnt].aModel[nCntEn].pMeshEnemy->GetFVF());

			// 頂点バッファをロック
			g_Enemy[nCnt].aModel[nCntEn].pMeshEnemy->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			// 頂点数分回す
			for (int nCntEnemy = 0; nCntEnemy < nNumVtx; nCntEnemy++)
			{
				// 頂点座標の代入
				D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;

				// 頂点座標の比較
				if (Vtx.x > g_Enemy[nCnt].Vtxmax.x)
				{// xが最大値より大きかったら
					// 代入
					g_Enemy[nCnt].Vtxmax.x = Vtx.x;
				}
				if (Vtx.y > g_Enemy[nCnt].Vtxmax.y)
				{// yが最大値より大きかったら
					// 代入
					g_Enemy[nCnt].Vtxmax.y = Vtx.y;
				}
				if (Vtx.z > g_Enemy[nCnt].Vtxmax.z)
				{// zが最大値より大きかったら
					// 代入
					g_Enemy[nCnt].Vtxmax.z = Vtx.z;
				}

				if (Vtx.x < g_Enemy[nCnt].Vtxmin.x)
				{// xが最小値より小さかったら
					// 代入
					g_Enemy[nCnt].Vtxmin.x = Vtx.x;
				}
				if (Vtx.y < g_Enemy[nCnt].Vtxmin.y)
				{// yが最小値より小さかったら
					// 代入
					g_Enemy[nCnt].Vtxmin.y = Vtx.y;
				}
				if (Vtx.z < g_Enemy[nCnt].Vtxmin.z)
				{// zが最小値より小さかったら
					// 代入
					g_Enemy[nCnt].Vtxmin.z = Vtx.z;
				}

				// 頂点フォーマットのサイズ分進める
				pVtxBuff += sizeFVF;
			}

			// サイズを代入する
			g_Enemy[nCnt].size.x = g_Enemy[nCnt].Vtxmax.x - g_Enemy[nCnt].Vtxmin.x;	// sizeのx
			g_Enemy[nCnt].size.y = g_Enemy[nCnt].Vtxmax.y - g_Enemy[nCnt].Vtxmin.y;	// sizeのy
			g_Enemy[nCnt].size.z = g_Enemy[nCnt].Vtxmax.z - g_Enemy[nCnt].Vtxmin.z;	// sizeのz

			// アンロック
			g_Enemy[nCnt].aModel[nCntEn].pMeshEnemy->UnlockVertexBuffer();

			// マテリアルデータへのポインタ
			D3DXMATERIAL* pMat;

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Enemy[nCnt].aModel[nCntEn].pBuffMatEnemy->GetBufferPointer();

			// マテリアル数だけ回す
			for (int nCntMat = 0; nCntMat < (int)g_Enemy[nCnt].aModel[nCntEn].dwNumMatEnemy; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					// テクスチャの読み込み
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_Enemy[nCnt].aModel[nCntEn].pTexture[nCntMat]);
				}
			}
		}
	}
}
//===================================
// 敵の終了処理
//===================================
void UninitEnemy(void)
{
	// 音楽を停止
	StopSound();

	// テクスチャの破棄
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		for (int nCntEn = 0; nCntEn < ENEMYTYPE_MAX; nCntEn++)
		{
			for (int nCntMat = 0; nCntMat < (int)g_Enemy[nCnt].aModel[nCntEn].dwNumMatEnemy; nCntMat++)
			{
				if (g_Enemy[nCnt].aModel[nCntEn].pTexture[nCntMat] != NULL)
				{
					g_Enemy[nCnt].aModel[nCntEn].pTexture[nCntMat]->Release();
					g_Enemy[nCnt].aModel[nCntEn].pTexture[nCntMat] = NULL;
				}
			}
		}
	}

	// メッシュの破棄,マテリアルの破棄
	for (int nCntEn = 0; nCntEn < MAX_ENEMY; nCntEn++)
	{// モデル最大数
		for (int nCnt = 0; nCnt < ENEMYTYPE_MAX; nCnt++)
		{
			if (g_Enemy[nCntEn].aModel[nCnt].pMeshEnemy != NULL)
			{
				g_Enemy[nCntEn].aModel[nCnt].pMeshEnemy->Release();
				g_Enemy[nCntEn].aModel[nCnt].pMeshEnemy = NULL;
			}

			if (g_Enemy[nCntEn].aModel[nCnt].pBuffMatEnemy != NULL)
			{
				g_Enemy[nCntEn].aModel[nCnt].pBuffMatEnemy->Release();
				g_Enemy[nCntEn].aModel[nCnt].pBuffMatEnemy = NULL;
			}
		}

	}
}
//====================================
// 敵の更新処理
//====================================
void UpdateEnemy(void)
{
	// 現在のモードの取得
	MODE nMode = GetMode();

	// プレイヤーの取得
	PLAYER* pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{// 敵の数

		if (!g_Enemy[nCnt].bUse)
		{// 未使用なら
			continue;
		}

		if (nMode == MODE_GAME)
		{// モードがゲームなら
			// 影の座標更新設定
			SetPositionShadow(g_Enemy[nCnt].nIdxEnemy, D3DXVECTOR3(g_Enemy[nCnt].pos.x, 0.0f, g_Enemy[nCnt].pos.z));

			// 種類を保存
			int nType = g_Enemy[nCnt].nType;

			// 半径を算出する変数
			D3DXVECTOR3 PRadiusPos(50.0f, 0.0f, 50.0f);
			D3DXVECTOR3 ERadiusPos(50.0f, 0.0f, 50.0f);

			// 半径を算出する変数2
			D3DXVECTOR3 Pradius(6.0f, 0.0f, 6.0f);
			D3DXVECTOR3 Eradius(6.0f, 0.0f, 6.0f);

			// 半径を算出する変数3
			D3DXVECTOR3 radiusPlayer(10.0f, 0.0f, 10.0f);
			D3DXVECTOR3 radiusEnemy(10.0f, 0.0f, 10.0f);

			// 速度計算用の変数
			float fspeed = 0.0f;

			// プレイヤーの位置を取得
			D3DXVECTOR3 playerPos = GetPlayer()->pos;

			// プレイヤーとの距離の差を求める
			D3DXVECTOR3 diff = playerPos - g_Enemy[nCnt].pos;

			// 角度の算出
			float fAngle = atan2f(diff.x, diff.z);

			// 範囲計算===============================================
			// 距離を求める
			float fDisX = (playerPos.x - g_Enemy[nCnt].pos.x);
			float fDisY = (playerPos.y - g_Enemy[nCnt].pos.y);
			float fDisZ = (playerPos.z - g_Enemy[nCnt].pos.z);

			// 2つの半径
			float fRadX = (PRadiusPos.x + ERadiusPos.x);
			float fRadY = (PRadiusPos.y + ERadiusPos.y);
			float fRadZ = (PRadiusPos.z + ERadiusPos.z);
			//========================================================

			// 当たり判定用===========================================
			// 距離を求める
			float fdisX = (pPlayer->pos.x - g_Enemy[nCnt].pos.x);
			float fdisY = (pPlayer->pos.y - g_Enemy[nCnt].pos.y);
			float fdisZ = (pPlayer->pos.z - g_Enemy[nCnt].pos.z);

			// 2つの半径
			float fradX = (Pradius.x + Eradius.x);
			float fradY = (Pradius.y + Eradius.y);
			float fradZ = (Pradius.z + Eradius.z);
			//=========================================================

			// 右手の当たり判定用==================================
			// 距離を求める
			float fRightX = (pPlayer->aModel[4].mtxWorld._41 - g_Enemy[nCnt].pos.x);
			float fRightY = (pPlayer->aModel[4].mtxWorld._42 - g_Enemy[nCnt].pos.y);
			float fRightZ = (pPlayer->aModel[4].mtxWorld._43 - g_Enemy[nCnt].pos.z);

			// 2つの半径
			float fX = (radiusPlayer.x + radiusEnemy.x);
			//================================================

#ifdef _DEBUG
			// 当たり判定確認用
			SetEffect(D3DXVECTOR3(pPlayer->aModel[4].mtxWorld._41, pPlayer->aModel[4].mtxWorld._42, pPlayer->aModel[4].mtxWorld._43), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), 10);
#endif
			switch (g_Enemy[nCnt].State)
			{
			case ENEMYSTATE_NORMAL:

				// 敵の角度
				g_Enemy[nCnt].rot.y = fAngle + D3DX_PI;

				// 各タイプごとの追尾スピード--------------------------------------
				if (g_Enemy[nCnt].nType == ENEMYTYPE_FIRE)
				{// 一種類目の敵なら
					fspeed = (float)(rand() % 3) + 0.01f;
				}
				else if (g_Enemy[nCnt].nType == ENEMYTYPE_NOFIRE)
				{// 二種類目の敵なら
					fspeed = (float)(rand() % 3) + 0.01f;
				}
				else if (g_Enemy[nCnt].nType == ENEMYTYPE_PURA)
				{// 三種類目の敵なら
					fspeed = (float)(rand() % 3) + 0.03f;
				}
				else if (g_Enemy[nCnt].nType == ENEMYTYPE_KAN)
				{// 四種類目の敵なら
					fspeed = (float)(rand() % 3) + 0.04f;
				}
				else if (g_Enemy[nCnt].nType == ENEMYTYPE_RECYCLE)
				{// 五種類目の敵なら
					fspeed = (float)(rand() % 3) + 0.06f;
				}
				//-------------------------------------------------------------------

				// 追尾システム
				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX + fRadY + fRadZ) * (fRadX + fRadY + fRadZ))
				{// 範囲内にはいったとき

					// 移動量の更新
					g_Enemy[nCnt].move.x = sinf(g_Enemy[nCnt].rot.y + D3DX_PI) * fspeed;
					g_Enemy[nCnt].move.z = cosf(g_Enemy[nCnt].rot.y + D3DX_PI) * fspeed;
				}

				// プレイヤーをはじきとばす
				if ((fdisX * fdisX) + (fdisY * fdisY) + (fdisZ * fdisZ) <= (fradX + fradY + fradZ) * (fradX + fradY + fradZ))
				{// 範囲内にはいったとき
					// 吹っ飛ばす
					pPlayer->move.x = sinf(g_Enemy[nCnt].rot.y + D3DX_PI) * 25.0f;
					pPlayer->move.y = 5.0f;
					pPlayer->move.z = cosf(g_Enemy[nCnt].rot.y + D3DX_PI) * 25.0f;

					if (pPlayer->Pcon == PLAYERCONDITION_NORMAL)
					{// プレイヤーの体力を減らす
						
						//DamageFade(MODE_DAMAGEFADE);
						HitPlayer(1);

						// 音楽再生
						PlaySound(SOUND_LABLE_PLAYERDAMAGE);
					}
				}

				//  敵をはじきとばす処理を入れたい
				if ((fRightX * fRightX) + (fRightY * fRightY) + (fRightZ * fRightZ) <= (fX + fX) * (fX + fX))
				{
					if (g_Enemy[nCnt].State == ENEMYSTATE_NORMAL && pPlayer->state == PLAYERSTATE_ACTION)
					{// 攻撃モーション
						// 右手に当たっていたら
						HitEnemy(nCnt, 2);

						// 音楽再生
						PlaySound(SOUND_LABLE_DAMAGESE);

						if (g_Enemy[nCnt].State == ENEMYSTATE_DAMAGE)
						{
							// 敵を吹っ飛ばす
							g_Enemy[nCnt].move.x = sinf(pPlayer->rot.y + D3DX_PI) * 70.0f;
							g_Enemy[nCnt].move.y = 8.0f;
							g_Enemy[nCnt].move.z = cosf(pPlayer->rot.y + D3DX_PI) * 70.0f;

							// 位置更新
							g_Enemy[nCnt].pos.x += g_Enemy[nCnt].move.x;
							g_Enemy[nCnt].pos.z += g_Enemy[nCnt].move.z;

						}
					}
				}

				break;

			case ENEMYSTATE_DAMAGE:
				// 状態管理カウンターをデクリメントする
				g_Enemy[nCnt].nCntState--;

				if (g_Enemy[nCnt].nCntState <= 0)
				{// カウンターが0以下になったら
					// 通常状態に戻す
					g_Enemy[nCnt].State = ENEMYSTATE_NORMAL;
				}

				break;

			default:
				break;
			}

			// 前回の位置を保存
			g_Enemy[nCnt].posOld = g_Enemy[nCnt].pos;

			// 位置更新
			if (g_Enemy[nCnt].State == ENEMYSTATE_NORMAL)
			{
				g_Enemy[nCnt].pos.x += g_Enemy[nCnt].move.x;
				g_Enemy[nCnt].pos.z += g_Enemy[nCnt].move.z;

			}
			g_Enemy[nCnt].pos.y += g_Enemy[nCnt].move.y;
		}

		// メッシュとの当たり判定
		CollisionEnemyToWall(nCnt);
	}

	// 当たり判定
	CollisionBlock();
}
//====================================
// 敵の描画処理
//====================================
void DrawEnemy(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxRot, mtxTrans;

	// 現在のマテリアルを保存
	D3DMATERIAL9 matDef;

	// マテリアルデータへのポインタ
	D3DXMATERIAL* pMat;

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		// タイプを保存
		int nType = g_Enemy[nCnt].nType;

		if (!g_Enemy[nCnt].bUse)
		{// 未使用状態なら
			continue;
		}

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Enemy[nCnt].mtxWorld);

		// 向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nCnt].rot.y, g_Enemy[nCnt].rot.x, g_Enemy[nCnt].rot.z);
		D3DXMatrixMultiply(&g_Enemy[nCnt].mtxWorld, &g_Enemy[nCnt].mtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Enemy[nCnt].pos.x, g_Enemy[nCnt].pos.y, g_Enemy[nCnt].pos.z);
		D3DXMatrixMultiply(&g_Enemy[nCnt].mtxWorld, &g_Enemy[nCnt].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCnt].mtxWorld);

		// 現在のマトリックスの取得
		pDevice->GetMaterial(&matDef);

		// マテリアル数だけ回す
		for (int nCntMat = 0; nCntMat < (int)g_Enemy[nCnt].aModel[nType].dwNumMatEnemy; nCntMat++)
		{
			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Enemy[nCnt].aModel[nType].pBuffMatEnemy->GetBufferPointer();

			// マテリアル
			D3DXMATERIAL mat;

			switch (g_Enemy[nCnt].State)
			{
			case ENEMYSTATE_NORMAL:
				// マテリアル設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				break;

			case ENEMYSTATE_DAMAGE:

				mat = pMat[nCntMat];

				mat.MatD3D.Diffuse.r = 1.0f;
				mat.MatD3D.Diffuse.g = 0.0f;
				mat.MatD3D.Diffuse.b = 0.0f;
				mat.MatD3D.Diffuse.a = 1.0f;

				// マテリアル設定
				pDevice->SetMaterial(&mat.MatD3D);

				break;
			}

			// テクスチャ設定
			pDevice->SetTexture(0, g_Enemy[nCnt].aModel[nType].pTexture[nCntMat]);

			// ブロック(パーツ)の描画
			g_Enemy[nCnt].aModel[nType].pMeshEnemy->DrawSubset(nCntMat);
		}

		// マテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}

#ifdef _DEBUG
	// 敵の総数表示
	DrawEnemySet(g_nNumEnemy);
#endif

}
//====================================
// 敵の設定処理
//====================================
void SetEnemy(ENEMYTYPE nType, D3DXVECTOR3 pos)
{
	for (int nCnt1 = 0; nCnt1 < MAX_ENEMY; nCnt1++)
	{
		if (!g_Enemy[nCnt1].bUse)
		{
			// 未使用なら
			g_Enemy[nCnt1].pos = pos;								// 座標
			g_Enemy[nCnt1].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 移動量
			g_Enemy[nCnt1].nType = nType;							// 種類
			g_Enemy[nCnt1].bUse = true;								// 使用判定
			g_Enemy[nCnt1].nIdxEnemy = SetShadow(D3DXVECTOR3(g_Enemy[nCnt1].pos.x, 0.0f, g_Enemy[nCnt1].pos.z), g_Enemy[nCnt1].rot, D3DXVECTOR3(0.5f, 0.0f, 0.5f));

			// 敵数をカウント
			g_nNumEnemy++;					

			break;
		}
	}
}
//====================================
// 敵の総数の値を返す
//====================================
int GetNumEnemy()
{
	return g_nNumEnemy;
}
//====================================
// 敵のヒット処理
//====================================
void HitEnemy(int nCntEnemy,int nDamage)
{	
	// 現在のモードの取得
	MODE nMode = GetMode();

	// ダメージ受けたら体力減らす
	g_Enemy[nCntEnemy].nLife -= nDamage;		

	if (g_Enemy[nCntEnemy].nLife <= 0)
	{// 体力が0以下なら
		// 未使用状態
		g_Enemy[nCntEnemy].bUse = false;

		// 影の消去
		DeleteShadow(g_Enemy[nCntEnemy].nIdxEnemy);

		// パーティクル
		SetParticle(g_Enemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.7f), 20, PARTICLETYPE_ENEMY);

		// 敵の総数をデクリメント
		g_nNumEnemy--;
	}
	else
	{
		// パーティクル
		SetParticle(g_Enemy[nCntEnemy].pos, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 15, PARTICLETYPE_ENEMY);

		g_Enemy[nCntEnemy].State = ENEMYSTATE_DAMAGE;	// ダメージ状態に変更
		g_Enemy[nCntEnemy].nCntState = 10;				// ダメージ状態の時間
	}
}
//==========================
// 敵の取得
//==========================
Enemy* GetEnemy()
{
	return &g_Enemy[0];
}
// TODO : テキストやりたかったらどうぞ