/* 2025.07.01 駒沢風助 ファイル作成 */

#pragma once
#include "Object_Base.h"

#include "StructDefine.h"

/* すべてのキャラクターのベースとなるクラスの宣言 */

// キャラクターベースクラス
class Character_Base : public Object_Base
{
	public:
		Character_Base(int iId);			// コンストラクタ
		virtual ~Character_Base() {};		// デストラクタ

		void SetPosition(POSITION_3D_MAP stPosition) { this->stMapPosition = stPosition; };	// 座標を設定

		POSITION_3D_MAP GetPosition()	{ return this->stMapPosition; };	// 座標を取得
		int				iGetId()		{ return this->iId; };				// IDを取得

	protected:
		/* 変数 */
		POSITION_3D_MAP					stMapPosition;				// 座標(マップ上の座標)
		int								iId;
};
