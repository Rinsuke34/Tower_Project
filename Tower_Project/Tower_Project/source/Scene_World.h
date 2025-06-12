/* 2025.06.13 駒沢風助 ファイル追加 */

#include "AppFrame.h"

/* シーン"ワールド"の宣言 */

// シーン"ワールド"
class Scene_World : public SceneBase
{
	public:
		Scene_World();				// コンストラクタ
		virtual ~Scene_World();		// デストラクタ

		virtual void	Initialization()	override;	// 初期化
		virtual void	Process()			override;	// 計算
		virtual void	Draw()				override;	// 描画
};
