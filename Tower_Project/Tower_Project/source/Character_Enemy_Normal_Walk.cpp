/* 2025.07.01 駒沢風助 ファイル作成 */

#include "Character_Enemy_Normal_Walk.h"
#include <vector>

#include "DataList_Object.h"

#include "StructDefine.h"
#include "ConstantDefine.h"

/* エネミー(歩行/通常)クラスの定義 */
// コンストラクタ
Character_Enemy_Normal_Walk::Character_Enemy_Normal_Walk() : Character_Base()
{

}

// デストラクタ
Character_Enemy_Normal_Walk::~Character_Enemy_Normal_Walk()
{

}

// 初期化
void Character_Enemy_Normal_Walk::Initialization()
{

}

// 更新
void Character_Enemy_Normal_Walk::Update()
{
	// 現在の座標からマップ上の座標を取得
	POSITION_3D_MAP stMapPosition = { 0, 0, 0 };
	stMapPosition.iX = static_cast<int>(this->vecPosition.x / TILE_SIZE_PIXEL_X);	// X座標を設定
	stMapPosition.iY = static_cast<int>(this->vecPosition.y / TILE_SIZE_PIXEL_Y);	// Y座標を設定
	stMapPosition.iZ = static_cast<int>(this->vecPosition.z / TILE_SIZE_PIXEL_Z);	// Z座標を設定

	// メイン拠点(破壊対象)の座標を取得
	POSITION_3D_MAP stMainBasePosition = { 0, 0, 0 };
	stMainBasePosition = static_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->aMapBuildingData[1000].stPosition;

	/* A*アルゴリズムを用いて、現在の座標からメイン拠点までの最短経路を取得 */
	// A*アルゴリズムの評価値リストを作成
	ASTAR_EVALUATION_LIST stAStarEvaluationList[MAP_SIZE_X][MAP_SIZE_Y][MAP_SIZE_Z];
	// A*アルゴリズムの評価値リストを初期化
	for (int i = 0; i < MAP_SIZE_X; i++) {
		for (int j = 0; j < MAP_SIZE_Y; j++) {
			for (int k = 0; k < MAP_SIZE_Z; k++) {
				stAStarEvaluationList[i][j][k].iG		= 0;		// 開始点からの移動コスト
				stAStarEvaluationList[i][j][k].iH		= 0;		// ゴールまでの推定コスト
				stAStarEvaluationList[i][j][k].iF		= 0;		// 総コスト
				stAStarEvaluationList[i][j][k].bOpen	= false;	// オープンリストに存在するか
				stAStarEvaluationList[i][j][k].bClose	= false;	// クローズリストに存在するか
			}
		}
	}

	// A*アルゴリズムの開始点を設定
	stAStarEvaluationList[stMapPosition.iX][stMapPosition.iY][stMapPosition.iZ].iG		= 0;	// 開始点からの移動コストを0に設定
	stAStarEvaluationList[stMapPosition.iX][stMapPosition.iY][stMapPosition.iZ].iH		= 0;	// ゴールまでの推定コストを0に設定
	stAStarEvaluationList[stMapPosition.iX][stMapPosition.iY][stMapPosition.iZ].iF		= 0;	// 総コストを0に設定
	stAStarEvaluationList[stMapPosition.iX][stMapPosition.iY][stMapPosition.iZ].bOpen	= true;	// オープンリストに存在するように設定

	// A*アルゴリズムのオープンリストを探索
	for (int x = 0; x < MAP_SIZE_X; x++)
	{
		for (int y = 0; y < MAP_SIZE_Y; y++)
		{
			for (int z = 0; z < MAP_SIZE_Z; z++)
			{
				// オープンリストに存在する座標であるなら確認を開始する
				if (stAStarEvaluationList[x][y][z].bOpen == true)
				{
					// 現在の座標から隣接する座標を取得
					for (int dx = -1; dx <= 1; dx++) {
						for (int dz = -1; dz <= 1; dz++) {
							if (dx == 0 && dz == 0) continue; // 現在の座標はスキップ
							int nx = i + dx;
							int ny = j + dy;
							int nz = k; // Z座標は固定
							// マップの範囲内かチェック
							if (nx >= 0 && nx < MAP_SIZE_X && ny >= 0 && ny < MAP_SIZE_Y && nz >= 0 && nz < MAP_SIZE_Z) {
								// 隣接座標の評価値を更新
								stAStarEvaluationList[nx][ny][nz].iG = stAStarEvaluationList[i][j][k].iG + 1;
								stAStarEvaluationList[nx][ny][nz].iH = abs(nx - stMainBasePosition.iX) + abs(ny - stMainBasePosition.iY);	// マンハッタン距離(XとZの差の絶対値を加算した値)
								stAStarEvaluationList[nx][ny][nz].iF = stAStarEvaluationList[nx][ny][nz].iG + stAStarEvaluationList[nx][ny][nz].iH;
								stAStarEvaluationList[nx][ny][nz].bOpen = true;
							}
						}
					}
					// オープンリストから現在の座標を削除し、クローズリストに追加
					stAStarEvaluationList[i][j][k].bOpen = false;
					stAStarEvaluationList[i][j][k].bClose = true;
				}
			}
		}
	}
}

// 描写
void Character_Enemy_Normal_Walk::Draw()
{

}

// リセット処理
void Character_Enemy_Normal_Walk::Reset()
{

}
