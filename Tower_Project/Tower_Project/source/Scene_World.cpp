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

    /* テスト画像読み込み */
    //aiTestGrHandle[0];  // 上
    //aiTestGrHandle[1];  // 手前
    //aiTestGrHandle[2];  // 左
    //aiTestGrHandle[3];  // 奥
    //aiTestGrHandle[4];  // 右

    iGrHandle = LoadGraph("resource/test.png");;
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
    SetCameraPositionAndTargetAndUpVec(VAdd(VGet(0.0f, 1500.0f, 500.f), this->vecCameraMove), VAdd(this->vecCameraTargetMove, VGet(0.0f, 0.0f, 0.f)), VGet(0.0f, 1.0f, 0.f));

    /* 中心に線を交差させる */
	DrawLine3D(VGet(0.0f, 0.0f, -10000.0f), VGet(0.0f, 0.0f, 10000.0f), GetColor(255, 0, 0));
	DrawLine3D(VGet(-10000.0f, 0.0f, 0.0f), VGet(10000.0f, 0.0f, 0.0f), GetColor(0, 255, 0));
	DrawLine3D(VGet(0.0f, -10000.0f, 0.0f), VGet(0.0f, 10000.0f, 0.0f), GetColor(0, 0, 255));

    /* カメラの注視点にも線を交差させる */
	DrawLine3D(VAdd(VGet(0.0f, 0.0f, -100.0f), this->vecCameraTargetMove), VAdd(VGet(0.0f, 0.0f, 100.0f), this->vecCameraTargetMove), GetColor(255, 0, 0));
	DrawLine3D(VAdd(VGet(-100.0f, 0.0f, 0.0f), this->vecCameraTargetMove), VAdd(VGet(100.0f, 0.0f, 0.0f), this->vecCameraTargetMove), GetColor(0, 255, 0));
	DrawLine3D(VAdd(VGet(0.0f, -100.0f, 0.0f), this->vecCameraTargetMove), VAdd(VGet(0.0f, 100.0f, 0.0f), this->vecCameraTargetMove), GetColor(0, 0, 255));

    ///* 0以外の座標に球を描写 */
    //for (const auto& mapData : vMapData_Chunks)
    //{
    //    if (mapData.iId != 0)
    //    {
    //        // 3D座標
    //        float x = static_cast<float>(mapData.stPosition.iX);
    //        float y = static_cast<float>(mapData.stPosition.iY);
    //        float z = static_cast<float>(mapData.stPosition.iZ);

    //        DrawSphere3D(VGet(x, y, z), 50.0f, 16, GetColor(0, 0, 255), GetColor(255, 0, 0), TRUE);
    //    }
    //}

    /* 0以外の座標に四角形を描写 */
    for (const auto& mapData : vMapData_Chunks)
    {
        /* IDが0以外(何かしらのブロックが存在している)状態であるか */
        if (mapData.iId != 0)
        {
            /* 中心座標を取得(int型で保存されているのでfloat型で取得) */
            float fX = static_cast<float>(mapData.stPosition.iX);
            float fY = static_cast<float>(mapData.stPosition.iY);
            float fZ = static_cast<float>(mapData.stPosition.iZ);

            /* 頂点データを取得 */
            // 中心座標を中心とした立方体の頂点座標を計算
            VERTEX3D aVertex[8];
			aVertex[0].pos  = VGet(fX + TILE_SIZE / 2, fY + TILE_SIZE / 2, fZ + TILE_SIZE / 2);
			aVertex[1].pos  = VGet(fX + TILE_SIZE / 2, fY + TILE_SIZE / 2, fZ - TILE_SIZE / 2);
			aVertex[2].pos  = VGet(fX + TILE_SIZE / 2, fY - TILE_SIZE / 2, fZ + TILE_SIZE / 2);
			aVertex[3].pos  = VGet(fX + TILE_SIZE / 2, fY - TILE_SIZE / 2, fZ - TILE_SIZE / 2);
            aVertex[4].pos  = VGet(fX - TILE_SIZE / 2, fY + TILE_SIZE / 2, fZ + TILE_SIZE / 2);
            aVertex[5].pos  = VGet(fX - TILE_SIZE / 2, fY + TILE_SIZE / 2, fZ - TILE_SIZE / 2);
            aVertex[6].pos  = VGet(fX - TILE_SIZE / 2, fY - TILE_SIZE / 2, fZ + TILE_SIZE / 2);
            aVertex[7].pos  = VGet(fX - TILE_SIZE / 2, fY - TILE_SIZE / 2, fZ - TILE_SIZE / 2);
			
            for (int i = 0; i < 8; ++i)
            {
                aVertex[i].norm = VGet(0.0f, 1.0f, 0.0f);
                aVertex[i].dif = GetColorU8(255, 255, 255, 255);
                aVertex[i].spc = GetColorU8(0, 0, 0, 0);
                aVertex[i].u = (i % 2 == 1) ? 1.0f : 0.0f;
                aVertex[i].v = (i >= 2) ? 1.0f : 0.0f;
                aVertex[i].su = 0.0f;
                aVertex[i].sv = 0.0f;
            }

            // インデックスデータ（10ポリゴン）
            unsigned short Index[30] = { 0, 1, 4, 4, 1, 5, 2, 0, 6, 6, 0, 4, 3, 1, 2, 2, 1, 0, 7, 5, 3, 3, 5, 1, 6, 4, 7, 7, 4, 5 };

            // 四角形（板ポリゴン）の描画
            DrawPolygonIndexed3D(aVertex, 8, Index, 10, iGrHandle, FALSE);



            //// 頂点データ
            //VERTEX3D Vertex[4];
            //Vertex[0].pos = VGet(fX - TILE_SIZE / 2, fY, fZ - TILE_SIZE / 2);
            //Vertex[1].pos = VGet(fX + TILE_SIZE / 2, fY, fZ - TILE_SIZE / 2);
            //Vertex[2].pos = VGet(fX - TILE_SIZE / 2, fY, fZ + TILE_SIZE / 2);
            //Vertex[3].pos = VGet(fX + TILE_SIZE / 2, fY, fZ + TILE_SIZE / 2);
            //for (int i = 0; i < 4; ++i)
            //{
            //    Vertex[i].norm = VGet(0.0f, 1.0f, 0.0f);
            //    Vertex[i].dif = GetColorU8(255, 255, 255, 255);
            //    Vertex[i].spc = GetColorU8(0, 0, 0, 0);
            //    Vertex[i].u = (i % 2 == 1) ? 1.0f : 0.0f;
            //    Vertex[i].v = (i >= 2) ? 1.0f : 0.0f;
            //    Vertex[i].su = 0.0f;
            //    Vertex[i].sv = 0.0f;
            //}

            //// インデックスデータ（2ポリゴン）
            //unsigned short Index[6] = { 3, 1, 2, 2, 1, 0 };

            //// 四角形（板ポリゴン）の描画
            //DrawPolygonIndexed3D(Vertex, 4, Index, 2, iGrHandle, FALSE);
        }
    }
}

