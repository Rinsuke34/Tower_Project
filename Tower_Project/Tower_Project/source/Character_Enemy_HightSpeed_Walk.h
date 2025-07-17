/* 2025.07.18 駒沢風助 ファイル作成 */

#pragma once
#include "Character_Base.h"

#include <vector>
#include "StructDefine.h"

/* エネミー(歩行/高速)クラスの宣言 */

// エネミー(歩行/高速)クラス
class Character_Enemy_HightSpeed_Walk : public Character_Base
{
	public:
		Character_Enemy_HightSpeed_Walk();				// コンストラクタ
		virtual ~Character_Enemy_HightSpeed_Walk();		// デストラクタ

		virtual void	Initialization()	override;	// 初期化
		virtual void	Update()			override;	// 更新
		virtual void	Draw()				override;	// 描写
};
