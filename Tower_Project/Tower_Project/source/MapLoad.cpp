/* 2025.06.19 駒沢風助 ファイル追加 */

#include "Scene_World.h"

#include "Building_MainBase.h"
#include "Building_EnemySpawner.h"
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
                    // 座標のIDを取得
					int iId = json["MapData"].at(iY).at(iX).at(iZ).get<int>();

                    pDataList_Object->aiMapData[iX][iY][iZ] = 0;

                    // オブジェクトのIDであるか確認
                    switch (iId)
                    {
                        // メインベース
                        case OBJECT_ID_MAIN_BASE:
                            {
                                // メイン拠点を追加
                                Building_MainBase* pAddBuilding = new Building_MainBase();
                                pDataList_Object->SetBuilding(pAddBuilding);
                                pAddBuilding->SetPosition({ iX, iY, iZ });               
								this->stSelectionPosition = { iX, iY, iZ }; // メインベースの位置を選択座標に設定
                            }
                            break;

                        // エネミースポナー
                        case OBJECT_ID_ENEMY_SPAWNER:
                            {
                                // エネミースポナーを追加
                                Building_EnemySpawner* pAddBuilding = new Building_EnemySpawner();
                                this->pDataList_Object->SetBuilding(pAddBuilding);
                                pAddBuilding->SetPosition({ iX, iY, iZ });
                            }
    					    break;

						// エネミー(通常歩行)
                        case OBJECT_ID_ENEMY_NORMAL_WALK:
                            {
                                // エネミーを追加
                                Character_Enemy_Normal_Walk* pAddCharacter = new Character_Enemy_Normal_Walk();
                                this->pDataList_Object->SetCharacter(pAddCharacter);
                                pAddCharacter->SetPosition({ iX, iY, iZ });
                            }
							break;

                        // 該当しないIDの場合、足場として扱う
                        default:
                            pDataList_Object->aiMapData[iX][iY][iZ] = iId;
							break;
                    }
                }
                catch (const std::exception& ErrorCode)
                {
                    // 範囲外アクセス時の処理
                    pDataList_Object->aiMapData[iX][iY][iZ] = 0;
                }
            }
        }
    }

    // オブジェクトの初期化
	pDataList_Object->Object_Initialization();
}