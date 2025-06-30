/* 2025.06.20 駒沢風助 ファイル作成 */

#pragma once
#include "AppFrame.h"

#include "ConstantDefine.h"

/* テクスチャ管理クラスの宣言 */

// テクスチャ管理クラス
class DataList_Texture : public DataListBase
{
	public:
		DataList_Texture();				// コンストラクタ
		virtual ~DataList_Texture();	// デストラクタ

		/* テクスチャ取得 */
		void	LoadTexture();			// テクスチャ読み込み

		/* グラフィックハンドル */
		// 0:上面, 1:下面, 2:側面 
		int		aiGrHandle_SampleBlock[3];


	protected:
};
