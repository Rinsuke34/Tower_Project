/* 2025.06.13 駒沢風助 ファイル追加 */

#include "AppFrame.h"

#include "StructDefine.h"
#include "ConstantDefine.h"

#include <nlohmann/json.hpp>
#include <fstream>

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

	private:
		/* 関数 */
		void	MapLoad();		// マップ読み込み

		/* 変数 */
		std::vector<MAP_DATA>	vMapData_Chunks;	// チャンクのデータ
		int						iGrHandle;
};
