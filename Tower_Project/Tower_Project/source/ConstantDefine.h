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

static const int DIRECTION_MAX		= 3;	// 向きの最大数

// 移動コスト
static const int MOVE_COST_DEFAULT	= 1;	// デフォルトの移動コスト
static const int MOVE_COST_UP		= 2;	// 上方向の追加移動コスト
static const int MOVE_COST_DOWN		= 1;	// 下方向の追加移動コスト
static const int MOVE_COST_OFF_LOAD	= 2;	// オフロード(道以外)の追加移動コスト

// A*アルゴリズム用ID
static const int ASTER_ID_NONE	= 0;	// 特に何もないノード
static const int ASTAR_ID_START	= 1;	// スタートノード
static const int ASTAR_ID_GOAL	= 2;	// ゴールノード

// オブジェクト用のID
static const int OBJECT_ID_MAIN_BASE				= 1000;	// メインベースのID
static const int OBJECT_ID_ENEMY_SPAWNER			= 1001;	// エネミースポナー
static const int OBJECT_ID_ENEMY_NORMAL_WALK		= 1002;	// エネミー(通常歩行)のID
static const int OBJECT_ID_BARRICADE				= 1003;	// バリケードのID
static const int OBJECT_ID_TURRET					= 1004;	// タレットのID
static const int OBJECT_ID_ENEMY_HIGHTSPEED_WALK	= 1005;	// エネミー(高速歩行)のID

static const int OBJECT_ID_MINIMUM_VALUE		= 1000;	// オブジェクトの最小ID
static const int OBJECT_ID_MAX					= 1006;	// オブジェクトの最大ID

static const int OBJECT_FACTION_PLAYER			= 0;	// プレイヤー側のオブジェクト
static const int OBJECT_FACTION_ENEMY			= 1;	// エネミー側のオブジェクト

// カメラモード
static const int CAMERA_MODE_TOP_VIEW	= 0;	// トップビューカメラ
static const int CAMERA_MODE_FPS		= 1;	// FPSカメラ

// 足場のID
static const int PLATFORM_ID_NONE		= 0;	// なし
static const int PLATFORM_ID_DIRT		= 1;	// 土
static const int PLATFORM_ID_ROAD		= 2;	// 道路
static const int PLATFORM_ID_STONE		= 3;	// 石

static const int PLATFORM_ID_MINIMUM_VALUE	= 1;	// 足場の最小ID
static const int PLATFORM_ID_MAX			= 4;	// 足場の最大ID

// エネミー関連
static const int ENEMY_SPAWN_INTERVAL_SHORTETED	= 60 * 10;	// エネミースポーンの最短時間(フレーム単位)
static const int ENEMY_SPAWN_INTERVAL_RANDOM	= 60 * 20;	// エネミースポーンのランダム時間(フレーム単位)

#define ENEMY_SPAWN_INTERVAL (ENEMY_SPAWN_INTERVAL_SHORTETED + (rand() % ENEMY_SPAWN_INTERVAL_RANDOM))	// エネミースポーンのインターバルのマクロ(フレーム単位)

static const int ENEMY_ATTACK_RANGE		= 64;	// エネミーの攻撃範囲(ピクセル単位)
static const int ENEMY_ATTACK_INTERVAL	= 60;	// エネミーの攻撃間隔(フレーム単位)
static const int ENEMY_ATTACK_DAMAGE	= 1;	// エネミーの攻撃ダメージ
static const int ENEMY_HP_MAX			= 10;	// エネミーの最大体力

// オブジェクト関連
static const int OBJECT_HP_MAX_MAIN_BASE			= 50;	// メイン拠点の最大体力
static const int OBJECT_HP_MAX_BARRICADE			= 20;	// バリケードの最大体力
static const int OBJECT_HP_MAX_TURRET				= 5;	// タレットの最大体力

static const int OBJECT_ATTACK_RANGE_TURRET			= 64 * 4;	// タレットの攻撃範囲(ピクセル単位)
static const int OBJECT_ATTACK_INTERVAL_TURRET		= 60;		// タレットの攻撃間隔(フレーム単位)
static const int OBJECT_ATTACK_DAMAGE_TURRET		= 1;		// タレットの攻撃ダメージ

static const int ADD_COST_INTERVAL = 60 * 5;	// コスト追加の間隔(フレーム単位)
