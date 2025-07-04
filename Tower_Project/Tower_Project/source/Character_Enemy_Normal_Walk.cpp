/* 2025.07.01 駒沢風助 ファイル作成 */

#include "Character_Enemy_Normal_Walk.h"
#include <vector>

#include "DataList_Object.h"

#include "StructDefine.h"
#include "ConstantDefine.h"

Character_Enemy_Normal_Walk::Character_Enemy_Normal_Walk() : Character_Base()  
{
    // 移動ルートをA*アルゴリズムで計算
    // ※X軸とZ軸の二次元で判断する
	
    // スタート座標を設定
	this->vecPosition = VGet(64, 0, 64); // 初期位置（ワールド座標）

    // スタート座標をマップ座標に変換
    POSITION_3D_MAP stStart = {
        static_cast<int>(this->vecPosition.x / TILE_SIZE_PIXEL_X),
        static_cast<int>(this->vecPosition.y / TILE_SIZE_PIXEL_Y),
        static_cast<int>(this->vecPosition.z / TILE_SIZE_PIXEL_Z)
    };

    // ゴール（拠点）の座標を取得
    DataList_Object* pObj = static_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"));
    if (!pObj) return;
    auto it = pObj->aMapBuildingData.find(1000);
    if (it == pObj->aMapBuildingData.end()) return;
    POSITION_3D_MAP stGoal = it->second.stPosition;

    // マップデータ(足場)(3次元配列)の取得
    auto& aiMapData = pObj->aiMapData;

    // 評価値リストを作成
	std::vector<ASTAR_EVALUATION_LIST> stAStarEvaluationList;

    // スタート地点の情報を追加
	ASTAR_EVALUATION_LIST stAddStart;
    stAddStart.iId      = 0;
	stAddStart.iG       = 0;
    stAddStart.iH       = abs(stStart.iX - stGoal.iX) + abs(stStart.iZ - stGoal.iZ);  // ゴールまでのコストはマンハッタン距離で算出(Y軸は考慮しない)
    stAddStart.iF       = stAddStart.iG + stAddStart.iH;
    stAddStart.bOpen    = true;
    stAddStart.bClose   = false;
    stAddStart.stParent = {-1, -1, -1};
	stAStarEvaluationList.push_back(stAddStart);

    // 確認で使用する変数定義
	bool            bGoalFoundFlg       = false;            // ゴール到達フラグ
	POSITION_3D_MAP stCurrentPosition   = { -1, -1, -1 };   // 現在探索中の座標

    // A*アルゴリズムを用いた経路探索処理
    while (true)
    {
		// 評価値リスト内のオープンリストからF値(類型コストが最小のノード)を探索
		int     iMinF       = INT_MAX;  // 最小F値
		bool    bFoundFlg   = false;    // 最小F値ノードが見つかったかのフラグ

        for (auto& node : stAStarEvaluationList)
        {
            // オープンリスト内かつF値が最小であるか
            if (node.bOpen && node.iF < iMinF)
            {
				// F値が最小のノードである場合
				bFoundFlg           = true;     // 最小F値ノードが見つかったフラグを立てる
				iMinF               = node.iF;  // 最小F値を更新
				stCurrentPosition   = { node.stParent.iX, node.stParent.iY, node.stParent.iZ }; // 現在探索中の座標を更新
			}
        }

        // 最小F値ノードが見つからなかった場合、探索失敗とする
        if (!bFoundFlg)
        {
            break;
        }

        // ゴールに到達した場合、探索成功とする
        if (stCurrentPosition.iX == stGoal.iX && stCurrentPosition.iZ == stGoal.iZ)
        {
            bGoalFoundFlg = true;
			break;
        }


        // 現在ノードをクローズリストへ移動
        auto& currentNode = stAStarEvaluationList[ASTAR_INDEX(stCurrent.iX, stCurrent.iY, stCurrent.iZ)];
        currentNode.bOpen = false;
        currentNode.bClose = true;

        // 隣接（X/Z方向）のノードを探索
        for (int iX = -1; iX <= 1; iX++) {
            for (int iZ = -1; iZ <= 1; iZ++) {
                if ((iX == 0 && iZ == 0) || (iX != 0 && iZ != 0)) continue; // X/Zのみに移動可

                int iSearchX = stCurrent.iX + iX;
                int iSearchY = stCurrent.iY;
                int iSearchZ = stCurrent.iZ;

                // 範囲外ならスキップ
                if (iSearchX < 0 || iSearchX >= MAP_SIZE_X || iSearchZ < 0 || iSearchZ >= MAP_SIZE_Z)
                    continue;

                int iNewY = iSearchY;
                int iMoveCost = 1;

                if (aiMapData[iSearchX][iSearchY][iSearchZ] != 0) {
                    // 足場がある → 上にスペースがあるか確認
                    if (iSearchY + 1 < MAP_SIZE_Y && aiMapData[iSearchX][iSearchY + 1][iSearchZ] == 0) {
                        iNewY = iSearchY + 1; // 上に移動
                        iMoveCost = 2;       // 移動コスト2倍
                    }
                    else {
                        continue; // 上にも詰まっている → 移動不可
                    }
                }
                else {
                    // 足場がない → 下に足場があるか確認
                    int y = iSearchY - 1;
                    bool bFound = false;
                    while (y >= 0) {
                        if (aiMapData[iSearchX][y][iSearchZ] != 0) {
                            iNewY = y + 1; // 足場の上に移動
                            bFound = true;
                            break;
                        }
                        y--;
                    }
                    if (!bFound) continue; // 足場が見つからない → 移動不可
                }

                // 新Yが範囲外ならスキップ
                if (iNewY < 0 || iNewY >= MAP_SIZE_Y)
                    continue;

                auto& nextNode = stAStarEvaluationList[ASTAR_INDEX(iSearchX, iNewY, iSearchZ)];

                if (nextNode.bClose)
                    continue; // すでに探索済み

                // G, H, Fの再計算
                int iG = currentNode.iG + iMoveCost;
                int iH = abs(iSearchX - stGoal.iX) + abs(iNewY - stGoal.iY) + abs(iSearchZ - stGoal.iZ);
                int iF = iG + iH;

                // より良い経路なら更新
                if (nextNode.bOpen) {
                    if (iF < nextNode.iF) {
                        nextNode.iG = iG;
                        nextNode.iH = iH;
                        nextNode.iF = iF;
                        nextNode.stParent = stCurrent;
                    }
                }
                else {
                    // 初めての訪問 → オープンリストに追加
                    nextNode.iG = iG;
                    nextNode.iH = iH;
                    nextNode.iF = iF;
                    nextNode.bOpen = true;
                    nextNode.stParent = stCurrent;
                }
            }
        }
    }

    // 探索成功なら経路を復元
    if (bGoalFound) {
        POSITION_3D_MAP stTrace = stGoal;
        while (!(stTrace.iX == stStart.iX && stTrace.iY == stStart.iY && stTrace.iZ == stStart.iZ)) {
            vPath.push_back(stTrace);
            stTrace = stAStarEvaluationList[ASTAR_INDEX(stTrace.iX, stTrace.iY, stTrace.iZ)].stParent;
        }
        vPath.push_back(stStart); // 始点も追加
        std::reverse(vPath.begin(), vPath.end()); // 順路を逆転
    }
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
	// 移動ルートが設定されていない場合は何もしない
	if (vPath.empty()) {
		return;
	}

	// 現在の位置を取得
	POSITION_3D_MAP currentPos = {
		static_cast<int>(this->vecPosition.x / TILE_SIZE_PIXEL_X),
		static_cast<int>(this->vecPosition.y / TILE_SIZE_PIXEL_Y),
		static_cast<int>(this->vecPosition.z / TILE_SIZE_PIXEL_Z)
	};

	// 次の目標位置を取得
	POSITION_3D_MAP nextPos = vPath.front();
	// 目標位置に到達した場合、次の位置へ移動
	if (currentPos.iX == nextPos.iX && currentPos.iY == nextPos.iY && currentPos.iZ == nextPos.iZ) {
		vPath.erase(vPath.begin()); // 目標位置を削除
		if (vPath.empty()) {
			return; // 目標位置がなくなった場合は終了
		}
		nextPos = vPath.front(); // 次の目標位置を取得
	}
	// 目標位置までの移動
	float targetX = nextPos.iX * TILE_SIZE_PIXEL_X;
	float targetY = nextPos.iY * TILE_SIZE_PIXEL_Y;
	float targetZ = nextPos.iZ * TILE_SIZE_PIXEL_Z;
	// 目標位置に向かって移動
	this->vecPosition.x += (targetX - this->vecPosition.x) * 0.1f; // 10%の速さで目標位置に向かう
	this->vecPosition.y += (targetY - this->vecPosition.y) * 0.1f; // 10%の速さで目標位置に向かう
	this->vecPosition.z += (targetZ - this->vecPosition.z) * 0.1f; // 10%の速さで目標位置に向かう
	// 位置が目標位置に近づいたら、位置を目標位置に設定
	if (abs(this->vecPosition.x - targetX) < 0.1f) {
		this->vecPosition.x = targetX;
	}
	if (abs(this->vecPosition.y - targetY) < 0.1f) {
		this->vecPosition.y = targetY;
	}
	if (abs(this->vecPosition.z - targetZ) < 0.1f) {
		this->vecPosition.z = targetZ;
	}
	// 位置が目標位置に到達した場合、次の目標位置へ移動
	if (abs(this->vecPosition.x - targetX) < 0.1f &&
		abs(this->vecPosition.y - targetY) < 0.1f &&
		abs(this->vecPosition.z - targetZ) < 0.1f) {
		vPath.erase(vPath.begin()); // 目標位置を削除
	}
	// 目標位置がなくなった場合は何もしない
	if (vPath.empty()) {
		return;
	}
	// 位置を更新
	this->vecPosition.x = targetX;
	this->vecPosition.y = targetY;
	this->vecPosition.z = targetZ;
	// キャラクターの向きを目標位置に向ける
	float deltaX = targetX - this->vecPosition.x;
	float deltaY = targetY - this->vecPosition.y;
	float deltaZ = targetZ - this->vecPosition.z;
	this->vecDirection.x = deltaX;
	this->vecDirection.y = deltaY;
	this->vecDirection.z = deltaZ;
	// 向きを正規化
	float length = sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
	if (length > 0.0f) {
		this->vecDirection.x /= length;
		this->vecDirection.y /= length;
		this->vecDirection.z /= length;
	}
	else {
		this->vecDirection.x = 0.0f;
		this->vecDirection.y = 0.0f;
		this->vecDirection.z = 0.0f;
	}
}

// 描写
void Character_Enemy_Normal_Walk::Draw()
{
    // カプセルを描写
    DrawCapsule3D(this->vecPosition, VAdd(this->vecPosition, VGet(0, 64, 0)), 40.0f, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
}

// リセット処理
void Character_Enemy_Normal_Walk::Reset()
{

}
