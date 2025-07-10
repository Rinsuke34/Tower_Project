/* 2025.07.01 駒沢風助 ファイル作成 */

#include "Character_Enemy_Normal_Walk.h"
#include <vector>

#include "DataList_Object.h"

#include "StructDefine.h"
#include "ConstantDefine.h"

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
    // 移動ルートをA*アルゴリズムで計算
    // ※X軸とZ軸の二次元で判断する
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

    // スタート地点の情報をオープンリストとして評価値リストへ追加
    ASTAR_EVALUATION_LIST stAddStart;
    stAddStart.iId = ASTAR_ID_START;	// スタートノードに設定
    stAddStart.iG = 0;
    stAddStart.iH = abs(stStart.iX - stGoal.iX) + abs(stStart.iZ - stGoal.iZ);  // ゴールまでのコストはマンハッタン距離で算出(Y軸は考慮しない)
    stAddStart.iF = stAddStart.iG + stAddStart.iH;
    stAddStart.bOpen = true;
    stAddStart.bClose = false;
    stAddStart.stPosition = stStart; // 現在の座標をスタート座標に設定
    stAddStart.stParent = { -1, -1, -1 };
    stAStarEvaluationList.push_back(stAddStart);

    // 確認で使用する変数定義
    bool            bGoalFoundFlg = false;			// ゴール到達フラグ
    POSITION_3D_MAP stCurrentPosition = { -1, -1, -1 };	// 現在探索中の座標

    // A*アルゴリズムを用いた経路探索処理
    while (true)
    {
        // 評価値リスト内のオープンリストからF値(類型コストが最小のノード)を探索
        int     iMinF = INT_MAX;  // 最小F値
        bool    bFoundFlg = false;    // 最小F値ノードが見つかったかのフラグ
        int     iGetG = 0;        // 最小F値のG値(スタート地点からの総コスト)

        for (auto& node : stAStarEvaluationList)
        {
            // オープンリスト内かつF値が最小であるか
            if (node.bOpen && node.iF < iMinF)
            {
                // F値が最小のノードである場合
                bFoundFlg = true;     // 最小F値ノードが見つかったフラグを立てる
                iMinF = node.iF;  // 最小F値を更新
                stCurrentPosition = { node.stPosition.iX, node.stPosition.iY, node.stPosition.iZ }; // 現在探索中の座標を更新
                iGetG = node.iG;  // 最小F値のG値を更新
            }
        }

        // 最小F値ノードが見つからなかった場合、探索失敗とする
        if (!bFoundFlg)
        {
            break;
        }

        // 最小F値ノードを探索したので、現在のノードをオープンリストからクローズリストへ移動
        for (auto& node : stAStarEvaluationList)
        {
            if (node.stPosition.iX == stCurrentPosition.iX && node.stPosition.iY == stCurrentPosition.iY && node.stPosition.iZ == stCurrentPosition.iZ)
            {
                node.bOpen = false; // オープンリストから削除
                node.bClose = true;  // クローズリストに追加
                break;
            }
        }

        // 隣接(X/Z方向)のノードを探索
        const int POS_INDEX = 4;
        POSITION_3D_MAP astNextPosition[POS_INDEX] =
        {
            { stCurrentPosition.iX - 1, stCurrentPosition.iY, stCurrentPosition.iZ }, // 左
            { stCurrentPosition.iX + 1, stCurrentPosition.iY, stCurrentPosition.iZ }, // 右
            { stCurrentPosition.iX, stCurrentPosition.iY, stCurrentPosition.iZ - 1 }, // 前
            { stCurrentPosition.iX, stCurrentPosition.iY, stCurrentPosition.iZ + 1 }  // 奥
        };

        for (int iIndex = 0; iIndex < POS_INDEX; iIndex++)
        {
            int iMoveCost = MOVE_COST_DEFAULT;  // 移動コスト

            // 確認する座標を取得
            int iSearchX = astNextPosition[iIndex].iX;
            int iSearchY = astNextPosition[iIndex].iY;
            int iSearchZ = astNextPosition[iIndex].iZ;

            // マップの範囲外ならスキップ
            if (iSearchX < 0 || MAP_SIZE_X <= iSearchX || iSearchZ < 0 || MAP_SIZE_Z <= iSearchZ)
            {
                continue;
            }

            // 移動先に足場があるか確認
            if (aiMapData[iSearchX][iSearchY][iSearchZ] != 0)
            {
                // 足場がある場合
                // 現在の座標が最上段であるならスキップ
                if (stCurrentPosition.iY == MAP_SIZE_Y - 1)
                {
                    continue;
                }

                // 元座標と移動先の一つ上の座標に足場があるか確認
                // ※どちらかに足場がある場合、移動不可とする
                if (aiMapData[stCurrentPosition.iX][stCurrentPosition.iY + 1][stCurrentPosition.iZ] != 0 ||
                    aiMapData[iSearchX][iSearchY + 1][iSearchZ] != 0)
                {
                    continue;
                }

                // 確認対象のノード情報を一つ上の段とする
                iSearchY += 1;

                // 上方向の移動コストを設定
                iMoveCost = MOVE_COST_UP;
            }
            else
            {
                // 足場がない場合
                // 現在の座標が最下段であるならスキップ
                if (stCurrentPosition.iY == 0)
                {
                    continue;
                }

                // 移動先座標を基準とし、足場が見つかるまで下方向へサーチ
                int     iPlatformSearchY = iSearchY; // 足場のあるY座標
                bool    bFoundPlatform = false;    // 足場が見つかったかのフラグ
                for (int iY = iSearchY; iY >= 0; iY--)
                {
                    // 足場があるか確認
                    if (aiMapData[iSearchX][iY][iSearchZ] != 0)
                    {
                        iPlatformSearchY = iY;   // 足場の座標を設定
                        bFoundPlatform = true; // 足場が見つかったフラグを立てる
                        break;
                    }
                }

                // 足場が見つからなかった場合、スキップ
                if (!bFoundPlatform)
                {
                    continue;
                }

                // 足場が見つかった場合、移動先座標を足場の上に設定
                iSearchY = iPlatformSearchY + 1;

                // 下方向の移動コストを設定
                iMoveCost = MOVE_COST_DOWN;
            }

            // 移動先座標の情報をまとめる
            ASTAR_EVALUATION_LIST stAddNode;
            stAddNode.iId = ASTER_ID_NONE;				// 特に何もないノードとして設定
            stAddNode.iG = iGetG + iMoveCost;            // 移動コストを加算
            stAddNode.iH = abs(iSearchX - stGoal.iX) + abs(iSearchY - stGoal.iY) + abs(iSearchZ - stGoal.iZ); // ゴールまでのコストはマンハッタン距離で算出(Y軸は考慮しない)
            stAddNode.iF = stAddNode.iG + stAddNode.iH;  // 総コストを計算
            stAddNode.bOpen = true;
            stAddNode.bClose = false;
            stAddNode.stPosition.iX = iSearchX;						// 移動先座標を設定
            stAddNode.stPosition.iY = iSearchY;						// 移動先座標を設定
            stAddNode.stPosition.iZ = iSearchZ;						// 移動先座標を設定
            stAddNode.stParent = stCurrentPosition;            // 親座標を現在の座標に設定

            // すでに評価値リストに同じ座標が存在するか確認
            // ※同じ座標が存在する場合は、より良い経路であれば更新する
            bool bAddNodeFlg = true; // ノードを追加するかのフラグ
            for (auto& node : stAStarEvaluationList)
            {
                // 完全に同じ座標であるか確認
                if (node.stPosition.iX == iSearchX && node.stPosition.iY == iSearchY && node.stPosition.iZ == iSearchZ)
                {
                    // 同じ座標が存在する場合、ノード追加を行わない
                    bAddNodeFlg = false;
                    break;
                }
            }

            // ノードを追加するフラグが立っている場合、評価値リストに追加
            if (bAddNodeFlg)
            {
                // ゴールに到達した場合、探索成功とする
                if (stCurrentPosition.iX == stGoal.iX && stCurrentPosition.iZ == stGoal.iZ)
                {
                    bGoalFoundFlg = true;
                    stAddNode.iId = ASTAR_ID_GOAL; // ゴールノードに設定

                    // 移動先座標をオープンリストとして評価値リストへ追加
                    stAStarEvaluationList.push_back(stAddNode);
                    break;
                }
                else
                {
                    // 移動先座標をオープンリストとして評価値リストへ追加
                    stAStarEvaluationList.push_back(stAddNode);
                }
            }
        }

        // 探索が終了した場合、ループを抜ける
        if (bGoalFoundFlg)
        {
            break;
        }
    }

    // 探索が成功したか確認
    if (bGoalFoundFlg)
    {
        // 経路を復元し、移動ルートに追加する
        // ※ここではゴールからスタートへ向けて経路を復元する
        bool			bStartFound = false;			// スタート座標が見つかったかのフラグ
        POSITION_3D_MAP stCheckPosition = { -1, -1, -1 };	// 現在のチェック座標を初期化

        // 評価値リストをループして、ゴールからスタートへ向けて経路を復元
        while (true)
        {
            // 移動前座標を評価値リストから検索し、親座標を見つける
            for (auto& Evaluation : stAStarEvaluationList)
            {
                // チェック座標が一致するノードを探す
                // ※現在のチェック座標が初期状態である場合、IDがゴールノードの情報を取得
                if ((Evaluation.stPosition.iX == stCheckPosition.iX &&
                    Evaluation.stPosition.iY == stCheckPosition.iY &&
                    Evaluation.stPosition.iZ == stCheckPosition.iZ) ||
                    (Evaluation.iId == ASTAR_ID_GOAL &&
                        stCheckPosition.iX == -1 &&
                        stCheckPosition.iY == -1 &&
                        stCheckPosition.iZ == -1))
                {
                    // 対象のノードが見つかった場合、チェック座標を親座標に更新する
                    stCheckPosition = Evaluation.stParent;

                    // ノードの座標を移動ルートに追加
                    POSITION_3D_MAP stAddMovePath = { Evaluation.stPosition.iX, Evaluation.stPosition.iY, Evaluation.stPosition.iZ };
                    this->aMovePath.push_back(stAddMovePath);

                    // スタート座標に到達した場合、フラグを立てる
                    if (Evaluation.iId == ASTAR_ID_START)
                    {
                        bStartFound = true;
                        break;
                    }
                }
            }

            // スタート座標に到達した場合、ループを抜ける
            if (bStartFound)
            {
                // 移動ルートのインデックスを初期化
                this->iMovePathIndex = static_cast<int>(this->aMovePath.size()) - 1;

                // 現在の移動開始座標を設定
                this->vecNowMoveStartPosition = VGet(
                    static_cast<float>(this->aMovePath[this->iMovePathIndex].iX * TILE_SIZE_PIXEL_X),
                    static_cast<float>(this->aMovePath[this->iMovePathIndex].iY * TILE_SIZE_PIXEL_Y),
                    static_cast<float>(this->aMovePath[this->iMovePathIndex].iZ * TILE_SIZE_PIXEL_Z)
                );

                // 現在の移動終了座標を設定
                this->vecNowMoveEndPosition = VGet(
                    static_cast<float>(this->aMovePath[this->iMovePathIndex - 1].iX * TILE_SIZE_PIXEL_X),
                    static_cast<float>(this->aMovePath[this->iMovePathIndex - 1].iY * TILE_SIZE_PIXEL_Y),
                    static_cast<float>(this->aMovePath[this->iMovePathIndex - 1].iZ * TILE_SIZE_PIXEL_Z)
                );

                break;
            }
        }
    }
}

// 更新
void Character_Enemy_Normal_Walk::Update()
{
    // 移動ルートが存在しない場合は何もしない
    if (this->aMovePath.empty())
    {
        return;
    }

    const float MOVE_SPEED = 1.0f; // 移動速度
    const float ARRIVAL_EPSILON = 0.1f; // これ以下なら到達とみなす

    // 移動前座標から移動後座標へのベクトルを計算
    VECTOR vecDir = VSub(this->vecNowMoveEndPosition, this->vecPosition);

    // 移動前の距離を計算
    float fDistBefore = VSize(vecDir);

    // 正規化して進行方向単位ベクトルを得る
    vecDir = VNorm(vecDir);

    // 移動量をスケール
    VECTOR vecMove = VScale(vecDir, MOVE_SPEED);

    // 現在位置を更新
    this->vecPosition = VAdd(this->vecPosition, vecMove);

    // 移動後座標までの距離を再計算
    float fDistAfter = VSize(VSub(this->vecNowMoveEndPosition, this->vecPosition));

    // 到達判定：移動後距離がしきい値以下 または 移動前より距離が減らなくなった
    if (fDistAfter <= ARRIVAL_EPSILON || fDistAfter > fDistBefore)
    {
        // 現在の座標を移動前座標に設定
        this->vecNowMoveStartPosition = this->vecNowMoveEndPosition;

        // インデックスを減らす
        this->iMovePathIndex--;

        // インデックスが0以下ならルート終了
        if (this->iMovePathIndex <= 0)
        {
            // 終点に到達したので移動ルートをクリア
            this->aMovePath.clear();
            return;
        }

        // 次の移動後座標を設定
        POSITION_3D_MAP& stNext = this->aMovePath[this->iMovePathIndex];
        this->vecNowMoveEndPosition = VGet(
            static_cast<float>(stNext.iX) * TILE_SIZE_PIXEL_X,
            static_cast<float>(stNext.iY) * TILE_SIZE_PIXEL_Y,
            static_cast<float>(stNext.iZ) * TILE_SIZE_PIXEL_Z
        );
    }
}

// 描写
void Character_Enemy_Normal_Walk::Draw()
{
    // カプセルを描写
    DrawCapsule3D(this->vecPosition, VAdd(this->vecPosition, VGet(0, 64, 0)), 16.0f, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
}

// リセット処理
void Character_Enemy_Normal_Walk::Reset()
{

}
