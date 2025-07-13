/* 2025.06.20 駒沢風助 ファイル作成 */

#include "DataList_Texture.h"

/* テクスチャ管理クラスの定義 */
// コンストラクタ
DataList_Texture::DataList_Texture() : DataListBase("DataList_Texture")
{
	/* テクスチャ読み込み */
	LoadTexture();
}

// デストラクタ
DataList_Texture::~DataList_Texture()
{
	/* グラフィックハンドルの削除 */
	for (int i = 0; i < PLATFORM_ID_MAX; ++i)
	{
		for (int j = 0; j < DIRECTION_MAX; ++j)
		{
			DeleteGraph(this->aiGrHandle_Block[i][j]);
		}
	}
}

// テクスチャ読み込み
void DataList_Texture::LoadTexture()
{
	/* ブロックのテクスチャの読み込み */
	// 土(ダート)
	this->aiGrHandle_Block[PLATFORM_ID_DIRT][DIRECTION_TOP]		= LoadGraph("resource/Texture_Block/Dirt_Top.png");
	this->aiGrHandle_Block[PLATFORM_ID_DIRT][DIRECTION_BOTTOM]	= LoadGraph("resource/Texture_Block/Dirt_Bottom.png");
	this->aiGrHandle_Block[PLATFORM_ID_DIRT][DIRECTION_SIDE]	= LoadGraph("resource/Texture_Block/Dirt_Side.png");

	// 道路
	this->aiGrHandle_Block[PLATFORM_ID_ROAD][DIRECTION_TOP]		= LoadGraph("resource/Texture_Block/Road_Top.png");
	this->aiGrHandle_Block[PLATFORM_ID_ROAD][DIRECTION_BOTTOM]	= LoadGraph("resource/Texture_Block/Road_Bottom.png");
	this->aiGrHandle_Block[PLATFORM_ID_ROAD][DIRECTION_SIDE]	= LoadGraph("resource/Texture_Block/Road_Side.png");

	// 石
	this->aiGrHandle_Block[PLATFORM_ID_STONE][DIRECTION_TOP]	= LoadGraph("resource/Texture_Block/Stone_Top.png");
	this->aiGrHandle_Block[PLATFORM_ID_STONE][DIRECTION_BOTTOM]	= LoadGraph("resource/Texture_Block/Stone_Bottom.png");
	this->aiGrHandle_Block[PLATFORM_ID_STONE][DIRECTION_SIDE]	= LoadGraph("resource/Texture_Block/Stone_Side.png");
}
