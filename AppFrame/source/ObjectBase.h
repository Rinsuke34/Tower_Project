/* 2024.12.15 駒沢風助 ファイル作成 */

#pragma once
#include <DxLib.h>
#include <vector>
#include <algorithm>
#include "AppStructDefine.h"
#include "AppFunctionDefine.h"

/* すべてのオブジェクトのベースとなるクラスの宣言 */

// オブジェクトベースクラス
class ObjectBase
{
	public:
		ObjectBase();					// コンストラクタ
		virtual ~ObjectBase() {};		// デストラクタ

		virtual void	Initialization()		{};	// 初期化
		virtual void	Update()				{};	// 更新
		virtual void	Draw()					{};	// 描写
		virtual void	Reset()					{};	// リセット処理

		bool	bGetDeleteFlg()					{ return this->bDeleteFlg; };			// 削除フラグを取得

		void	SetDeleteFlg(bool bDeleteFlg)	{ this->bDeleteFlg	= bDeleteFlg; };	// 削除フラグを設定

	protected:
		/* 変数 */
		bool	bDeleteFlg;				// 削除フラグ(有効ならオブジェクトを削除)
};
