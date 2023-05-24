#pragma once
#include "Secne.h"

class InputState;
/// <summary>
/// �^�C�g���V�[��
/// </summary>
class TitleScene : public Scene
{
public:
	TitleScene(SceneManager& manager);
	virtual ~TitleScene();

	void Update(const InputState& input);
	virtual void Draw() override;

private:
	unsigned int m_color = 0x000000;
	//�t�F�[�h�C���̎���Update�֐�
	void FadeInUpdat(const InputState& input);
	//�ʏ��Ԃ̎���Update�֐�
	void NormalUpdat(const InputState& input);
	//�t�F�[�h�A�E�g�̎���Update�֐�
	void FadeOutUpdat(const InputState& input);

	//Update�p�����o�֐��|�C���^
	void (TitleScene::* updateFunc_)(const InputState& input);
};
