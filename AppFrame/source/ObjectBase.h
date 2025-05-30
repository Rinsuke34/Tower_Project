/* 2024.12.15 ��򕗏� �t�@�C���쐬 */

#pragma once
#include <DxLib.h>
#include <vector>
#include <algorithm>
#include "AppStructDefine.h"
#include "AppFunctionDefine.h"

/* ���ׂẴI�u�W�F�N�g�̃x�[�X�ƂȂ�N���X�̐錾 */

// �I�u�W�F�N�g�x�[�X�N���X
class ObjectBase
{
	public:
		ObjectBase();					// �R���X�g���N�^
		virtual ~ObjectBase() {};		// �f�X�g���N�^

		virtual void	Initialization()		{};	// ������
		virtual void	Update()				{};	// �X�V
		virtual void	Draw()					{};	// �`��
		virtual void	Reset()					{};	// ���Z�b�g����

		bool	bGetDeleteFlg()					{ return this->bDeleteFlg; };			// �폜�t���O���擾

		void	SetDeleteFlg(bool bDeleteFlg)	{ this->bDeleteFlg	= bDeleteFlg; };	// �폜�t���O��ݒ�

	protected:
		/* �ϐ� */
		bool	bDeleteFlg;				// �폜�t���O(�L���Ȃ�I�u�W�F�N�g���폜)
};
