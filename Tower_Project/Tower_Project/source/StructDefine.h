/* 2025.06.19 駒沢風助 ファイル作成 */

#pragma once

/* プロジェクトで使用する構造体の宣言 */

// ※下記の情報は使わないかも
// 3D座標情報(マップ)
struct POSITION_3D_MAP
{
	int iX;
	int iY;
	int iZ;
};

// マップ情報
struct MAP_DATA
{
	POSITION_3D_MAP stPosition;	// 座標
	int				iId;		// ID
};

// 評価リスト(A*アルゴリズム用)
struct ASTAR_EVALUATION_LIST
{
	int iId;					// ID
	int iG;						// スタートからのコスト
	int iH;						// ゴールまでの予想コスト
	int iF;						// 総コスト
	bool bOpen;					// オープンリストにあるかどうか
	bool bClose;				// クローズリストにあるかどうか
	POSITION_3D_MAP	stParent;	// 親座標
};