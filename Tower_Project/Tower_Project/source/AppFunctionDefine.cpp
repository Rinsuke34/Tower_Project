/* 2024.12.08 駒沢風助 ファイル作成 */

#include "AppFrame.h"
#include "VariableDefine.h"

/* シーン */
#include "Scene_Title.h"

/* データリスト */
#include "DataList_Texture.h"

// シーンの設定
namespace SCENE_SET
{
	// ゲーム起動時のシーンをセット
	void	SetFastScene()
	{
		/* シーン"タイトル"をセット */
		gpSceneServer->AddSceneReservation(new Scene_Title());
	}

	// ロードシーンをセット
	void	SetLoadScene()
	{

	}
}

// 初期化
namespace PROJECT_INIT
{
	// プロジェクト初期化処理
	void	Init()
	{
		/* データリスト作成 */
		{
			/* テクスチャデータリストを追加 */
			gpDataListServer->AddDataList(new DataList_Texture());
		}

		/* データリスト取得 */
		{
			/* テクスチャデータリストを取得 */
			gpDataList_Texture = static_cast<DataList_Texture*>(gpDataListServer->GetDataList("DataList_Texture"));
		}
	}
}