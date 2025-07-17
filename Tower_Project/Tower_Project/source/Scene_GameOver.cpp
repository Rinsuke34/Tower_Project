/* 2025.07.18 駒沢風助 ファイル追加 */

#include "Scene_GameOver.h"
#include "Scene_Title.h"

/* シーン"ゲームオーバー"の定義 */
// コンストラクタ
Scene_GameOver::Scene_GameOver(int iScore) : SceneBase("Scene_GameOver", 0, false)
{
	// スコアを設定
	this->iScore = iScore;
}

// デストラクタ
Scene_GameOver::~Scene_GameOver()
{

}

// 初期化
void Scene_GameOver::Initialization()
{

}

// 計算
void Scene_GameOver::Process()
{
	/* 入力待ち */
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_Z] == TRUE)
	{
		/* シーン"タイトル"をセット */
		gpSceneServer->AddSceneReservation(new Scene_Title);

		/* シーン削除フラグを有効にする */
		this->bDeleteFlg = true;
	}
}

// 描画
void Scene_GameOver::Draw()
{
	DrawString(SCREEN_SIZE_WIDE / 2, SCREEN_SIZE_HEIGHT / 2, "ゲームオーバー", GetColor(255, 255, 255));
	DrawString(SCREEN_SIZE_WIDE / 2, SCREEN_SIZE_HEIGHT / 2 - 20, "Z:タイトルへ", GetColor(255, 255, 255));
	DrawFormatString(SCREEN_SIZE_WIDE / 2, SCREEN_SIZE_HEIGHT / 2 - 40, GetColor(255, 255, 255), "スコア: %d", this->iScore);
}
