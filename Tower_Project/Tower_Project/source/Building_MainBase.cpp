/* 2025.07.01 駒沢風助 ファイル作成 */

#include "Building_MainBase.h"

#include "ConstantDefine.h"

#include "DataList_Object.h"

/* メイン拠点クラスの定義 */
// コンストラクタ
Building_MainBase::Building_MainBase() : Building_Base()
{
	this->iModelHandle = MV1LoadModel("resource/test/flag.mv1");
}

// デストラクタ
Building_MainBase::~Building_MainBase()
{
	MV1DeleteModel(this->iModelHandle);
}

// 初期化
void Building_MainBase::Initialization()
{
	// マップ上の座標から実際の座標を設定
	this->vecPosition.x = this->stMapPosition.iX * TILE_SIZE_PIXEL_X;							// X座標を設定
	this->vecPosition.y = this->stMapPosition.iY * TILE_SIZE_PIXEL_Y - (TILE_SIZE_PIXEL_Y / 2);	// Y座標を設定
	this->vecPosition.z = this->stMapPosition.iZ * TILE_SIZE_PIXEL_Z;							// Z座標を設定

	// データリスト上にこのオブジェクトの情報を設定
	MAP_DATA stMapData = { this->stMapPosition.iX, this->stMapPosition.iY, this->stMapPosition.iZ, 1000 };
	static_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->aMapBuildingData[1000] = stMapData;
}

// 更新
void Building_MainBase::Update()
{


}

// 描写
void Building_MainBase::Draw()
{
	// モデルの位置を設定
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	// モデルの描写
	MV1DrawModel(this->iModelHandle);
}
