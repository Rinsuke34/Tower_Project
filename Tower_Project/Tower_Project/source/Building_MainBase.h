/* 2025.07.01 駒沢風助 ファイル作成 */

#pragma once
#include "Building_Base.h"

/* メイン拠点クラスの宣言 */

// メイン拠点クラス
class Building_MainBase : public Building_Base
{
	public:
		Building_MainBase();				// コンストラクタ
		virtual ~Building_MainBase();		// デストラクタ

		virtual void	Initialization()	override;	// 初期化
		virtual void	Update()			override;	// 更新
		virtual void	Draw()				override;	// 描写

	private:
		/* 変数 */
		int	iModelHandle;	// モデルハンドル
};
