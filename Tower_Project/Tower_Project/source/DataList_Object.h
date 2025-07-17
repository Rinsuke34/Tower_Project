/* 2025.07.01 駒沢風助 ファイル作成 */

#pragma once
#include "AppFrame.h"
#include <vector>
#include <map>
#include "ConstantDefine.h"

/* オブジェクト */
#include "Character_Base.h"
#include "Building_Base.h"

/* オブジェクト管理クラスの宣言 */

// オブジェクト管理クラス
class DataList_Object : public DataListBase
{
	public:
		DataList_Object();				// コンストラクタ
		virtual ~DataList_Object();		// デストラクタ

		void	Object_Initialization();	// リスト内オブジェクト初期化
		void	Object_Update();			// リスト内オブジェクト更新
		void	Object_Draw();				// リスト内オブジェクト描写
		void	Object_Delete();			// リスト内オブジェクト削除(削除フラグが立っているものを削除)
		void	Object_Reset();				// リスト内オブジェクトリセット

		/* データ設定 */
		void	SetCharacter(Character_Base* pCharacter)	{	this->paCharacterList.push_back(pCharacter);	};	// キャラクター追加
		void	SetBuilding(Building_Base* pBuilding)		{	this->paBuildingList.push_back(pBuilding);		};	// 建造物追加

		/* リスト */
		std::vector<Character_Base*>	paCharacterList;		// キャラクター(エネミー)リスト
		std::vector<Building_Base*>		paBuildingList;			// 建造物リスト

		/* マップ情報 */
		int							aiMapData[MAP_SIZE_X][MAP_SIZE_Y][MAP_SIZE_Z];	// マップデータ(足場)(3次元配列)
		std::vector<MAP_DATA>		aMapBuildingData;								// マップデータ(建造物)(ID/情報)
		bool						bMainBaseBleakFlg;								// メイン拠点破壊フラグ
};
