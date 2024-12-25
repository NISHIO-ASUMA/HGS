//=======================================
//
//モデル処理[model.h]
//Author : TANEKAWA RIKU
//
//=======================================
#ifndef _MODEL_H_//このマクロ定義がされていなかったら
#define _MODEL_H_//2重インクルード防止のマクロ定義

#include "main.h"

#define MAX_MODEL (25)	//	モデルの使う数
#define MAX_TEXTUREMODEL (128)

//壁の種類
typedef enum
{
	WALLTYPE_OKU=0,
	WALLTYPE_HIDARI,
	WALLTYPE_TEMAE,
	WALLTYPE_MIGI,
	WALLTYPE_DOOR1,
	WALLTYPE_DOOR2,
	WALLTYPE_DOOR3,
	WALLTYPE_DOOR4,

	WALLTYPE_GOALOKU,
	WALLTYPE_GOALTEMAE,
	WALLTYPE_GOALMIGI,

	WALLTYPE_CLEAR,
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

	"data/MODEL/wall_oku.x",		//	ルーム1の奥の壁
	"data/MODEL/wall_hidari.x",		//	ルーム1の左壁
	"data/MODEL/wall_temae.x",		//	ルーム1の手前壁
	"data/MODEL/wall_migi.x",		//	ルーム1の右壁奥
	"data/MODEL/wall_migi.x",		//	ルーム1の右壁手前

	"data/MODEL/wall_oku.x",		//	ルーム2の奥の壁
	"data/MODEL/wall_temae.x",		//	ルーム2の手前壁
	"data/MODEL/wall_migi.x",		//	ルーム2の右壁奥
	"data/MODEL/wall_migi.x",		//	ルーム2の右壁手前

	"data/MODEL/wall_oku.x",		//	ルーム3の奥の壁
	"data/MODEL/wall_temae.x",		//	ルーム3の手前壁
	"data/MODEL/wall_migi.x",		//	ルーム3の右壁奥
	"data/MODEL/wall_migi.x",		//	ルーム3の右壁手前

	"data/MODEL/wall_oku.x",		//	ルーム4の奥の壁
	"data/MODEL/wall_temae.x",		//	ルーム4の手前壁
	"data/MODEL/wall_migi.x",		//	ルーム4の右壁奥
	"data/MODEL/wall_migi.x",		//	ルーム4の右壁手前

	"data/MODEL/roomdoor.x",		//	ルーム1のドア
	"data/MODEL/roomdoor.x",		//	ルーム2のドア
	"data/MODEL/roomdoor.x",		//	ルーム3のドア
	"data/MODEL/roomdoor.x",		//	ルーム4のドア

	"data/MODEL/wall_goal_oku.x",	//	ゴールの奥壁
	"data/MODEL/wall_goal_temae.x",	//	ゴールの手前壁
	"data/MODEL/wall_goal_migi.x",	//	ゴールの右壁

	"data/MODEL/present_box.x",		//	ゴールのプレゼント

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

