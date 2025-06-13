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
	SetUseLighting(FALSE);

	/* �J�����ݒ� */
	SetCameraPositionAndTargetAndUpVec( VGet(0.0f, 500.0f, -500.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.f, 1.f, 0.0f));

	/* �I�u�W�F�N�g�`�� */
	DrawLine3D(VGet(100.0f, 0.0f, 0.0f), VGet(-100.0f, 0.0f, 0.0f), GetColor(255, 0, 0));
	DrawLine3D(VGet(0.0f, 0.0f, 100.0f), VGet(0.0f, 0.0f, -100.0f), GetColor(0, 0, 255));

	DrawTriangle3D(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 100.0f), VGet(100.0f, 0.0f, 0.0f), GetColor(255, 255, 255), TRUE);
}

