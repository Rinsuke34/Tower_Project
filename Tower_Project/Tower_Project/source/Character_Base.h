/* 2025.07.01 駒沢風助 ファイル作成 */

#pragma once
#include "Object_Base.h"

/* すべてのキャラクターのベースとなるクラスの宣言 */

// キャラクターベースクラス
class Character_Base : public Object_Base
{
	public:
		Character_Base();					// コンストラクタ
		virtual ~Character_Base() {};		// デストラクタ

	protected:
};
