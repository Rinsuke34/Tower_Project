/* 2025.06.13 ��򕗏� �t�@�C���ǉ� */

#include "AppFrame.h"

/* �V�[��"���[���h"�̐錾 */

// �V�[��"���[���h"
class Scene_World : public SceneBase
{
	public:
		Scene_World();				// �R���X�g���N�^
		virtual ~Scene_World();		// �f�X�g���N�^

		virtual void	Initialization()	override;	// ������
		virtual void	Process()			override;	// �v�Z
		virtual void	Draw()				override;	// �`��
};
