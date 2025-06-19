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

    iGrHandle = LoadGraph("resource/test.png");;
}

// 計算
void Scene_World::Process()
{

}

// 描画
void Scene_World::Draw()
{
    /* カメラ設定 */
    SetCameraPositionAndTargetAndUpVec(VGet(1000.0f, 1500.0f, 1000.f), VGet(0.0f, 0.0f, 0.f), VGet(0.0f, 1.0f, 0.f));

    /* 中心に線を交差させる */
	DrawLine3D(VGet(0.0f, 0.0f, -10000.0f), VGet(0.0f, 0.0f, 10000.0f), GetColor(255, 0, 0));
	DrawLine3D(VGet(-10000.0f, 0.0f, 0.0f), VGet(10000.0f, 0.0f, 0.0f), GetColor(0, 255, 0));
	DrawLine3D(VGet(0.0f, -10000.0f, 0.0f), VGet(0.0f, 10000.0f, 0.0f), GetColor(0, 0, 255));

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
        if (mapData.iId != 0)
        {
            // 3D座標
            float x = static_cast<float>(mapData.stPosition.iX);
            float y = static_cast<float>(mapData.stPosition.iY);
            float z = static_cast<float>(mapData.stPosition.iZ);

            // 四角形のサイズ
            float size = 100.0f;

            // 頂点データ
            VERTEX3D Vertex[4];
            Vertex[0].pos = VGet(x - size / 2, y, z - size / 2);
            Vertex[1].pos = VGet(x + size / 2, y, z - size / 2);
            Vertex[2].pos = VGet(x - size / 2, y, z + size / 2);
            Vertex[3].pos = VGet(x + size / 2, y, z + size / 2);
            for (int i = 0; i < 4; ++i)
            {
                Vertex[i].norm = VGet(0.0f, 1.0f, 0.0f);
                Vertex[i].dif = GetColorU8(255, 255, 255, 255);
                Vertex[i].spc = GetColorU8(0, 0, 0, 0);
                Vertex[i].u = (i % 2 == 1) ? 1.0f : 0.0f;
                Vertex[i].v = (i >= 2) ? 1.0f : 0.0f;
                Vertex[i].su = 0.0f;
                Vertex[i].sv = 0.0f;
            }

            // インデックスデータ（2ポリゴン）
            unsigned short Index[6] = { 3, 1, 2, 2, 1, 0 };

            // 四角形（板ポリゴン）の描画
            DrawPolygonIndexed3D(Vertex, 4, Index, 2, iGrHandle, FALSE);
            //DrawPolygonIndexed3D(Vertex, 4, Index, 2, DX_NONE_GRAPH, FALSE);
        }
    }
}

