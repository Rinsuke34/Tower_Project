/* 2025.06.13 駒沢風助 ファイル追加 */

#include "AppFrame.h"

#include "StructDefine.h"
#include "ConstantDefine.h"
#include "VariableDefine.h"

#include <nlohmann/json.hpp>
#include <fstream>

/* データリスト */
#include "DataList_Object.h"

/* シーン"ワールド"の宣言 */

// シーン"ワールド"
class Scene_World : public SceneBase
{
	public:
		Scene_World(bool bMapCreateMode);	// コンストラクタ
		virtual ~Scene_World();				// デストラクタ

		virtual void	Initialization()	override;	// 初期化
		virtual void	Process()			override;	// 計算
		virtual void	Draw()				override;	// 描画

	private:
		/* 関数 */
		void	MapLoad();			// マップ読み込み
		void	MapCreate();		// マップ作成処理
		void	MapSave();			// マップ保存
		void	DrawMapCreate();	// マップ作成描写

		void	CameraControl();	// カメラ制御
		void	DrawBlock();		// 足場描写
		void	SelectPosition();	// 選択座標変更処理

		void	Cmaera_TopView();	// トップビューカメラ
		void	Camera_FPS();		// FPSカメラ

		DataList_Object*	pDataList_Object;	// オブジェクトデータリスト

		/* 変数 */
		VECTOR	vecCameraPos;					// カメラ移動量
		VECTOR	vecCameraTargetPos;				// カメラ注視点移動量
		float	fCameraAngleX;					// カメラX軸回転量
		float	fCameraAngleY;					// カメラY軸回転量

		int		iCameraMode;					// カメラモード（0:トップビュー, 1:FPSカメラ）

		bool	bMapCreateMode;					// マップ作成モードフラグ
		int		iAddBlockId;					// 追加するブロックのID

		POSITION_3D_MAP	stSelectionPosition;	// 選択中の座標
};
