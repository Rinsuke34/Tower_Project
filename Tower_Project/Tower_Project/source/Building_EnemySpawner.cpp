/* 2025.07.13 駒沢風助 ファイル作成 */

#include "Building_EnemySpawner.h"
#include "ConstantDefine.h"
#include "DataList_Object.h"
#include "Character_Enemy_Normal_Walk.h"
#include "Character_Enemy_HightSpeed_Walk.h"

/* エネミースポナークラスの定義 */
// コンストラクタ
Building_EnemySpawner::Building_EnemySpawner() : Building_Base(OBJECT_FACTION_ENEMY)
{
	/* 変数 */
	this->iModelHandle		= MV1LoadModel("resource/Model/Spawner/Spawner.mv1");
	this->iSpawnInterval	= ENEMY_SPAWN_INTERVAL;
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
	// スポーンのインターバルが完了しているなら再度設定する
	if (this->iSpawnInterval <= 0)
	{
		// エネミーを追加
		Character_Base* pAddCharacter;
		// 1/4で高速、3/4で通常歩行のエネミーをスポーンする
		if ((rand() % 4) == 0)
		{
			pAddCharacter = new Character_Enemy_HightSpeed_Walk();
		}
		else
		{
			pAddCharacter = new Character_Enemy_Normal_Walk();
		}
		DataList_Object* pDataList_Object = static_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
		pDataList_Object->SetCharacter(pAddCharacter);
		pAddCharacter->SetPosition(this->stMapPosition);

		// 追加したエネミーの初期化を行う
		pAddCharacter->Initialization();

		// スポーンまでのインターバルを設定する
		this->iSpawnInterval = ENEMY_SPAWN_INTERVAL;
	}
	else
	{
		// スポーンまでのインターバルを減らす
		this->iSpawnInterval--;
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
