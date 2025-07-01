/* 2025.06.13 駒沢風助 ファイル追加 */

#include "Scene_World.h"

/* シーン"ゲームメイン"の定義 */
// コンストラクタ
Scene_World::Scene_World() : SceneBase("Scene_World", 0, false)
{
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
	this->vecCameraPos			= VGet(0, 0, 0);	// カメラ移動量
	this->vecCameraTargetPos	= VGet(0, 0, 0);	// カメラ注視点移動量
	this->fCameraAngleX			= 0.0f;				// カメラX軸回転量
	this->fCameraAngleY			= 0.0f;				// カメラY軸回転量
	this->stSelectionPosition	= { 0, 0, 0 };		// 選択中の座標

	/* マップ読み込み */
    MapLoad();

    /* カメラ位置初期化 */
    this->vecCameraPos         = VGet(0, 0, 0);		// カメラ移動量
    this->vecCameraTargetPos   = VGet(0, 0, 0);		// カメラ注視点移動量
}

// 計算
void Scene_World::Process()
{
	/* 前後左右の入力で位置を変更 */
	const float	fSpeed	= 10.0f;			// 移動速度
	VECTOR		vecMove	= VGet(0, 0, 0);	// 移動量

	float angle = this->fCameraAngleX;

	// 前進
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_W])
	{
		vecMove.x += -sinf(angle) * fSpeed;
		vecMove.z += +cosf(angle) * fSpeed;
	}
	// 後退
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_S])
	{
		vecMove.x -= -sinf(angle) * fSpeed;
		vecMove.z -= +cosf(angle) * fSpeed;
	}
	// 左移動
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_A])
	{
		vecMove.x += -cosf(angle) * fSpeed;
		vecMove.z += -sinf(angle) * fSpeed;
	}
	// 右移動
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_D])
	{
		vecMove.x += +cosf(angle) * fSpeed;
		vecMove.z += +sinf(angle) * fSpeed;
	}
	// 上昇
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_SPACE])
	{
		this->vecCameraPos.y += fSpeed;
	}
	// 下降
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_LSHIFT])
	{
		this->vecCameraPos.y -= fSpeed;
	}

	/* 移動量分カメラ位置を移動 */
	this->vecCameraPos.x += vecMove.x;
	this->vecCameraPos.z += vecMove.z;

	/* カメラ注視点の算出 */
	// マウス移動量
	this->fCameraAngleX -= gstKeyboardInputData.iMouseMoveX * 0.01f;	// X軸回転量
	this->fCameraAngleY -= gstKeyboardInputData.iMouseMoveY * 0.01f;	// Y軸回転量

	// Y軸回転制限
	float fLimit = DX_PI_F / 2 - 0.01f;	// 約90度
	if (this->fCameraAngleY > fLimit)	{	this->fCameraAngleY = fLimit;	}
	if (this->fCameraAngleY < -fLimit)	{	this->fCameraAngleY = -fLimit;	}

	// カメラ注視点の設定
	const float fScale = 200.f;	// カメラ注視点の距離
	this->vecCameraTargetPos.x = fScale * cosf(this->fCameraAngleY) * -sinf(this->fCameraAngleX) + this->vecCameraPos.x;
	this->vecCameraTargetPos.y = fScale * sinf(this->fCameraAngleY) + this->vecCameraPos.y;
	this->vecCameraTargetPos.z = fScale * cosf(this->fCameraAngleY) * cosf(this->fCameraAngleX) + this->vecCameraPos.z;

	/* 選択中の座標を取得 */
	// カメラ注視点がどのブロックに当たっているかを計算
	this->stSelectionPosition.iX = static_cast<int>((this->vecCameraTargetPos.x + this->vecCameraPos.x) / TILE_SIZE_PIXEL_X);
	this->stSelectionPosition.iY = static_cast<int>((this->vecCameraTargetPos.y + this->vecCameraPos.y) / TILE_SIZE_PIXEL_Y);
	this->stSelectionPosition.iZ = static_cast<int>((this->vecCameraTargetPos.z + this->vecCameraPos.z) / TILE_SIZE_PIXEL_Z);

	/* オブジェクトの更新処理 */
	this->pDataList_Object->Object_Update();
}

// 描画
void Scene_World::Draw()
{
	/* ライティング無効 */
	SetUseLighting(FALSE);

    /* カメラ設定 */
    SetCameraPositionAndTargetAndUpVec(this->vecCameraPos, this->vecCameraTargetPos, VGet(0.0f, 1.0f, 0.f));

	// 裏面描写有効
	SetUseBackCulling(TRUE);

    /* 足場の描写 */
	for (int iX = 0; iX < MAP_SIZE_X; iX++)
	{
		for (int iY = 0; iY < MAP_SIZE_Y; iY++)
		{
			for (int iZ = 0; iZ < MAP_SIZE_Z; iZ++)
			{
				/* IDを取得 */
				int iId = pDataList_Object->aiMapData[iX][iY][iZ];

				/* IDが1あるか */
				if (iId == 1)
				{
					/* 中心座標を取得(int型で保存されているのでfloat型で取得) */
					float fX = static_cast<float>(iX * TILE_SIZE_PIXEL_X);
					float fY = static_cast<float>(iY * TILE_SIZE_PIXEL_Y);
					float fZ = static_cast<float>(iZ * TILE_SIZE_PIXEL_Z);

                    /* 中心座標を基準とした立方体の頂点座標を計算 */
					VERTEX3D aVertex[8];
					aVertex[0].pos = VGet(fX + TILE_SIZE_PIXEL_X / 2, fY + TILE_SIZE_PIXEL_Y / 2, fZ + TILE_SIZE_PIXEL_Z / 2);
					aVertex[1].pos = VGet(fX + TILE_SIZE_PIXEL_X / 2, fY + TILE_SIZE_PIXEL_Y / 2, fZ - TILE_SIZE_PIXEL_Z / 2);
					aVertex[2].pos = VGet(fX + TILE_SIZE_PIXEL_X / 2, fY - TILE_SIZE_PIXEL_Y / 2, fZ + TILE_SIZE_PIXEL_Z / 2);
					aVertex[3].pos = VGet(fX + TILE_SIZE_PIXEL_X / 2, fY - TILE_SIZE_PIXEL_Y / 2, fZ - TILE_SIZE_PIXEL_Z / 2);
					aVertex[4].pos = VGet(fX - TILE_SIZE_PIXEL_X / 2, fY + TILE_SIZE_PIXEL_Y / 2, fZ + TILE_SIZE_PIXEL_Z / 2);
					aVertex[5].pos = VGet(fX - TILE_SIZE_PIXEL_X / 2, fY + TILE_SIZE_PIXEL_Y / 2, fZ - TILE_SIZE_PIXEL_Z / 2);
					aVertex[6].pos = VGet(fX - TILE_SIZE_PIXEL_X / 2, fY - TILE_SIZE_PIXEL_Y / 2, fZ + TILE_SIZE_PIXEL_Z / 2);
					aVertex[7].pos = VGet(fX - TILE_SIZE_PIXEL_X / 2, fY - TILE_SIZE_PIXEL_Y / 2, fZ - TILE_SIZE_PIXEL_Z / 2);

					for (int i = 0; i < 8; ++i)
					{
						aVertex[i].dif  = GetColorU8(255, 255, 255, 255);	// 拡散光の色
						aVertex[i].spc  = GetColorU8(0, 0, 0, 0);			// 鏡面光の色
						aVertex[i].su   = 0.0f;								// スペキュラのU座標
						aVertex[i].sv   = 0.0f;								// スペキュラのV座標
					}

                    /* Y+方向の最大位置、あるいはY+方向座標にブロックが存在している状態であるか */
                    if (iY == MAP_SIZE_Y - 1 || pDataList_Object->aiMapData[iX][iY + 1][iZ] == 0)
                    {
                        /* 上面を描写 */
						// インデックスデータ（上面の2ポリゴン）
						unsigned short IndexTop[6] = { 0, 1, 4, 4, 1, 5 };

						// 法線ベクトルを設定
						for (int i = 0; i < 8; ++i)
						{
							aVertex[i].norm = VGet(0.0f, 1.0f, 0.0f); //
						}

						// uv座標を設定
						aVertex[0].u = 1.f;
						aVertex[0].v = 0.f;
						aVertex[1].u = 1.f;
						aVertex[1].v = 1.f;
						aVertex[4].u = 0.f;
						aVertex[4].v = 0.f;
						aVertex[5].u = 0.f;
						aVertex[5].v = 1.f;

						// 四角形（板ポリゴン）の描画
						DrawPolygonIndexed3D(aVertex, 8, IndexTop, 2, gpDataList_Texture->aiGrHandle_SampleBlock[DIRECTION_TOP], TRUE);
                    }

                    /* Y-方向の最大位置、あるいはY-方向座標にブロックが存在していない状態であるか */
                    if (iY == 0 || pDataList_Object->aiMapData[iX][iY - 1][iZ] == 0)
                    {
                        /* 底面を描写 */
                        // インデックスデータ（底面の2ポリゴン）
                        unsigned short IndexBottom[6] = { 6, 3, 2, 7, 3, 6 };

						// 法線ベクトルを設定
						for (int i = 0; i < 8; ++i)
						{
							aVertex[i].norm = VGet(0.0f, -1.0f, 0.0f);
						}

						// uv座標を設定
						aVertex[2].u = 1.f;
						aVertex[2].v = 0.f;
						aVertex[3].u = 1.f;
						aVertex[3].v = 1.f;
						aVertex[6].u = 0.f;
						aVertex[6].v = 0.f;
						aVertex[7].u = 0.f;
						aVertex[7].v = 1.f;

                        // 四角形（板ポリゴン）の描画
                        DrawPolygonIndexed3D(aVertex, 8, IndexBottom, 2, gpDataList_Texture->aiGrHandle_SampleBlock[DIRECTION_BOTTOM], TRUE);
                    }

					/* X+方向の最大位置、あるいはX+方向座標にブロックが存在している状態であるか */
					if (iX == MAP_SIZE_X - 1 || pDataList_Object->aiMapData[iX + 1][iY][iZ] == 0)
					{
						/* 右面を描写 */
						// インデックスデータ（右面の2ポリゴン）
						unsigned short IndexRight[6] = { 3, 1, 2, 2, 1, 0 };

						// 法線ベクトルを設定
						for (int i = 0; i < 8; ++i)
						{
							aVertex[i].norm = VGet(+1.0f, 0.0f, 0.0f);
						}

						// uv座標を設定
						aVertex[0].u = 0.f;
						aVertex[0].v = 0.f;
						aVertex[1].u = 1.f;
						aVertex[1].v = 0.f;
						aVertex[2].u = 0.f;
						aVertex[2].v = 1.f;
						aVertex[3].u = 1.f;
						aVertex[3].v = 1.f;

						// 四角形（板ポリゴン）の描画
						DrawPolygonIndexed3D(aVertex, 8, IndexRight, 2, gpDataList_Texture->aiGrHandle_SampleBlock[DIRECTION_SIDE], TRUE);
					}

					/* X-方向の最大位置、あるいはX-方向座標にブロックが存在していない状態であるか */
					if (iX == 0 || pDataList_Object->aiMapData[iX - 1][iY][iZ] == 0)
					{
						/* 左面を描写 */
						// インデックスデータ（左面の2ポリゴン）
						unsigned short IndexLeft[6] = { 6, 4, 7, 7, 4, 5 };

						// 法線ベクトルを設定
						for (int i = 0; i < 8; ++i)
						{
							aVertex[i].norm = VGet(-1.0f, 0.0f, 0.0f);
						}

						// uv座標を設定
						aVertex[4].u = 0.f;
						aVertex[4].v = 0.f;
						aVertex[5].u = 1.f;
						aVertex[5].v = 0.f;
						aVertex[6].u = 0.f;
						aVertex[6].v = 1.f;
						aVertex[7].u = 1.f;
						aVertex[7].v = 1.f;

						// 四角形（板ポリゴン）の描画
						DrawPolygonIndexed3D(aVertex, 8, IndexLeft, 2, gpDataList_Texture->aiGrHandle_SampleBlock[DIRECTION_SIDE], TRUE);
					}

					/* Z+方向の最大位置、あるいはZ+方向座標にブロックが存在している状態であるか */
					if (iZ == MAP_SIZE_Z - 1 || pDataList_Object->aiMapData[iX][iY][iZ + 1] == 0)
					{
						/* 手前面を描写 */
						// インデックスデータ（手前面の2ポリゴン）
						unsigned short IndexFront[6] = { 2, 0, 6, 6, 0, 4 };

						// 法線ベクトルを設定
						for (int i = 0; i < 8; ++i)
						{
							aVertex[i].norm = VGet(0.0f, 0.0f, +1.0f);
						}

						// uv座標を設定
						aVertex[0].u = 1.f;
						aVertex[0].v = 0.f;
						aVertex[2].u = 1.f;
						aVertex[2].v = 1.f;
						aVertex[4].u = 0.f;
						aVertex[4].v = 0.f;
						aVertex[6].u = 0.f;
						aVertex[6].v = 1.f;

						// 四角形（板ポリゴン）の描画
						DrawPolygonIndexed3D(aVertex, 8, IndexFront, 2, gpDataList_Texture->aiGrHandle_SampleBlock[DIRECTION_SIDE], TRUE);
					}

					/* Z-方向の最大位置、あるいはZ-方向座標にブロックが存在していない状態であるか */
					if (iZ == 0 || pDataList_Object->aiMapData[iX][iY][iZ - 1] == 0)
					{
						/* 奥面を描写 */
						// インデックスデータ（奥面の2ポリゴン）
						unsigned short IndexBack[6] = { 7, 5, 3, 3, 5, 1 };

						// 法線ベクトルを設定
						for (int i = 0; i < 8; ++i)
						{
							aVertex[i].norm = VGet(0.0f, 0.0f, -1.0f);
						}

						// uv座標を設定
						aVertex[1].u = 1.f;
						aVertex[1].v = 0.f;
						aVertex[3].u = 1.f;
						aVertex[3].v = 1.f;
						aVertex[5].u = 0.f;
						aVertex[5].v = 0.f;
						aVertex[7].u = 0.f;
						aVertex[7].v = 1.f;

						// 四角形（板ポリゴン）の描画
						DrawPolygonIndexed3D(aVertex, 8, IndexBack, 2, gpDataList_Texture->aiGrHandle_SampleBlock[DIRECTION_SIDE], TRUE);
					}
				}
			}
		}
	}

	// カメラ注視点に交差線を描写
	DrawLine3D(VAdd(this->vecCameraTargetPos, VGet(+10.f, 0.f, 0.f)), VAdd(this->vecCameraTargetPos, VGet(-10.f, 0.f, 0.f)), GetColor(255, 0, 0));
	DrawLine3D(VAdd(this->vecCameraTargetPos, VGet(0.f, +10.f, 0.f)), VAdd(this->vecCameraTargetPos, VGet(0.f, -10.f, 0.f)), GetColor(0, 255, 0));
	DrawLine3D(VAdd(this->vecCameraTargetPos, VGet(0.f, 0.f, +10.f)), VAdd(this->vecCameraTargetPos, VGet(0.f, 0.f, -10.f)), GetColor(0, 0, 255));

	// オブジェクトの描写処理
	this->pDataList_Object->Object_Draw();
}

