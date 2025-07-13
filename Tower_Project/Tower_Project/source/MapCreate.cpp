/* 2025.06.19 駒沢風助 ファイル追加 */

#include "Scene_World.h"

/* シーン"ゲームメイン"のマップ作成部分の定義 */
void Scene_World::MapCreate()
{
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
		if (this->iAddBlockId <= 0)
		{
			this->iAddBlockId = 0;
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
	// 現在の追加ブロックIDを表示
	DrawFormatString(10, 500, GetColor(255, 255, 255), "WS:追加するブロックのID変更, Z:ブロック追加, X:ブロック削除, Enter:マップ保存");
	DrawFormatString(10, 520, GetColor(255, 255, 255), "追加するブロックのID: %d", this->iAddBlockId);
	DrawFormatString(10, 540, GetColor(255, 255, 255), "0:無し, 1:土, 2:道, 3:石");
}
