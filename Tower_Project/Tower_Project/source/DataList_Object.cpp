/* 2025.07.01 駒沢風助 ファイル作成 */

#include "DataList_Object.h"

/* オブジェクト管理クラスの定義 */
// コンストラクタ
DataList_Object::DataList_Object() : DataListBase("DataList_Object")
{
	/* 初期化 */
	this->paBuildingList.clear();	// 建造物リスト初期化
	this->paCharacterList.clear();	// キャラクターリスト初期化
}

// デストラクタ
DataList_Object::~DataList_Object()
{
	/* メモリ開放 */
	for (auto pCharacter : this->paCharacterList)	{	delete pCharacter;	}	// キャラクターのメモリ開放
	for (auto pBuilding : this->paBuildingList)		{	delete pBuilding;	}	// 建造物のメモリ開放
}

// リスト内オブジェクト初期化
void DataList_Object::Object_Initialization()
{
	for (auto pCharacter : this->paCharacterList)	{	pCharacter->Initialization();	}	// キャラクター初期化
	for (auto pBuilding : this->paBuildingList)		{	pBuilding->Initialization();	}	// 建造物初期化
}

// リスト内オブジェクト更新
void DataList_Object::Object_Update()
{
	for (auto pCharacter : this->paCharacterList)	{	pCharacter->Update();	}	// キャラクター更新
	for (auto pBuilding : this->paBuildingList)		{	pBuilding->Update();	}	// 建造物更新
}

// リスト内オブジェクト描写
void DataList_Object::Object_Draw()
{
	for (auto pCharacter : this->paCharacterList)	{ pCharacter->Draw();	}	// キャラクター描写
	for (auto pBuilding : this->paBuildingList)		{ pBuilding->Draw();	}	// 建造物描写
}

// リスト内オブジェクト削除(削除フラグが立っているものを削除)
void DataList_Object::Object_Delete()
{
	/* キャラクターリスト内の削除フラグが有効なキャラクターを削除 */
	this->paCharacterList.erase(std::remove_if(this->paCharacterList.begin(), this->paCharacterList.end(), [](Character_Base* pCharacter)
	{
		/* 削除フラグが有効であるか確認　*/
		if (pCharacter->bGetDeleteFlg() == true)
		{
			// 有効である場合
			delete pCharacter;
			return true;
		}
		else
		{
			// 無効である場合
			return false;
		}
	}), this->paCharacterList.end());

	/* 建造物リスト内の削除フラグが有効な建造物を削除 */
	this->paBuildingList.erase(std::remove_if(this->paBuildingList.begin(), this->paBuildingList.end(), [](Building_Base* pBuilding)
	{
		/* 削除フラグが有効であるか確認　*/
		if (pBuilding->bGetDeleteFlg() == true)
		{
			// 有効である場合
			delete pBuilding;
			return true;
		}
		else
		{
			// 無効である場合
			return false;
		}
	}), this->paBuildingList.end());
}

// リスト内オブジェクトリセット
void DataList_Object::Object_Reset()
{
	for (auto pCharacter : this->paCharacterList)	{	pCharacter->Reset();	}	// キャラクターリセット
	for (auto pBuilding : this->paBuildingList)		{	pBuilding->Reset();		}	// 建造物リセット
}
