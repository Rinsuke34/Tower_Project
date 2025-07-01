/* 2025.07.01 駒沢風助 ファイル作成 */

#pragma once
#include "Character_Base.h"

/* エネミー(歩行/通常)クラスの宣言 */

// エネミー(歩行/通常)クラス
class Character_Enemy_Normal_Walk : public Character_Base
{
	public:
		Character_Enemy_Normal_Walk();				// コンストラクタ
		virtual ~Character_Enemy_Normal_Walk();		// デストラクタ

		virtual void	Initialization()	override;	// 初期化
		virtual void	Update()			override;	// 更新
		virtual void	Draw()				override;	// 描写
		virtual void	Reset()				override;	// リセット処理

	protected:
};
