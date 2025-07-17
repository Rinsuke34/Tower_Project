/* 2025.07.01 駒沢風助 ファイル作成 */

#include "Building_Base.h"

/* すべての建造物のベースとなるクラスの定義 */
// コンストラクタ
Building_Base::Building_Base(int iFactionNo) : Object_Base()
{
	// 初期化処理
	this->iNowHp		= 0;			// 残り体力を初期化
	this->stMapPosition	= { 0, 0, 0 };	// 座標を初期化
	this->iFactionNo	= iFactionNo;	// 陣営番号を設定
}
