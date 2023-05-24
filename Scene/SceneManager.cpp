#include "SceneManager.h"
#include "Secne.h"

void SceneManager::ChangeScene(Scene* scene)
{
	//シーンスタックが(empty)空ではなかったら
	if (!scenes_.empty())
	{
		delete scenes_.front();
		scenes_.pop_front();
	}
	scenes_.push_front(scene);//一個増える
}

void SceneManager::PushScene(Scene* scene)
{
	scenes_.push_front(scene);//一個増える
}

void SceneManager::PopScene()
{
	//ポップの結果シーンが0にならないようにする
	if (scenes_.size() > 1)
	{
		delete scenes_.front();//topはてっぺんの要素を返している
		scenes_.pop_front();//一個減る→普通は0になる
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