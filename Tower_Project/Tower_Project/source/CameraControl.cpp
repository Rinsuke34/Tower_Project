/* 2025.07.13 駒沢風助 ファイル追加 */

#include "Scene_World.h"

// カメラ制御
void Scene_World::CameraControl()
{
	switch (this->iCameraMode)
	{
		// トップビュー
		case CAMERA_MODE_TOP_VIEW:
			Cmaera_TopView();
			break;

		// FPSカメラ
		case CAMERA_MODE_FPS:
			Camera_FPS();
			break;
	}
}

// トップビューカメラ
void Scene_World::Cmaera_TopView()
{
	/* 選択中の座標をベースにカメラを設定 */
	// カメラ注視点
	this->vecCameraTargetPos.x = this->stSelectionPosition.iX * TILE_SIZE_PIXEL_X + TILE_SIZE_PIXEL_X / 2;
	this->vecCameraTargetPos.y = this->stSelectionPosition.iY * TILE_SIZE_PIXEL_Y + TILE_SIZE_PIXEL_Y / 2;
	this->vecCameraTargetPos.z = this->stSelectionPosition.iZ * TILE_SIZE_PIXEL_Z + TILE_SIZE_PIXEL_Z / 2;

	// カメラ位置
	this->vecCameraPos.x = this->vecCameraTargetPos.x;
	this->vecCameraPos.y = this->vecCameraTargetPos.y + 500;
	this->vecCameraPos.z = this->vecCameraTargetPos.z - 250;
}

void Scene_World::Camera_FPS()
{
	/* 前後左右の入力で位置を変更 */
	const float	fSpeed = 10.0f;				// 移動速度
	VECTOR		vecMove = VGet(0, 0, 0);	// 移動量

	float angle = this->fCameraAngleX;

	// 前進
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_W])
	{
		vecMove.x += -sinf(angle) * fSpeed;
		vecMove.z += +cosf(angle) * fSpeed;
	}
	// 後退
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_S])
	{
		vecMove.x -= -sinf(angle) * fSpeed;
		vecMove.z -= +cosf(angle) * fSpeed;
	}
	// 左移動
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_A])
	{
		vecMove.x += -cosf(angle) * fSpeed;
		vecMove.z += -sinf(angle) * fSpeed;
	}
	// 右移動
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_D])
	{
		vecMove.x += +cosf(angle) * fSpeed;
		vecMove.z += +sinf(angle) * fSpeed;
	}
	// 上昇
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_SPACE])
	{
		this->vecCameraPos.y += fSpeed;
	}
	// 下降
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_LSHIFT])
	{
		this->vecCameraPos.y -= fSpeed;
	}

	/* 移動量分カメラ位置を移動 */
	this->vecCameraPos.x += vecMove.x;
	this->vecCameraPos.z += vecMove.z;

	/* カメラ注視点の算出 */
	// マウス移動量
	this->fCameraAngleX -= gstKeyboardInputData.iMouseMoveX * 0.01f;	// X軸回転量
	this->fCameraAngleY -= gstKeyboardInputData.iMouseMoveY * 0.01f;	// Y軸回転量

	// Y軸回転制限
	float fLimit = DX_PI_F / 2 - 0.01f;	// 約90度
	if (this->fCameraAngleY > fLimit) { this->fCameraAngleY = fLimit; }
	if (this->fCameraAngleY < -fLimit) { this->fCameraAngleY = -fLimit; }

	// カメラ注視点の設定
	const float fScale = 200.f;	// カメラ注視点の距離
	this->vecCameraTargetPos.x = fScale * cosf(this->fCameraAngleY) * -sinf(this->fCameraAngleX) + this->vecCameraPos.x;
	this->vecCameraTargetPos.y = fScale * sinf(this->fCameraAngleY) + this->vecCameraPos.y;
	this->vecCameraTargetPos.z = fScale * cosf(this->fCameraAngleY) * cosf(this->fCameraAngleX) + this->vecCameraPos.z;
}