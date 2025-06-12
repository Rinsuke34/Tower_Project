/* 2025.05.09 ��򕗏� �t�@�C���ǉ� */

#include "Scene_Title.h"

/* �V�[�� */
#include "Scene_World.h"

/* �V�[��"�^�C�g��"�̒�` */
// �R���X�g���N�^
Scene_Title::Scene_Title() : SceneBase("Scene_Title", 0, false)
{
	// ����������
	Initialization();
}

// �f�X�g���N�^
Scene_Title::~Scene_Title()
{

}

// ������
void Scene_Title::Initialization()
{

}

// �v�Z
void Scene_Title::Process()
{
	/* ���͑҂� */
	if (gstKeyboardInputData.cgInput[INPUT_HOLD][KEY_INPUT_Z] == true)
	{
		/* �V�[��"���[���h"���Z�b�g */
		gpSceneServer->AddSceneReservation(new Scene_World());

		/* �V�[���폜�t���O��L���ɂ��� */
		this->bDeleteFlg = true;
	}
}

// �`��
void Scene_Title::Draw()
{
	/* �^�C�g����ʕ`�� */
	DrawString(SCREEN_SIZE_WIDE / 2, SCREEN_SIZE_HEIGHT / 2, "�^�C�g��", GetColor(255, 255, 255));
}

