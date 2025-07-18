/* 2025.06.19 駒沢風助 ファイル追加 */

#include "Scene_World.h"

#include "Scene_Title.h"

#include "Building_MainBase.h"
#include "Building_EnemySpawner.h"
#include "Character_Enemy_Normal_Walk.h"

/* シーン"ゲームメイン"のマップ作成部分の定義 */
void Scene_World::MapCreate()
{
	// 建築物追加モードであるか確認
	if (this->bAddBuildingMode == true)
	{
		// 建築物追加関連の処理
		// 追加する建造物IDを+1(Wキー)
		if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_W])
		{
			// 建造物IDを加算
			this->iAddBuildingId += 1;
			if (this->iAddBuildingId >= OBJECT_ID_MAX - 1)
			{
				this->iAddBuildingId = OBJECT_ID_MAX - 1;
			}
		}

		// 追加する建造物IDを-1(Sキー)
		if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_S])
		{
			// 建造物IDを減算
			this->iAddBuildingId -= 1;
			if (this->iAddBuildingId <= OBJECT_ID_MINIMUM_VALUE)
			{
				this->iAddBuildingId = OBJECT_ID_MINIMUM_VALUE;
			}
		}

		// 建造物削除(Xキー)
		if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_X])
		{
			// 選択座標の建造物を削除
			// ※Y座標は無視して、X,Z座標のみで削除する
			for (auto it = this->pDataList_Object->paBuildingList.begin();
				it != this->pDataList_Object->paBuildingList.end(); )
			{
				if ((*it)->GetPosition().iX == this->stSelectionPosition.iX &&
					(*it)->GetPosition().iZ == this->stSelectionPosition.iZ)
				{
					// 該当オブジェクトを削除
					delete* it; // オブジェクトのメモリ解放
					it = this->pDataList_Object->paBuildingList.erase(it);

					// マップデータからも削除
					auto& MapBuilding = this->pDataList_Object->aMapBuildingData;
					for (auto building = MapBuilding.begin(); building != MapBuilding.end(); )
					{
						if (building->stPosition.iX == this->stSelectionPosition.iX &&
							building->stPosition.iZ == this->stSelectionPosition.iZ)
						{
							// 要素を削除し、戻り値で次の有効なイテレータを取得
							building = MapBuilding.erase(building);
						}
						else
						{
							++building;
						}
					}
				}
				else
				{
					++it;
				}
			}

			// エネミーも削除対象とする
			for (auto it = this->pDataList_Object->paCharacterList.begin();
				it != this->pDataList_Object->paCharacterList.end(); )
			{
				if ((*it)->GetPosition().iX == this->stSelectionPosition.iX &&
					(*it)->GetPosition().iZ == this->stSelectionPosition.iZ)
				{
					// 該当オブジェクトを削除
					delete* it; // オブジェクトのメモリ解放
					it = this->pDataList_Object->paCharacterList.erase(it);
				}
				else
				{
					++it;
				}
			}
		}

		// 建造物追加(Zキー)
		if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_Z])
		{
			// 選択座標のY座標で下側から建造物を追加
			for (int iY = 0; iY < MAP_SIZE_Y; iY++)
			{
				if (this->pDataList_Object->aiMapData[this->stSelectionPosition.iX][iY][this->stSelectionPosition.iZ] == 0)
				{
					// 選択座標に建造物を追加
					switch (this->iAddBuildingId)
					{
						case OBJECT_ID_MAIN_BASE:
							{
								// メインベースを追加
								Building_MainBase* pAddBuilding = new Building_MainBase();
								this->pDataList_Object->SetBuilding(pAddBuilding);
								pAddBuilding->SetPosition({ this->stSelectionPosition.iX, iY, this->stSelectionPosition.iZ });
							}
							break;

						case OBJECT_ID_ENEMY_SPAWNER:
							{
								// エネミースポナーを追加
								Building_EnemySpawner* pAddBuilding = new Building_EnemySpawner();
								this->pDataList_Object->SetBuilding(pAddBuilding);
								pAddBuilding->SetPosition({ this->stSelectionPosition.iX, iY, this->stSelectionPosition.iZ });
							}
							break;

						case OBJECT_ID_ENEMY_NORMAL_WALK:
							{
								// エネミー(通常歩行)を追加
								Character_Enemy_Normal_Walk* pAddCharacter = new Character_Enemy_Normal_Walk();
								this->pDataList_Object->SetCharacter(pAddCharacter);
								pAddCharacter->SetPosition({ this->stSelectionPosition.iX, iY, this->stSelectionPosition.iZ });
							}
							break;
						}
					break;
				}
			}

			// オブジェクトの初期化を行う
			this->pDataList_Object->Object_Initialization();
		}
	}
	else
	{
		// 建築物追加モードでない場合
		// 地形編集関連の処理
		// 追加するブロックIDを+1(Wキー)
		if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_W])
		{
			// ブロックIDを加算
			this->iAddBlockId += 1;
			if (this->iAddBlockId >= PLATFORM_ID_MAX - 1)
			{
				this->iAddBlockId = PLATFORM_ID_MAX - 1;
			}
		}

		// 追加するブロックIDを-1(Sキー)
		if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_S])
		{
			// ブロックIDを減算
			this->iAddBlockId -= 1;
			if (this->iAddBlockId <= PLATFORM_ID_MINIMUM_VALUE)
			{
				this->iAddBlockId = PLATFORM_ID_MINIMUM_VALUE;
			}
		}

		// ブロック削除(Xキー)
		if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_X])
		{
			// 選択座標のY座標で最も上の足場を削除
			for (int iY = MAP_SIZE_Y - 1; iY >= 0; iY--)
			{
				if (this->pDataList_Object->aiMapData[this->stSelectionPosition.iX][iY][this->stSelectionPosition.iZ] != 0)
				{
					this->pDataList_Object->aiMapData[this->stSelectionPosition.iX][iY][this->stSelectionPosition.iZ] = 0;
					break;
				}
			}
		}

		// ブロック追加(Zキー)
		if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_Z])
		{
			// 選択座標のY座標で下側から足場を追加
			for (int iY = 0; iY < MAP_SIZE_Y; iY++)
			{
				if (this->pDataList_Object->aiMapData[this->stSelectionPosition.iX][iY][this->stSelectionPosition.iZ] == 0)
				{
					// 足場を追加
					this->pDataList_Object->aiMapData[this->stSelectionPosition.iX][iY][this->stSelectionPosition.iZ] = this->iAddBlockId;
					break;
				}
			}
		}
	}

	// 建造粒追加モード切り替え(Cキー)
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_C])
	{
		// 現在のモードを反転
		// ※建築物追加モードであれば地形編集モードに、地形編集モードであれば建築物追加モードに切り替える
		this->bAddBuildingMode = !this->bAddBuildingMode;
	}

	// マップ制作モード終了(Escキー)
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_ESCAPE])
	{
		// シーン削除フラグを有効にする
		this->bDeleteFlg = true;

		/* シーン"タイトル"をセット */
		gpSceneServer->AddSceneReservation(new Scene_Title());
	}

	// マップ保存(Enterキー)
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_RETURN])
	{
		// マップを保存
		MapSave();
	}
}

/* シーン"ゲームメイン"のマップ作成部分の定義(描写部分) */
void Scene_World::DrawMapCreate()
{
	// 建築物追加モードであるか確認
	if (this->bAddBuildingMode == true)
	{
		// 建築物追加モードの場合
		// 建築物追加関連の描写を行う
		DrawFormatString(10, 480, GetColor(255, 255, 255), "建造物追加モード");
		DrawFormatString(10, 500, GetColor(255, 255, 255), "WS:追加する建造物のID変更, Z:建造物追加, X:建造物削除, C:地形編集追加モードに切り替え, Enter:マップ保存, Esc:タイトルへ戻る, Q:カメラモード切り替え");
		DrawFormatString(10, 520, GetColor(255, 255, 255), "追加する建造物のID: %d", this->iAddBuildingId);
		DrawFormatString(10, 540, GetColor(255, 255, 255), "1000:メインベース, 1001:エネミースポナー, 1002:エネミー(通常歩行)");
	}
	else
	{
		// 建築物追加モードでない場合
		// 地形編集関連の描写を行う
		DrawFormatString(10, 480, GetColor(255, 255, 255), "地形編集モード");
		DrawFormatString(10, 500, GetColor(255, 255, 255), "WS:追加するブロックのID変更, Z:ブロック追加, X:ブロック削除, C:建造物追加モードに切り替え, Enter:マップ保存, Esc:タイトルへ戻る, Q:カメラモード切り替え");
		DrawFormatString(10, 520, GetColor(255, 255, 255), "追加するブロックのID: %d", this->iAddBlockId);
		DrawFormatString(10, 540, GetColor(255, 255, 255), "1:土, 2:道, 3:石");
	}
}
