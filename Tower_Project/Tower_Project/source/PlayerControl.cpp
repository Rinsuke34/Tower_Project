/* 2025.07.13 駒沢風助 ファイル追加 */

#include "Scene_World.h"

#include "Building_Barricade.h"
#include "Building_Turret.h"

// 選択座標変更処理
void Scene_World::SelectPosition()
{
	// X+方向
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_RIGHT])
	{
		this->stSelectionPosition.iX += 1;
	}

	// X-方向
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_LEFT])
	{
		this->stSelectionPosition.iX -= 1;
	}

	// Z+方向
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_UP])
	{
		this->stSelectionPosition.iZ += 1;
	}

	// Z-方向
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_DOWN])
	{
		this->stSelectionPosition.iZ -= 1;
	}

	// カメラモード切り替え(Qキー)
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_Q])
	{
		// カメラモードを切り替える
		if (this->iCameraMode == CAMERA_MODE_FPS)
		{
			// トップビューに切り替え
			this->iCameraMode = CAMERA_MODE_TOP_VIEW;
		}
		else
		{
			// FPSカメラに切り替え
			this->iCameraMode = CAMERA_MODE_FPS;
		}
	}
}

// 建築物作成
void Scene_World::CreateBuilding()
{
	// コストインターバルを更新
	if (this->iAddCostInterval <= 0)
	{
		// コストを追加
		this->iHaveCost++;

		// コストインターバルをリセット
		this->iAddCostInterval = ADD_COST_INTERVAL;
	}
	else
	{
		// コストインターバルを減少
		this->iAddCostInterval--;
	}

	// コストがないなら処理を終了
	if (this->iHaveCost <= 0)	return;

	// バリケード設置(Zキー)
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_Z])
	{
		// コストを減少
		this->iHaveCost--;

		// 選択座標のY座標で下側にある足場の上に建造物を追加
		for (int iY = 0; iY < MAP_SIZE_Y; iY++)
		{
			if (this->pDataList_Object->aiMapData[this->stSelectionPosition.iX][iY][this->stSelectionPosition.iZ] == 0)
			{
				// バリケードを追加
				Building_Barricade* pAddBuilding = new Building_Barricade();
				pDataList_Object->SetBuilding(pAddBuilding);
				pAddBuilding->SetPosition({ this->stSelectionPosition.iX, iY, this->stSelectionPosition.iZ });

				pAddBuilding->Initialization();
				break;
			}
		}
	}

	// タレット設置(Xキー)
	if (gstKeyboardInputData.cgInput[INPUT_TRG][KEY_INPUT_X])
	{
		// コストを減少
		this->iHaveCost--;

		// 選択座標のY座標で下側にある足場の上に建造物を追加
		for (int iY = 0; iY < MAP_SIZE_Y; iY++)
		{
			if (this->pDataList_Object->aiMapData[this->stSelectionPosition.iX][iY][this->stSelectionPosition.iZ] == 0)
			{
				// タレットを追加
				Building_Turret* pAddBuilding = new Building_Turret();
				pDataList_Object->SetBuilding(pAddBuilding);
				pAddBuilding->SetPosition({ this->stSelectionPosition.iX, iY, this->stSelectionPosition.iZ });

				pAddBuilding->Initialization();
				break;
			}
		}
	}
}

// 状態の描写
void Scene_World::DrawStatus()
{
	DrawFormatString(10, 480, GetColor(255, 255, 255), "スコア: %d", this->iScore);
	DrawFormatString(10, 500, GetColor(255, 255, 255), "現在の所持コスト: %d", this->iHaveCost);
	DrawFormatString(10, 520, GetColor(255, 255, 255), "Z:バリケード設置, X:タレット設置");
	DrawFormatString(10, 540, GetColor(255, 255, 255), "カメラモード切り替え");
}
