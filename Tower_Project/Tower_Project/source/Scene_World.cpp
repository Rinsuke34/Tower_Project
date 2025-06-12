/* 2025.06.13 駒沢風助 ファイル追加 */

#include "Scene_World.h"

/* シーン"タイトル"の定義 */
// コンストラクタ
Scene_World::Scene_World() : SceneBase("Scene_World", 0, false)
{
	// 初期化処理
	Initialization();
}

// デストラクタ
Scene_World::~Scene_World()
{

}

// 初期化
void Scene_World::Initialization()
{

}

// 計算
void Scene_World::Process()
{

}

// 描画
void Scene_World::Draw()
{
	/* ワールド画面描写 */
	DrawString(SCREEN_SIZE_WIDE / 2, SCREEN_SIZE_HEIGHT / 2, "ワールド", GetColor(255, 255, 255));
}

