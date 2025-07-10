/* 2025.06.19 駒沢風助 ファイル追加 */

#include "Scene_World.h"

#include "Building_MainBase.h"
#include "Character_Enemy_Normal_Walk.h"

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
                    pDataList_Object->aiMapData[iX][iY][iZ] = json["MapData"].at(iY).at(iX).at(iZ);
                }
                catch (const std::exception& ErrorCode)
                {
                    // 範囲外アクセス時の処理
                    pDataList_Object->aiMapData[iX][iY][iZ] = 0;
                }
            }
        }
    }

    // メイン拠点を追加
	Building_MainBase* pAddBuilding = new Building_MainBase();
	pDataList_Object->SetBuilding(pAddBuilding);
	pAddBuilding->SetPosition({ 16, 1, 16 });

	// エネミーを追加
	Character_Enemy_Normal_Walk* pAddCharacter = new Character_Enemy_Normal_Walk();
	pDataList_Object->SetCharacter(pAddCharacter);
	pAddCharacter->SetPosition({ 64, 0, 64 });

    // オブジェクトの初期化
	pDataList_Object->Object_Initialization();
}