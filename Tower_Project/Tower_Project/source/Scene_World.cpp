/* 2025.06.13 ��򕗏� �t�@�C���ǉ� */

#include "Scene_World.h"

/* �V�[��"�^�C�g��"�̒�` */
// �R���X�g���N�^
Scene_World::Scene_World() : SceneBase("Scene_World", 0, false)
{
	// ����������
	Initialization();
}

// �f�X�g���N�^
Scene_World::~Scene_World()
{

}

// ������
void Scene_World::Initialization()
{

}

// �v�Z
void Scene_World::Process()
{

}

// �`��
void Scene_World::Draw()
{
	/* ���[���h��ʕ`�� */
	DrawString(SCREEN_SIZE_WIDE / 2, SCREEN_SIZE_HEIGHT / 2, "���[���h", GetColor(255, 255, 255));
}

