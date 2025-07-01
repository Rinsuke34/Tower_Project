/* 2025.07.01 駒沢風助 ファイル作成 */

#include "Character_Enemy_Normal_Walk.h"

#include "StructDefine.h"
#include "ConstantDefine.h"

/* エネミー(歩行/通常)クラスの定義 */
// コンストラクタ
Character_Enemy_Normal_Walk::Character_Enemy_Normal_Walk() : Character_Base()
{

}

// デストラクタ
Character_Enemy_Normal_Walk::~Character_Enemy_Normal_Walk()
{

}

// 初期化
void Character_Enemy_Normal_Walk::Initialization()
{

}

// 更新
void Character_Enemy_Normal_Walk::Update()
{
	// 現在の座標からマップ上の座標を取得
	POSITION_3D_MAP stMapPosition = { 0, 0, 0 };
	stMapPosition.iX = static_cast<int>(this->vecPosition.x / TILE_SIZE_PIXEL_X);	// X座標を設定
	stMapPosition.iY = static_cast<int>(this->vecPosition.y / TILE_SIZE_PIXEL_Y);	// Y座標を設定
	stMapPosition.iZ = static_cast<int>(this->vecPosition.z / TILE_SIZE_PIXEL_Z);	// Z座標を設定

	// マップ上の座標から見て
}

// 描写
void Character_Enemy_Normal_Walk::Draw()
{

}

// リセット処理
void Character_Enemy_Normal_Walk::Reset()
{

}
