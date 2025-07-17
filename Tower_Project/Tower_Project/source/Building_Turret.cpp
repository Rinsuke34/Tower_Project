/* 2025.07.17 駒沢風助 ファイル作成 */

#include "ConstantDefine.h"
#include "DataList_Object.h"
#include "Building_Turret.h"

/* タレットクラスの定義 */
// コンストラクタ
Building_Turret::Building_Turret() : Building_Base(OBJECT_FACTION_PLAYER)
{
	/* 変数 */
	this->iModelHandle = MV1LoadModel("resource/Model/Turret/Turret.mv1");
	this->iMaxHp = OBJECT_HP_MAX_TURRET;	// タレットの最大体力を設定
	this->iNowHp = this->iMaxHp;			// タレットの初期体力を設定
	this->iAttackInterval	= 0;			// 攻撃間隔(フレーム数)
}

// デストラクタ
Building_Turret::~Building_Turret()
{
	MV1DeleteModel(this->iModelHandle);

	// データリスト上からこのオブジェクトの情報を削除
	auto& aMapBuildingData = static_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->aMapBuildingData;
	aMapBuildingData.erase(std::remove_if(aMapBuildingData.begin(), aMapBuildingData.end(),
		[this](const MAP_DATA& data) { return data.iId == OBJECT_ID_TURRET && data.stPosition.iX == this->stMapPosition.iX && data.stPosition.iZ == this->stMapPosition.iZ; }),
		aMapBuildingData.end());
}

// 初期化
void Building_Turret::Initialization()
{
	// マップ上の座標から実際の座標を設定
	this->vecPosition.x = this->stMapPosition.iX * TILE_SIZE_PIXEL_X;							// X座標を設定
	this->vecPosition.y = this->stMapPosition.iY * TILE_SIZE_PIXEL_Y - (TILE_SIZE_PIXEL_Y / 2);	// Y座標を設定
	this->vecPosition.z = this->stMapPosition.iZ * TILE_SIZE_PIXEL_Z;							// Z座標を設定

	// データリスト上にこのオブジェクトの情報を設定
	MAP_DATA stMapData = { this->stMapPosition.iX, this->stMapPosition.iY, this->stMapPosition.iZ, OBJECT_ID_TURRET };
	static_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->aMapBuildingData.push_back(stMapData);
}

// 更新
void Building_Turret::Update()
{
	// 体力が0以下なら削除フラグを立てる
	if (this->iNowHp <= 0)
	{
		this->bDeleteFlg = true;
		return;
	}

	// 周囲に敵キャラクターがいるか確認
	for (auto& Character : static_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->paCharacterList)
	{
		// 攻撃範囲内にいるか確認
		if (VSize(VSub(Character->vecGetPosition(), this->vecPosition)) <= OBJECT_ATTACK_RANGE_TURRET)
		{
			// 攻撃間隔が0であるか確認
			if (this->iAttackInterval <= 0)
			{
				// 攻撃のインターバルを設定
				this->iAttackInterval = OBJECT_ATTACK_INTERVAL_TURRET;

				// 攻撃処理を実行
				Character->ReceivedDamage(OBJECT_ATTACK_DAMAGE_TURRET);
			}
			else
			{
				// 攻撃のインターバルを減らす
				this->iAttackInterval--;
			}

			// 更新処理を終了する
			return;
		}
	}
}

// 描写
void Building_Turret::Draw()
{
	// モデルの位置を設定
	MV1SetPosition(this->iModelHandle, this->vecPosition);

	// モデルの描写
	MV1DrawModel(this->iModelHandle);

	// 体力バーの描写
	DrawHpBar();
}
