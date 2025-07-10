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

		void SetPosition(POSITION_3D_MAP stPosition) { this->stMapPosition = stPosition; };	// 座標を設定

	protected:
		std::vector<POSITION_3D_MAP>	aMovePath;					// 移動ルート
		int								iMovePathIndex;				// 現在の移動ルートのインデックス
		VECTOR							vecNowMoveStartPosition;	// 現在の移動開始座標
		VECTOR							vecNowMoveEndPosition;		// 現在の移動終了座標
		POSITION_3D_MAP					stMapPosition;				// 座標(マップ上の座標)
};
