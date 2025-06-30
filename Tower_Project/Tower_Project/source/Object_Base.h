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

		bool	bGetDeleteFlg()		{ return this->bDeleteFlg; };	// 削除フラグを取得
		VECTOR	vecGetPosition()	{ return this->vecPosition; };	// オブジェクトの中心座標を取得
	
		void	SetDeleteFlg(bool bDeleteFlg)	{ this->bDeleteFlg	= bDeleteFlg; };	// 削除フラグを設定
		void	SetPosition(VECTOR vecPosition) { this->vecPosition = vecPosition; };	// オブジェクトの中心座標を設定

	protected:
		/* 変数 */
		bool	bDeleteFlg;				// 削除フラグ(有効ならオブジェクトを削除)
		VECTOR	vecPosition;			// オブジェクトの中心座標
};
