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
	SetUseLighting(FALSE);

	/* カメラ設定 */
	SetCameraPositionAndTargetAndUpVec( VGet(0.0f, 500.0f, -500.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.f, 1.f, 0.0f));

	/* オブジェクト描写 */
	DrawLine3D(VGet(100.0f, 0.0f, 0.0f), VGet(-100.0f, 0.0f, 0.0f), GetColor(255, 0, 0));
	DrawLine3D(VGet(0.0f, 0.0f, 100.0f), VGet(0.0f, 0.0f, -100.0f), GetColor(0, 0, 255));

	DrawTriangle3D(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 100.0f), VGet(100.0f, 0.0f, 0.0f), GetColor(255, 255, 255), TRUE);
}

