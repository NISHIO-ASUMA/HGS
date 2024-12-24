//==============================
//
// ランキング処理 [ranksetdata.h]
// Author:TEAM_2
//
//==============================
#ifndef _RANKSETDATA_H_
#define _RANKSETDATA_H_

//*******************************
// インクルードファイル宣言
//*******************************
#include "main.h"

//*******************************
// プロトタイプ宣言
//*******************************
void InitRankingData(void);			// 順位の初期化
void UninitRankingData(void);		// 順位の終了
void UpdateRankingData(void);		// 順位の更新
void DrawRankingData(void);			// 順位の描画

#endif
