#include "GameplayingScene.h"
#include "DxLib.h"
#include <cassert>
#include "../game.h"
#include "../InputState.h"
#include "SceneManager.h"
#include "PauseScene.h"
#include "GameoverScene.h"
#include "GameclearScene.h"

GameplayingScene::GameplayingScene(SceneManager& manager) :
	Scene(manager), updateFunc_(&GameplayingScene::FadeInUpdat)
{

}

GameplayingScene::~GameplayingScene()
{

}

void GameplayingScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void GameplayingScene::Draw()
{
	DrawString(Game::kScreenWidth / 2, Game::kScreenHeight / 2, L"ゲームプレイングシーン", 0xffffff);
	DrawString(0, 20, L"ゲームクリア:Enter", 0xffffff);
	DrawString(0, 40, L"ゲームオーバー:z", 0xffffff);
	DrawString(0, 60, L"ポーズ:P", 0xffffff);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, fadeColor_, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameplayingScene::FadeInUpdat(const InputState& input)
{
	fadeValue_ = 255 * fadeTimer_ / kFadeInterval;
	if (--fadeTimer_ == 0)
	{
		updateFunc_ = &GameplayingScene::NormalUpdat;
		fadeValue_ = 0;
		return;
	}
}

void GameplayingScene::NormalUpdat(const InputState& input)
{
	//ポーズ画面
	if (input.IsTriggered(InputType::pause))
	{
		int sound = 0;
		manager_.PushScene(new PauseScene(manager_, sound));
		return;
	}

	if (input.IsTriggered(InputType::next))
	{
		updateFunc_ = &GameplayingScene::FadeOutUpdat;
		fadeColor_ = 0x000000;
		crea_ = 0;
		return;
	}
	else if (input.IsTriggered(InputType::shot))
	{
		updateFunc_ = &GameplayingScene::FadeOutUpdat;
		fadeColor_ = 0xff0000;
		crea_ = 1;
		return;
	}
}

void GameplayingScene::FadeOutUpdat(const InputState& input)
{
	fadeValue_ = 255 * fadeTimer_ / kFadeInterval;

	if(++fadeTimer_ == kFadeInterval)
	{
		switch (crea_)
		{
		case 0:
			manager_.ChangeScene(new GameclearScene(manager_));
			return;
		case 1:
			manager_.ChangeScene(new GameoverScene(manager_));
		default:
			return;
		}
	}
}

