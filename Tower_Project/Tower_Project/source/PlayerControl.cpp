/* 2025.07.13 駒沢風助 ファイル追加 */

#include "Scene_World.h"

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
}
