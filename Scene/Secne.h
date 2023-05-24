#pragma once

//�v���g�^�C�v�錾
class SceneManager;//�V�[���}�l�[�W���[
class InputState;//���̓X�e�[�g

/// <summary>
/// �V�[�����N���X//���ɂȂ��Ă���
/// </summary>
class Scene
{
protected:
	SceneManager& manager_;//�V�[���}�l�[�W���[�ւ̎Q��
	
	static constexpr int kFadeInterval = 60;
	int fadeTimer_ = kFadeInterval;//�t�F�[�h�^�C�}�[
	int fadeValue_ = 255;//����`�Ƃ̃u�����h�
public:
	Scene(SceneManager& manager) :manager_(manager){}
	virtual ~Scene() {}
	//�V�[�����X�V����
	virtual void Update(const InputState& input) = 0;
	//�V�[����`�悷��
	virtual void Draw() = 0;
};

