/* 2025.06.19 駒沢風助 ファイル作成 */

#pragma once

/* プロジェクトで使用する構造体の宣言 */
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