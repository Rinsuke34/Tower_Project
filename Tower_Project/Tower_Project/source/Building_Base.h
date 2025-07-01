/* 2025.07.01 駒沢風助 ファイル作成 */

#pragma once
#include "Object_Base.h"

#include "StructDefine.h"

/* すべての建造物のベースとなるクラスの宣言 */

// 建造物ベースクラス
class Building_Base : public Object_Base
{
	public:
		Building_Base();					// コンストラクタ
		virtual ~Building_Base() {};		// デストラクタ

		void SetHp(int iHp)								{	this->iHp			= iHp;			};	// 残り体力を設定
		void SetPosition(POSITION_3D_MAP stPosition)	{	this->stMapPosition	= stPosition;	};	// 座標を設定

		int				iGetHp()		{	return this->iHp;			};	// 残り体力を取得
		POSITION_3D_MAP	GetPosition()	{	return this->stMapPosition;	};	// 座標を取得

	protected:
		/* 変数 */
		int				iHp;				// 残り体力
		POSITION_3D_MAP	stMapPosition;		// 座標(マップ上の座標)
};
