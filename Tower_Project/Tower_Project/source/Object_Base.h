/* 2025.06.22 駒沢風助 ファイル作成 */

#pragma once
#include <DxLib.h>
#include <vector>
#include <algorithm>
#include "AppStructDefine.h"
#include "AppFunctionDefine.h"

/* すべてのオブジェクトのベースとなるクラスの宣言 */

// オブジェクトベースクラス
class Object_Base
{
	public:
		Object_Base();					// コンストラクタ
		virtual ~Object_Base() {};		// デストラクタ

		virtual void	Initialization()	{};	// 初期化
		virtual void	Update()			{};	// 更新
		virtual void	Draw()				{};	// 描写
		virtual void	Reset()				{};	// リセット処理

		void	DrawHpBar();					// 体力バーの描写

		int		iGetMaxHp()			{ return this->iMaxHp; };		// 最大体力を取得
		int		iGetNowHp()			{ return this->iNowHp; };		// 残り体力を取得
		bool	bGetDeleteFlg()		{ return this->bDeleteFlg; };	// 削除フラグを取得
		VECTOR	vecGetPosition()	{ return this->vecPosition; };	// オブジェクトの中心座標を取得
		VECTOR	vecGetDirection()	{ return this->vecDirection; };	// オブジェクトの向きを取得(正規化されたベクトル)
	
		void	SetDeleteFlg(bool bDeleteFlg)		{ this->bDeleteFlg		= bDeleteFlg; };	// 削除フラグを設定
		void	SetPosition(VECTOR vecPosition)		{ this->vecPosition		= vecPosition; };	// オブジェクトの中心座標を設定
		void	SetDirection(VECTOR vecDirection)	{ this->vecDirection	= vecDirection; };	// オブジェクトの向きを設定(正規化されたベクトル)

		void	ReceivedDamage(int iDamage) { this->iNowHp -= iDamage; }	// ダメージ分体力を減らす

	protected:
		/* 変数 */
		int		iMaxHp;					// 最大体力
		int		iNowHp;					// 残り体力
		bool	bDeleteFlg;				// 削除フラグ(有効ならオブジェクトを削除)
		VECTOR	vecPosition;			// オブジェクトの中心座標
		VECTOR	vecDirection;			// オブジェクトの向き(正規化されたベクトル)
};
