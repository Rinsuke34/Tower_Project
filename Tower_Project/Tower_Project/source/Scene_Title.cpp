/* 2025.05.09 駒沢風助 ファイル追加 */

#include "Scene_Title.h"

/* シーン */
#include "Scene_World.h"

/* シーン"タイトル"の定義 */
// コンストラクタ
Scene_Title::Scene_Title() : SceneBase("Scene_Title", 0, false)
{
	// 初期化処理
	Initialization();
}

// デストラクタ
Scene_Title::~Scene_Title()
{

}

// 初期化
void Scene_Title::Initialization()
{

}

// 計算
void Scene_Title::Process()
{
	/* 入力待ち */
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_Z] == true)
	{
		/* シーン"ワールド"をセット */
		gpSceneServer->AddSceneReservation(new Scene_World());

		/* シーン削除フラグを有効にする */
		this->bDeleteFlg = true;
	}
}

// 描画
void Scene_Title::Draw()
{
	/* タイトル画面描写 */
	DrawString(SCREEN_SIZE_WIDE / 2, SCREEN_SIZE_HEIGHT / 2, "タイトル", GetColor(255, 255, 255));
}

