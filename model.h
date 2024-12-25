//=======================================
//
//モデル処理[model.h]
//Author : TANEKAWA RIKU
//
//=======================================
#ifndef _MODEL_H_//このマクロ定義がされていなかったら
#define _MODEL_H_//2重インクルード防止のマクロ定義

#include "main.h"

#define MAX_MODEL (2)	//	モデルの使う数
#define MAX_TEXTUREMODEL (128)

//壁の種類
typedef enum
{
	WALLTYPE_NORMAL=0,
	WALLTYPE_MINI,
	WALLTYPE_DOOR,
	WALLTYPE_EXIT,
	WALLTYPE_ROOM,
	WALLTYPE_ENTERDOOR,

	WALLTYPE_MAX
}WALLTYPE;

//モデル構造体
typedef struct
{
	D3DXVECTOR3 pos;					//	位置(オフセット)
	LPDIRECT3DTEXTURE9 apTexture[MAX_TEXTUREMODEL];	//	テクスチャへのポインタ
	D3DXVECTOR3 move;					//移動量
	D3DXVECTOR3 rot;					//	向き
	D3DXVECTOR3 vtxMin;
	D3DXVECTOR3 vtxMax;
	D3DXVECTOR3 size;
	int nType;
	int Index;
	bool bUse;
	LPD3DXMESH pMesh;			
	LPD3DXBUFFER pBuffMat;				//	マテリアルへのポインタ
	DWORD dwNumMat;						//	マテリアル数
	int nIdxModelParent;				//	親モデルのインデックス
	D3DXMATRIX mtxWorld;				//	ワールドマトリックス
	D3DXVECTOR3 Offpos;
	D3DXVECTOR3 Offrot;
	bool bScoreAdded;					// スコア加算済みかどうか
	bool bSoundPlayed;					// 音を再生済みかどうか
}Model;

static const char* MODEL[MAX_MODEL] =
{

	"data/MODEL/wall.x",				//	奥の壁左
	"data/MODEL/wall.x",				//	奥の壁右
	//"data/MODEL/passagewall.x",			//	奥の通路壁左
	//"data/MODEL/passagewall.x",			//	奥の通路壁左
	//"data/MODEL/wall01.x",				//	部屋の手前壁左
	//"data/MODEL/wall01.x",				//	部屋の手前壁右
	//"data/MODEL/wall01.x",				//	部屋の手前壁真ん中
	//"data/MODEL/rightwall001.x",		//	部屋の右奥壁
	//"data/MODEL/rightwall001.x",		//	部屋の右手前壁
	//"data/MODEL/wall2.x",				//	通路の手前壁
	//"data/MODEL/wall3.x",				//	通路の奥壁
	//"data/MODEL/rightwall001.x",		//	部屋の左奥壁
	//"data/MODEL/rightwall001.x",		//	部屋の左手前壁
	//"data/MODEL/wall2.x",				//	通路の手前壁
	//"data/MODEL/wall3.x",				//	通路の奥壁
	//"data/MODEL/door1.x",				//	出口ドア
	//"data/MODEL/centerwall.x",			//	真ん中の左
	//"data/MODEL/centerwall.x",			//	真ん中の右
	//"data/MODEL/centerwall2.x",			//	真ん中の奥
	//"data/MODEL/centerwall2.x",			//	真ん中の手前
	//"data/MODEL/roomwall01.x",			//	奥の部屋の手前左
	//"data/MODEL/roomwall01.x",			//	奥の部屋の手前右
	//"data/MODEL/roomwallside.x",		//	奥の部屋の左
	//"data/MODEL/roomwallside.x",		//	奥の部屋の右
	//"data/MODEL/roomwallOku.x",			//	奥の部屋の奥壁
	//"data/MODEL/exit.x",				//	出口ドア
	//"data/MODEL/roomdoor.x",			//	奥の部屋のドア
	//"data/MODEL/exit.x",				//	入口ドア

};

//プロトタイプ宣言
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
void SetModel(D3DXVECTOR3 pos, int nType);
void CollisionBlock(void);//当たり判定
bool GetTask0(void);
bool GetTask(void);
bool GetTask2(void);
bool GetTask3(void);
bool GetTask4(void);
bool GetTask5(void);
bool GetExit(void);

#endif

