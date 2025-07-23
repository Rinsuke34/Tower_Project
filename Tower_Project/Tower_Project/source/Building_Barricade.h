/* 2025.07.17 駒沢風助 ファイル作成 */

#pragma once
#include "Building_Base.h"

/* バリケードクラスの宣言 */

// バリケードクラス
class Building_Barricade : public Building_Base
{
	public:
		Building_Barricade();				// コンストラクタ
		virtual ~Building_Barricade();		// デストラクタ

		virtual void	Initialization()	override;	// 初期化
		virtual void	Update()			override;	// 更新
		virtual void	Draw()				override;	// 描写
};
