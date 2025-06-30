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
	for (int i = 0; i < 3; ++i)
	{
		DeleteGraph(this->aiGrHandle_SampleBlock[i]);
	}
}

// テクスチャ読み込み
void DataList_Texture::LoadTexture()
{
	/* ブロックのテクスチャの読み込み */
	this->aiGrHandle_SampleBlock[DIRECTION_TOP]		= LoadGraph("resource/Texture_Block/Sample_Top.png");		// 上面
	this->aiGrHandle_SampleBlock[DIRECTION_BOTTOM]	= LoadGraph("resource/Texture_Block/Sample_Bottom.png");	// 下面
	this->aiGrHandle_SampleBlock[DIRECTION_SIDE]	= LoadGraph("resource/Texture_Block/Sample_Side.png");		// 側面
}
