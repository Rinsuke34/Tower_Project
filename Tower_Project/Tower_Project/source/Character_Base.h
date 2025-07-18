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

		void			RouteSearch();			// ルート探索処理

	protected:
		/* 変数 */
		POSITION_3D_MAP					stMapPosition;				// 座標(マップ上の座標)
		int								iId;

		/* 変数 */
		int	iModelHandle;	// モデルハンドル

		std::vector<POSITION_3D_MAP>	aMovePath;					// 移動ルート
		int								iMovePathIndex;				// 現在の移動ルートのインデックス
		VECTOR							vecNowMoveStartPosition;	// 現在の移動開始座標
		VECTOR							vecNowMoveEndPosition;		// 現在の移動終了座標

		float							fAngle;						// Y軸回転量(ラジアン)
		int								iAttackInterval;			// 攻撃間隔(フレーム数)
};
