/* 2025.06.19 駒沢風助 ファイル作成 */

#pragma once

/* プロジェクトで使用する定数の宣言 */

/* マップ系 */
// マップのサイズ
constexpr int MAP_SIZE_X	=	64;		// マップのX軸サイズ(タイル数単位)
constexpr int MAP_SIZE_Y	=	16;			// マップのY軸サイズ(タイル数単位)
constexpr int MAP_SIZE_Z	=	64;		// マップのZ軸サイズ(タイル数単位)

// タイルのサイズ
static const int TILE_SIZE_PIXEL_X	= 64;	// タイルのX軸サイズ(ピクセル単位)
static const int TILE_SIZE_PIXEL_Y	= 32;	// タイルのY軸サイズ(ピクセル単位)
static const int TILE_SIZE_PIXEL_Z	= 64;	// タイルのZ軸サイズ(ピクセル単位)

// 向き
static const int DIRECTION_TOP		= 0;	// 上面
static const int DIRECTION_BOTTOM	= 1;	// 下面
static const int DIRECTION_SIDE		= 2;	// 側面
