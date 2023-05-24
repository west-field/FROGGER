#include "SceneManager.h"
#include "Secne.h"

void SceneManager::ChangeScene(Scene* scene)
{
	//�V�[���X�^�b�N��(empty)��ł͂Ȃ�������
	if (!scenes_.empty())
	{
		delete scenes_.front();
		scenes_.pop_front();
	}
	scenes_.push_front(scene);//�������
}

void SceneManager::PushScene(Scene* scene)
{
	scenes_.push_front(scene);//�������
}

void SceneManager::PopScene()
{
	//�|�b�v�̌��ʃV�[����0�ɂȂ�Ȃ��悤�ɂ���
	if (scenes_.size() > 1)
	{
		delete scenes_.front();//top�͂Ă��؂�̗v�f��Ԃ��Ă���
		scenes_.pop_front();//����遨���ʂ�0�ɂȂ�
	}
}

void SceneManager::Update(const InputState& input)
{
	scenes_.front()->Update(input);
}

void SceneManager::Draw()
{
	for (int i = static_cast<int>(scenes_.size() - 1); i >= 0; i--)
	{
		scenes_[i]->Draw();
	}
}