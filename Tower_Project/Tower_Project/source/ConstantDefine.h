/* 2025.06.19 駒沢風助 ファイル作成 */

#pragma once

/* プロジェクトで使用する定数の宣言 */

/* マップ系 */
// マップのサイズ
constexpr int MAP_SIZE_X	=	64;		// マップのX軸サイズ(タイル数単位)
constexpr int MAP_SIZE_Y	=	8;		// マップのY軸サイズ(タイル数単位)
constexpr int MAP_SIZE_Z	=	64;		// マップのZ軸サイズ(タイル数単位)

// タイルのサイズ
static const int TILE_SIZE_PIXEL_X	= 32;	// タイルのX軸サイズ(ピクセル単位)
static const int TILE_SIZE_PIXEL_Y	= 16;	// タイルのY軸サイズ(ピクセル単位)
static const int TILE_SIZE_PIXEL_Z	= 32;	// タイルのZ軸サイズ(ピクセル単位)

// 向き
static const int DIRECTION_TOP		= 0;	// 上面
static const int DIRECTION_BOTTOM	= 1;	// 下面
static const int DIRECTION_SIDE		= 2;	// 側面

// 移動コスト
static const int MOVE_COST_DEFAULT	= 1;	// デフォルトの移動コスト
static const int MOVE_COST_UP		= 2;	// 上方向の移動コスト
static const int MOVE_COST_DOWN		= 1;	// 下方向の移動コスト

// A*アルゴリズム用ID
static const int ASTER_ID_NONE	= 0;	// 特に何もないノード
static const int ASTAR_ID_START	= 1;	// スタートノード
static const int ASTAR_ID_GOAL	= 2;	// ゴールノード

// オブジェクト用のID
static const int OBJECT_ID_MAIN_BASE			= 1000;	// メインベースのID
static const int OBJECT_ID_ENEMY_NORMAL_WALK	= 2000;	// エネミー(通常歩行)のID
