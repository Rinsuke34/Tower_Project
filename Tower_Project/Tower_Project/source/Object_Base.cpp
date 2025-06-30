/* 2025.06.22 駒沢風助 ファイル作成 */

#include "Object_Base.h"

/* すべてのオブジェクトのベースとなるクラスの定義 */

// コンストラクタ
Object_Base::Object_Base()
{
	/* 初期化 */
	this->bDeleteFlg	= false;					// 削除フラグ
	this->vecPosition	= VGet(0.0f, 0.0f, 0.0f);	// オブジェクトの中心座標
}
