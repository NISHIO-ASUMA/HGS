//======================================
//
// メッシュの球型の処理 [mashfan.h]
// Author: TEAM_2
//
//======================================
#ifndef _MESHFAN_H_
#define _MESHFAN_H_

//***************************
// インクルードファイル宣言
//***************************
#include "main.h"

//***************************
// マクロ定義
//***************************
// メッシュフィールドのブロック数
#define meshwall_X_BLOCK (10) // X方向のブロック数
#define meshwall_Z_BLOCK (10) // Z方向のブロック数

// メッシュフィールドの頂点数
#define meshwall_VERTEX_NUM ((meshwall_X_BLOCK + 1) * (meshwall_Z_BLOCK + 1))

// メッシュフィールドのインデックス数
#define meshwall_INDEX_NUM (meshwall_X_BLOCK * meshwall_Z_BLOCK * 6)

// メッシュフィールドのプリミティブ数
#define meshwall_PRIMITIVE_NUM ((meshwall_X_BLOCK * meshwall_Z_BLOCK * 2) + ((meshwall_Z_BLOCK - 1) * 2))

//***************************
// プロトタイプ宣言
//***************************
void InitmeshFan(void);
void UninitmeshFan(void);
void UpdatemeshFan(void);
void DrawmeshFan(void);

#endif // !_MESHFAN_H_

