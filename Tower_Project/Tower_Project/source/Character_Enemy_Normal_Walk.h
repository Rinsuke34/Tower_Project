/* 2025.07.01 駒沢風助 ファイル作成 */

#pragma once
#include "Character_Base.h"

#include <vector>
#include "StructDefine.h"

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
		/* 変数 */
		int	iModelHandle;	// モデルハンドル

		std::vector<POSITION_3D_MAP>	aMovePath;					// 移動ルート
		int								iMovePathIndex;				// 現在の移動ルートのインデックス
		VECTOR							vecNowMoveStartPosition;	// 現在の移動開始座標
		VECTOR							vecNowMoveEndPosition;		// 現在の移動終了座標
		
		float							fAngle;						// Y軸回転量(ラジアン)
};
