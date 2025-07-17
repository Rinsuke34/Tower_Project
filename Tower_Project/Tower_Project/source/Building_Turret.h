/* 2025.07.17 駒沢風助 ファイル作成 */

#pragma once
#include "Building_Base.h"

/* タレットクラスの宣言 */

// タレットクラス
class Building_Turret : public Building_Base
{
	public:
		Building_Turret();				// コンストラクタ
		virtual ~Building_Turret();		// デストラクタ

		virtual void	Initialization()	override;	// 初期化
		virtual void	Update()			override;	// 更新
		virtual void	Draw()				override;	// 描写

	private:
		/* 変数 */
		int		iModelHandle;		// モデルハンドル
		int		iAttackInterval;	// 攻撃間隔(フレーム数)
};
