/* 2025.07.13 駒沢風助 ファイル作成 */

#include "Building_EnemySpawner.h"

#include "ConstantDefine.h"

#include "DataList_Object.h"

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
	// マップ上の座標から実際の座標を設定
	this->vecPosition.x = this->stMapPosition.iX * TILE_SIZE_PIXEL_X;							// X座標を設定
	this->vecPosition.y = this->stMapPosition.iY * TILE_SIZE_PIXEL_Y - (TILE_SIZE_PIXEL_Y / 2);	// Y座標を設定
	this->vecPosition.z = this->stMapPosition.iZ * TILE_SIZE_PIXEL_Z;							// Z座標を設定

	// データリスト上にこのオブジェクトの情報を設定
	MAP_DATA stMapData = { this->stMapPosition.iX, this->stMapPosition.iY, this->stMapPosition.iZ, OBJECT_ID_ENEMY_SPAWNER };
	static_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->aMapBuildingData.push_back(stMapData);
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
	// モデルの位置を設定
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	// モデルの描写
	MV1DrawModel(this->iModelHandle);
}
