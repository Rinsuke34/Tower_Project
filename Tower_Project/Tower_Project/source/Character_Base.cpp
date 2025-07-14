/* 2025.07.01 駒沢風助 ファイル作成 */

#include "Character_Base.h"

/* すべてのキャラクターのベースとなるクラスの定義 */
// コンストラクタ
Character_Base::Character_Base(int iId) : Object_Base()
{
	// IDを設定
	this->iId = iId;
}
