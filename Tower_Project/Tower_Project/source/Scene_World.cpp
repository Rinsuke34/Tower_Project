/* 2025.06.13 駒沢風助 ファイル追加 */

#include "Scene_World.h"

#include "Scene_GameOver.h"

/* シーン"ゲームメイン"の定義 */
// コンストラクタ
Scene_World::Scene_World(bool bMapCreateMode) : SceneBase("Scene_World", 0, false)
{
	// 引数
	// bMapCreateMode: マップ作成モードフラグ

	// マップ作成モード関連のフラグ設定
	this->bMapCreateMode	= bMapCreateMode;
	this->bAddBuildingMode	= false;
	this->iAddBlockId		= PLATFORM_ID_MINIMUM_VALUE;
	this->iAddBuildingId	= OBJECT_ID_MINIMUM_VALUE;

	this->iHaveCost			= 0;					// 所持コスト
	this->iAddCostInterval	= ADD_COST_INTERVAL;	// コスト追加間隔(フレーム数)
	this->iScore			= 0;					// スコア(生存時間)

	// 初期化処理
	Initialization();
}

// デストラクタ
Scene_World::~Scene_World()
{
	// オブジェクトデータリスト削除
	gpDataListServer->DeleteDataList("DataList_Object");
}

// 初期化
void Scene_World::Initialization()
{
	/* オブジェクトデータリストの生成＆登録 */
	this->pDataList_Object = new DataList_Object();
	gpDataListServer->AddDataList(this->pDataList_Object);

	/* 変数初期化 */
	this->stSelectionPosition	= { 0, 0, 0 };		// 選択中の座標
	this->iAddBlockId			= 0;				// 追加するブロックのID

	/* マップ読み込み */
    MapLoad();

    /* カメラ位置設定初期化 */
	this->iCameraMode			= CAMERA_MODE_TOP_VIEW;	// カメラモード（0:トップビュー, 1:FPSカメラ）
    this->vecCameraPos			= VGet(0, 0, 0);		// カメラ移動量
    this->vecCameraTargetPos	= VGet(0, 0, 0);		// カメラ注視点移動量
}

// 計算
void Scene_World::Process()
{
	/* 選択座標変更処理 */
	SelectPosition();

	/* カメラ制御 */
	CameraControl();

	/* マップ作成モードであるか */
	if (this->bMapCreateMode)
	{
		/* マップ作成処理 */
		MapCreate();
		return;
	}

	/* 建造物作成処理 */
	CreateBuilding();

	/* オブジェクトの更新処理 */
	this->pDataList_Object->Object_Update();

	/* オブジェクトの削除処理 */
	this->pDataList_Object->Object_Delete();

	/* スコア更新 */
	this->iScore++;

	/* メインベースが破壊されたか確認 */
	if (this->pDataList_Object->bMainBaseBleakFlg)
	{
		/* シーン"ゲームオーバー"をセット */
		gpSceneServer->AddSceneReservation(new Scene_GameOver(this->iScore));

		/* シーン削除フラグを有効化する */
		this->bDeleteFlg = true;
		return;
	}
}

// 描画
void Scene_World::Draw()
{
	/* ライティングを無効化 */
	SetUseLighting(FALSE);

    /* カメラ設定 */
    SetCameraPositionAndTargetAndUpVec(this->vecCameraPos, this->vecCameraTargetPos, VGet(0.0f, 1.0f, 0.f));

    /* 足場の描写 */
	DrawBlock();

	/* オブジェクトの描写処理 */
	this->pDataList_Object->Object_Draw();

	/* 選択座標に縦線を描写 */
	DrawLine3D(
		VGet(this->stSelectionPosition.iX * TILE_SIZE_PIXEL_X, 0, this->stSelectionPosition.iZ * TILE_SIZE_PIXEL_Z),
		VGet(this->stSelectionPosition.iX * TILE_SIZE_PIXEL_X, MAP_SIZE_Y * TILE_SIZE_PIXEL_Y, this->stSelectionPosition.iZ * TILE_SIZE_PIXEL_Z),
		GetColor(255, 0, 0)
	);

	/* マップ作成モードであるか */
	if (this->bMapCreateMode)
	{
		/* マップ作成オプションの描写 */
		DrawMapCreate();
	}
	else
	{
		/* 状態の描写 */
		DrawStatus();
	}
}

