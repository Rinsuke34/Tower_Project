/* 2024.12.08 ��򕗏� �t�@�C���쐬 */

#include "AppFrame.h"

/* �V�[�� */
#include "Scene_Title.h"

// �V�[���̐ݒ�
namespace SCENE_SET
{
	// �Q�[���N�����̃V�[�����Z�b�g
	void	SetFastScene()
	{
		/* �V�[��"�^�C�g��"���Z�b�g */
		gpSceneServer->AddSceneReservation(new Scene_Title());
	}

	// ���[�h�V�[�����Z�b�g
	void	SetLoadScene()
	{

	}
}

// ������
namespace PROJECT_INIT
{
	// �v���W�F�N�g����������
	void	Init()
	{
		/* �f�[�^���X�g�쐬 */
		{

		}

		/* �f�[�^���X�g�擾 */
		{

		}
	}
}