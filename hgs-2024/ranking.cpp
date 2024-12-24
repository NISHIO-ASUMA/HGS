//==============================
//
//ランキング処理
//Author:TEAM_2
//
//==============================

#include "ranking.h"
#include "input.h"
#include "fade.h"
#include <stdio.h>
#include "score.h"
#include "rankscore.h"
#include "ranksetdata.h"
#include "sound.h"

//================================
//ランキングの初期化処理
//================================
void InitRanking(void)
{
	InitRankingData();		//順位の初期化

	InitRankingScore();		//ランキングのスコアの初期化

	ResetRanking();			//ランキングのリセット

	SetRankingTexture();	//ランキングのテクスチャ処理

	// 音楽を再生
	PlaySound(SOUND_LABEL_RANKING);
}
//================================
//ランキングの終了処理
//================================
void UninitRanking(void)
{
	// 音楽を止める
	StopSound();

	UninitRankingData();	 //順位の終了処理

	UninitRankingScore();	 //ランキングのスコアの終了処理
}
//================================
//ランキングの更新処理
//================================
void UpdateRanking(void)
{
	UpdateRankingData();	//順位の更新処理

	UpdateRankingScore();	//ランキングのスコアの更新処理
}
//================================
//ランキングの描画処理
//================================
void DrawRanking(void)
{
	DrawRankingData();		//順位の描画処理

	DrawRankingScore();		//ランキングのスコアの描画処理
}
