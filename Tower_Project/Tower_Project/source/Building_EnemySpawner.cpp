/* 2025.07.13 駒沢風助 ファイル作成 */

#include "Building_EnemySpawner.h"

/* エネミースポナークラスの定義 */
// コンストラクタ
Building_EnemySpawner::Building_EnemySpawner() : Building_Base()
{
	/* 変数 */
	this->iModelHandle	= MV1LoadModel("resource/Model/Spawner/Spawner.mv1");
	this->SpawnFlag		= false;
}

// デストラクタ
Building_EnemySpawner::~Building_EnemySpawner()
{
	MV1DeleteModel(this->iModelHandle);
}

// 初期化
void Building_EnemySpawner::Initialization()
{

}

// 更新
void Building_EnemySpawner::Update()
{
	// スポーンフラグが立っている場合、エネミーをスポーンする処理を実行
	if (this->SpawnFlag)
	{
		// エネミーをスポーンする処理をここに記述
		// 例: gpDataListServer->SpawnEnemy(this->stPosition);

		// スポーン後、フラグを下ろす
		this->SpawnFlag = false;
	}
}

// 描写
void Building_EnemySpawner::Draw()
{

}
