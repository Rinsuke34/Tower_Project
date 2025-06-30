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

}

// 初期化
void Scene_World::Initialization()
{
	/* マップ読み込み */
    MapLoad();

    /* カメラ位置初期化 */
    this->vecCameraMove         = VGet(0, 0, 0);    // カメラ移動量
    this->vecCameraTargetMove   = VGet(0, 0, 0);	// カメラ注視点移動量
}

// 計算
void Scene_World::Process()
{
    /* 前後左右の入力でカメラ移動量を変更 */
    // 前
    if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_W])
    {
        this->vecCameraMove.z -= 10;
    }
    // 後
    if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_S])
    {
        this->vecCameraMove.z += 10;
    }
    // 左
    if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_A])
    {
        this->vecCameraMove.x += 10;
    }
    // 右
    if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_D])
    {
        this->vecCameraMove.x -= 10;
    }

    /* 十字キーの入力でカメラ注視点移動量を変更 */
	// 上
    if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_UP])
    {
        this->vecCameraTargetMove.z -= 10;
    }
    // 下
    if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_DOWN])
    {
        this->vecCameraTargetMove.z += 10;
    }
    // 左
    if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_LEFT])
    {
        this->vecCameraTargetMove.x += 10;
    }
    // 右
    if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_RIGHT])
    {
        this->vecCameraTargetMove.x -= 10;
    }
}

// 描画
void Scene_World::Draw()
{
    /* カメラ設定 */
    SetCameraPositionAndTargetAndUpVec(VAdd(VGet(0.0f, 1000.0f, 500.f), this->vecCameraMove), VAdd(this->vecCameraTargetMove, VGet(0.0f, 0.0f, 0.f)), VGet(0.0f, 1.0f, 0.f));

    /* 中心に線を交差させる */
	DrawLine3D(VGet(0.0f, 0.0f, -1000.0f), VGet(0.0f, 0.0f, 1000.0f), GetColor(255, 0, 0));
	DrawLine3D(VGet(-1000.0f, 0.0f, 0.0f), VGet(1000.0f, 0.0f, 0.0f), GetColor(0, 255, 0));
	DrawLine3D(VGet(0.0f, -1000.0f, 0.0f), VGet(0.0f, 1000.0f, 0.0f), GetColor(0, 0, 255));

    /* カメラの注視点にも線を交差させる */
	//DrawLine3D(VAdd(VGet(0.0f, 0.0f, -100.0f), this->vecCameraTargetMove), VAdd(VGet(0.0f, 0.0f, 100.0f), this->vecCameraTargetMove), GetColor(255, 0, 0));
	//DrawLine3D(VAdd(VGet(-100.0f, 0.0f, 0.0f), this->vecCameraTargetMove), VAdd(VGet(100.0f, 0.0f, 0.0f), this->vecCameraTargetMove), GetColor(0, 255, 0));
	//DrawLine3D(VAdd(VGet(0.0f, -100.0f, 0.0f), this->vecCameraTargetMove), VAdd(VGet(0.0f, 100.0f, 0.0f), this->vecCameraTargetMove), GetColor(0, 0, 255));

    /* 足場の描写 */
	for (int iX = 0; iX < MAP_SIZE_X; iX++)
	{
		for (int iY = 0; iY < MAP_SIZE_Y; iY++)
		{
			for (int iZ = 0; iZ < MAP_SIZE_Z; iZ++)
			{
				/* IDを取得 */
				int iId = this->aiMapData[iX][iY][iZ];

				/* IDが0以外(何かしらのブロックが存在している)状態であるか */
				if (iId != 0)
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
						aVertex[i].norm = VGet(0.0f, 1.0f, 0.0f);           // 法線ベクトル
						aVertex[i].dif  = GetColorU8(255, 255, 255, 255);   // 拡散光の色
						aVertex[i].spc  = GetColorU8(0, 0, 0, 0);           // 鏡面光の色
						aVertex[i].u    = (i % 2 == 1) ? 1.0f : 0.0f;       // テクスチャ座標U
						aVertex[i].v    = (i >= 2) ? 1.0f : 0.0f;           // テクスチャ座標V
						aVertex[i].su   = 0.0f;                             // スペキュラのU座標
						aVertex[i].sv   = 0.0f;                             // スペキュラのV座標
					}

                    /* Y+方向の最大位置、あるいはY+方向座標にブロックが存在している状態であるか */
                    if (iY == MAP_SIZE_Y - 1 || this->aiMapData[iX][iY + 1][iZ] == 0)
                    {
                        /* 上面を描写 */
						// インデックスデータ（上面の2ポリゴン）
						unsigned short IndexTop[6] = { 0, 1, 4, 4, 1, 5 };

						// 四角形（板ポリゴン）の描画
						DrawPolygonIndexed3D(aVertex, 8, IndexTop, 2, gpDataList_Texture->aiGrHandle_SampleBlock[DIRECTION_TOP], FALSE);
                    }

                    /* Y-方向の最大位置、あるいはY-方向座標にブロックが存在していないじょうたいであるか */
                    if (iY == 0 || this->aiMapData[iX][iY - 1][iZ] == 0)
                    {
                        /* 底面を描写 */
                        // インデックスデータ（底面の2ポリゴン）
                        unsigned short IndexBottom[6] = { 3, 2, 7, 7, 2, 6 };

                        // 四角形（板ポリゴン）の描画
                        DrawPolygonIndexed3D(aVertex, 8, IndexBottom, 2, gpDataList_Texture->aiGrHandle_SampleBlock[DIRECTION_BOTTOM], FALSE);
                    }

					/* X+方向の最大位置、あるいはX+方向座標にブロックが存在している状態であるか */
					if (iX == MAP_SIZE_X - 1 || this->aiMapData[iX + 1][iY][iZ] == 0)
					{
						/* 右面を描写 */
						// インデックスデータ（右面の2ポリゴン）
						unsigned short IndexRight[6] = { 3, 1, 2, 2, 1, 0 };

						// 四角形（板ポリゴン）の描画
						DrawPolygonIndexed3D(aVertex, 8, IndexRight, 2, gpDataList_Texture->aiGrHandle_SampleBlock[DIRECTION_SIDE], FALSE);
					}

					/* X-方向の最大位置、あるいはX-方向座標にブロックが存在していないじょうたいであるか */
					if (iX == 0 || this->aiMapData[iX - 1][iY][iZ] == 0)
					{
						/* 左面を描写 */
						// インデックスデータ（左面の2ポリゴン）
						unsigned short IndexLeft[6] = { 6, 4, 7, 7, 4, 5 };

						// 四角形（板ポリゴン）の描画
						DrawPolygonIndexed3D(aVertex, 8, IndexLeft, 2, gpDataList_Texture->aiGrHandle_SampleBlock[DIRECTION_SIDE], FALSE);
					}

					/* Z+方向の最大位置、あるいはZ+方向座標にブロックが存在している状態であるか */
					if (iZ == MAP_SIZE_Z - 1 || this->aiMapData[iX][iY][iZ + 1] == 0)
					{
						/* 手前面を描写 */
						// インデックスデータ（手前面の2ポリゴン）
						unsigned short IndexFront[6] = { 2, 0, 6, 6, 0, 4 };

						// 四角形（板ポリゴン）の描画
						DrawPolygonIndexed3D(aVertex, 8, IndexFront, 2, gpDataList_Texture->aiGrHandle_SampleBlock[DIRECTION_SIDE], FALSE);
					}

					/* Z-方向の最大位置、あるいはZ-方向座標にブロックが存在していないじょうたいであるか */
					if (iZ == 0 || this->aiMapData[iX][iY][iZ - 1] == 0)
					{
						/* 奥面を描写 */
						// インデックスデータ（奥面の2ポリゴン）
						unsigned short IndexBack[6] = { 7, 5, 3, 3, 5, 1 };

						// 四角形（板ポリゴン）の描画
						DrawPolygonIndexed3D(aVertex, 8, IndexBack, 2, gpDataList_Texture->aiGrHandle_SampleBlock[DIRECTION_SIDE], FALSE);
					}
				}
			}
		}
	}
}

