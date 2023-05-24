#include "GameclearScene.h"
#include <DxLib.h>
#include "../game.h"
#include "../InputState.h"
#include "SceneManager.h"
#include "TitleScene.h"

GameclearScene::GameclearScene(SceneManager& manager) :
	Scene(manager), updateFunc_(&GameclearScene::FadeInUpdat)
{ 
}

GameclearScene::~GameclearScene()
{

}

void GameclearScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void GameclearScene::Draw()
{
	DrawString(Game::kScreenWidth / 2, Game::kScreenHeight / 2, L"ÉQÅ[ÉÄÉNÉäÉA", 0xffffff);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, fadeColor_, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameclearScene::FadeInUpdat(const InputState& input)
{
	fadeValue_ = 255 * fadeTimer_ / kFadeInterval;
	if (--fadeTimer_ == 0)
	{
		updateFunc_ = &GameclearScene::NormalUpdat;
		fadeValue_ = 0;
	}
}
void GameclearScene::FadeOutUpdat(const InputState& input)
{
	fadeValue_ = 255 * fadeTimer_ / kFadeInterval;
	if (++fadeTimer_ == kFadeInterval)
	{
		manager_.ChangeScene(new TitleScene(manager_));
		return;
	}
}

void GameclearScene::NormalUpdat(const InputState& input)
{
	if (input.IsTriggered(InputType::next))
	{
		updateFunc_ = &GameclearScene::FadeOutUpdat;
		fadeColor_ = 0x000000;
		return;
	}
}
