/* 2025.07.18 駒沢風助 ファイル作成 */

#include "Character_Enemy_HightSpeed_Walk.h"
#include <vector>

#include "DataList_Object.h"

#include "StructDefine.h"
#include "ConstantDefine.h"

Character_Enemy_HightSpeed_Walk::Character_Enemy_HightSpeed_Walk() : Character_Base(OBJECT_ID_ENEMY_NORMAL_WALK)
{
    /* 変数 */
    this->iModelHandle = MV1LoadModel("resource/Model/Enemy/Enemy2.mv1");

    this->fAngle            = 0.0f;             // 初期角度設定
    this->iAttackInterval   = 0;                // 攻撃間隔を初期化
    this->iMaxHp            = ENEMY_HP_MAX;     // エネミーの最大体力を設定
    this->iNowHp            = this->iMaxHp;     // エネミーの初期体力を設定
}

// デストラクタ
Character_Enemy_HightSpeed_Walk::~Character_Enemy_HightSpeed_Walk()
{
    MV1DeleteModel(this->iModelHandle);
}

// 初期化
void Character_Enemy_HightSpeed_Walk::Initialization()
{
    // ルート検索
    RouteSearch();
}

// 更新
void Character_Enemy_HightSpeed_Walk::Update()
{
    // 体力が0以下なら削除フラグを立てる
    if (this->iNowHp <= 0)
    {
        this->bDeleteFlg = true;
        return;
    }

    // 周囲に建造物があるか確認
    for (auto& Building : static_cast<DataList_Object*>(gpDataListServer->GetDataList("DataList_Object"))->paBuildingList)
    {
        // 建造物の陣営がプレイヤーであるか確認
        if (Building->iGetFactionNo() == OBJECT_FACTION_PLAYER)
        {
            // 建造物が攻撃範囲内であるか確認
            if (VSize(VSub(Building->vecGetPosition(), this->vecPosition)) <= ENEMY_ATTACK_RANGE)
            {
                // 攻撃範囲内に建造物がある場合
                // 攻撃のインターバルが0であるか確認
                if (this->iAttackInterval <= 0)
                {
                    // 攻撃のインターバルを設定
                    this->iAttackInterval = ENEMY_ATTACK_INTERVAL / 3;

                    // 攻撃処理を実行
                    Building->ReceivedDamage(ENEMY_ATTACK_DAMAGE);
                }
                else
                {
                    // 攻撃のインターバルを減らす
                    this->iAttackInterval--;
                }


                // 更新処理を終了する
                return;
            }
        }
    }

    // 移動ルートが存在しない場合は何もしない
    if (this->aMovePath.empty())
    {
        return;
    }

    // 移動前座標を保存
    VECTOR vecOldPosition = this->vecPosition;

    const float MOVE_SPEED      = 3.0f; // 移動速度
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

    // 移動前座標と移動後座標から角度を計算
    float fDirectionX = vecOldPosition.x - this->vecPosition.x;
    float fDirectionZ = vecOldPosition.z - this->vecPosition.z;
    this->fAngle = atan2f(fDirectionZ, fDirectionX);
}

// 描写
void Character_Enemy_HightSpeed_Walk::Draw()
{
    // モデルの位置を設定
    MV1SetPosition(this->iModelHandle, this->vecPosition);

    // モデルの回転を設定
    MV1SetRotationXYZ(this->iModelHandle, VGet(0.0f, -this->fAngle, 0.0f));

    // モデルの描写
    MV1DrawModel(this->iModelHandle);

    // 体力バーの描写
    DrawHpBar();
}
