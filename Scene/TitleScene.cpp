#include "TitleScene.h"
#include <DxLib.h>
#include "../game.h"
#include "../InputState.h"
#include "../Util/DrawFunctions.h"
#include "SceneManager.h"
#include "GameplayingScene.h"
#include "PauseScene.h"

TitleScene::TitleScene(SceneManager& manager) : Scene(manager), updateFunc_(&TitleScene::FadeInUpdat)
{
	
}

TitleScene::~TitleScene()
{
	
}

void TitleScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void TitleScene::Draw()
{
	DrawString(0, 20, L"次へ:Enter", 0xffffff);
	DrawString(0, 40, L"ポーズ:P", 0xffffff);
	DrawString(Game::kScreenWidth / 2, Game::kScreenHeight / 2, L"タイトル", 0xffffff);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::FadeInUpdat(const InputState& input)
{
	fadeValue_ = 255 * static_cast<int>(fadeTimer_) / static_cast<int>(kFadeInterval);
	if (--fadeTimer_ == 0)
	{
		updateFunc_ = &TitleScene::NormalUpdat;
		fadeValue_ = 0;
	}
}

void TitleScene::NormalUpdat(const InputState& input)
{
	//「次へ」ボタンが押されたら次シーンへ移行する
	if (input.IsTriggered(InputType::next))
	{
		updateFunc_ = &TitleScene::FadeOutUpdat;
	}
	else if (input.IsTriggered(InputType::pause))
	{
		int bgm = 0;
		manager_.PushScene(new PauseScene(manager_, bgm));
		return;
	}
}

void TitleScene::FadeOutUpdat(const InputState& input)
{
	fadeValue_ = 255 * static_cast<int>(fadeTimer_) / static_cast<int>(kFadeInterval);
	if (++fadeTimer_ == kFadeInterval)
	{
		manager_.ChangeScene(new GameplayingScene(manager_));
		return;
	}
}
