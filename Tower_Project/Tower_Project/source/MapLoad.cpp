/* 2025.06.19 駒沢風助 ファイル追加 */

#include "Scene_World.h"

/* シーン"ゲームメイン"のマップロード部分の定義 */
void Scene_World::MapLoad()
{
	/* 読み込みたいマップデータのパス指定 */
	std::string stPath = "resource/MapData/Map.json";
	std::ifstream File(stPath);

	/* jsonファイル読み込み */
	nlohmann::json json;
	File >> json;

	/* チャンクデータ読み込み */
	for (auto& chunk : json["Chunks"])
	{
        /* チャンクの中心座標取得 */
        int chunkX = chunk["ChunkPosition"]["X"];
        int chunkZ = chunk["ChunkPosition"]["Z"];

        /* チャンクの対象IDを取得 */
        // "ID"は3次元配列 [Z][Y][X]
        const auto& idArray = chunk["ID"];
        int zSize = idArray.size();
        for (int z = 0; z < zSize; ++z)
        {
            const auto& yArray = idArray[z];
            int ySize = yArray.size();
            for (int y = 0; y < ySize; ++y)
            {
                const auto& xArray = yArray[y];
                int xSize = xArray.size();
                for (int x = 0; x < xSize; ++x)
                {
                    int id = xArray[x];
                    MAP_DATA mapData;
                    // X軸とZ軸を正しく反映
                    mapData.stPosition.iX = chunkX + (x - (CHUNK_SIZE / 2)) * TILE_SIZE;
                    mapData.stPosition.iY = y * TILE_SIZE;
                    mapData.stPosition.iZ = chunkZ + (z - (CHUNK_SIZE / 2)) * TILE_SIZE;

                    mapData.iId = id;
                    vMapData_Chunks.push_back(mapData);
                }
            }
        }
	}
}