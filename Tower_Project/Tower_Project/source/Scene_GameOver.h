/* 2025.07.18 駒沢風助 ファイル追加 */

#include "AppFrame.h"

/* シーン"ゲームオーバー"の宣言 */

// シーン"ゲームオーバー"
class Scene_GameOver : public SceneBase
{
	public:
		Scene_GameOver(int iScore);		// コンストラクタ
		virtual ~Scene_GameOver();		// デストラクタ

		virtual void	Initialization()	override;	// 初期化
		virtual void	Process()			override;	// 計算
		virtual void	Draw()				override;	// 描画

	private:
		int iScore;				// スコア
};
