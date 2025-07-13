/* 2025.07.13 駒沢風助 ファイル作成 */

#pragma once
#include "Building_Base.h"

/* エネミースポナークラスの宣言 */

// エネミースポナークラス
class Building_EnemySpawner : public Building_Base
{
	public:
		Building_EnemySpawner();				// コンストラクタ
		virtual ~Building_EnemySpawner();		// デストラクタ

		virtual void	Initialization()	override;	// 初期化
		virtual void	Update()			override;	// 更新
		virtual void	Draw()				override;	// 描写

	private:
		/* 変数 */
		int	iModelHandle;	// モデルハンドル
};
