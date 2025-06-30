/* 2025.06.19 駒沢風助 ファイル追加 */

#include "Scene_World.h"

/* シーン"ゲームメイン"のマップロード部分の定義 */
void Scene_World::MapLoad()
{
	/* 読み込みたいマップデータのパス指定 */
	std::string stPath = "resource/MapData/MapData.json";
	std::ifstream File(stPath);

	/* jsonファイル読み込み */
	nlohmann::json json;
	File >> json;

	/* マップデータ読み込み */
    for (int iX = 0; iX < MAP_SIZE_X; iX++)
    {
        for (int iY = 0; iY < MAP_SIZE_Y; iY++)
        {
            for (int iZ = 0; iZ < MAP_SIZE_Z; iZ++)
            {
				/* 3次元配列の値を設定 */
                try
                {
                    this->aiMapData[iX][iY][iZ] = json["MapData"].at(iY).at(iX).at(iZ);
                }
                catch (const std::exception& e)
                {
                    // 範囲外アクセス時の処理
                    this->aiMapData[iX][iY][iZ] = 0;
                }
            }
        }
    }
}