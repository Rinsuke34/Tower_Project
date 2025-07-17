/* 2025.06.22 駒沢風助 ファイル作成 */

#include "Object_Base.h"

#include "ConstantDefine.h"

/* すべてのオブジェクトのベースとなるクラスの定義 */

// コンストラクタ
Object_Base::Object_Base()
{
	/* 初期化 */
	this->bDeleteFlg	= false;					// 削除フラグ
	this->vecPosition	= VGet(0.0f, 0.0f, 0.0f);	// オブジェクトの中心座標
	this->iMaxHp		= 0;						// 最大体力を設定
	this->iNowHp		= 0;						// 残り体力を初期化
}

// 体力バーの描写
void Object_Base::DrawHpBar()
{
	// 現在のワールド座標をスクリーン座標に変換
	// ※少し上に表示するため、Y座標を調整
	VECTOR vecScreenPos = ConvWorldPosToScreenPos(VAdd(this->vecPosition, VGet(0, TILE_SIZE_PIXEL_Y * 3, 0)));

	// 最大HP分の体力バーを赤色で描写
	DrawBox(vecScreenPos.x - 20, vecScreenPos.y - 10, vecScreenPos.x + 20, vecScreenPos.y - 5, GetColor(255, 0, 0), true);

	// 現在のHP分の体力バーを緑色で描写
	int iHpWidth = static_cast<int>(40.0f * (static_cast<float>(this->iNowHp) / static_cast<float>(this->iMaxHp)));
	DrawBox(vecScreenPos.x - 20, vecScreenPos.y - 10, vecScreenPos.x - 20 + iHpWidth, vecScreenPos.y - 5, GetColor(0, 255, 0), true);
}
