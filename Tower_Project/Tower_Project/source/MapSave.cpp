/* 2025.06.19 駒沢風助 ファイル追加 */

#include "Scene_World.h"

/* シーン"ゲームメイン"のマップセーブ部分の定義 */
void Scene_World::MapSave()
{
    // 現在のマップデータを保存する(建造物のIDと座標を書き加えるので)
    int aiSaveMapData[MAP_SIZE_X][MAP_SIZE_Y][MAP_SIZE_Z];

    for (int iX = 0; iX < MAP_SIZE_X; iX++)
    {
        for (int iY = 0; iY < MAP_SIZE_Y; iY++)
        {
            for (int iZ = 0; iZ < MAP_SIZE_Z; iZ++)
            {
                aiSaveMapData[iX][iY][iZ] = pDataList_Object->aiMapData[iX][iY][iZ];
            }
        }
    }

    // オブジェクトの座標をマップデータに上書きする
	for (const auto& object : pDataList_Object->aMapBuildingData)
	{
        // オブジェクトのIDを座標に上書き
		aiSaveMapData[object.second.stPosition.iX][object.second.stPosition.iY][object.second.stPosition.iZ] = object.first;
	}

    /* 保存先のパス指定 */
    std::string stPath = "resource/MapData/MapData.json";
    std::ofstream File(stPath);

    /* JSONオブジェクトを用意 */
    nlohmann::json json;

    // MapData[y][x][z] の3次元配列を保存
    for (int iY = 0; iY < MAP_SIZE_Y; iY++)
    {
        nlohmann::json layerX;

        for (int iX = 0; iX < MAP_SIZE_X; iX++)
        {
            nlohmann::json rowZ;

            for (int iZ = 0; iZ < MAP_SIZE_Z; iZ++)
            {
                int iId = aiSaveMapData[iX][iY][iZ];
                rowZ.push_back(iId);
            }

            layerX.push_back(rowZ);
        }

        json["MapData"].push_back(layerX);
    }

    /* ファイルに書き出し */
    File << std::setw(4) << json << std::endl;
}