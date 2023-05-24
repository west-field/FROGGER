#include "GameoverScene.h"
#include <DxLib.h>
#include "../game.h"
#include "../InputState.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "GameplayingScene.h"

GameoverScene::GameoverScene(SceneManager& manager) :
	Scene(manager),  updateFunc_(&GameoverScene::FadeInUpdat)
{

}

GameoverScene::~GameoverScene()
{
}

void GameoverScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void GameoverScene::Draw()
{
	DrawString(Game::kScreenWidth / 2, Game::kScreenHeight / 2, L"ゲームオーバー", 0xffffff);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, fadeColor_, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameoverScene::FadeInUpdat(const InputState& input)
{
	fadeValue_ = 255 * fadeTimer_ / kFadeInterval;
	if (--fadeTimer_ == 0)
	{
		updateFunc_ = &GameoverScene::NormalUpdat;
		fadeColor_ = 0x000000;
		fadeValue_ = 0;
	}
}

void GameoverScene::NormalUpdat(const InputState& input)
{
	//「次へ」ボタンが押されたら次シーンへ移行する
	if (input.IsTriggered(InputType::next))
	{
		updateFunc_ = &GameoverScene::FadeOutUpdat;
		return;
	}
}

void GameoverScene::FadeOutUpdat(const InputState& input)
{
	fadeValue_ = 255 * fadeTimer_ / kFadeInterval;
	if (++fadeTimer_ == kFadeInterval)
	{
		manager_.ChangeScene(new TitleScene(manager_));
		return;
	}
}

