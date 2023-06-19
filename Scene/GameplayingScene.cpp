#include "GameplayingScene.h"
#include "DxLib.h"
#include <cassert>
#include "../game.h"
#include "../InputState.h"
#include "SceneManager.h"
#include "PauseScene.h"
#include "GameoverScene.h"
#include "GameclearScene.h"
#include "../Util/DrawFunctions.h"
#include "../Game/Stage.h"
#include "../Player.h"

namespace
{
	//マップチップサイズ
	constexpr int kMapSize = 16;
	//マップチップ数
	constexpr int kMapChipNum = 32;
	//マップ表示拡大率(16*16を32*32に)
	constexpr float kDrawScale = 2.0f;
}

GameplayingScene::GameplayingScene(SceneManager& manager) :
	Scene(manager), updateFunc_(&GameplayingScene::FadeInUpdat)
{
	chipHandle_ = my::MyLoadGraph(L"Data/stage/mapchip.png");
	stage_ = std::make_shared<Stage>();
	stage_->Load(L"Data/stage/stage1.fmf");
	player_ = std::make_shared<Player>();
}

GameplayingScene::~GameplayingScene()
{
	DeleteGraph(chipHandle_);
}

void GameplayingScene::Update(const InputState& input)
{
	player_->Update();
	(this->*updateFunc_)(input);
}

void GameplayingScene::Draw()
{
	DrawString(Game::kScreenWidth / 2, Game::kScreenHeight / 2, L"ゲームプレイングシーン", 0xffffff);
	DrawString(0, 20, L"ゲームクリア:Enter", 0xffffff);
	DrawString(0, 40, L"ゲームオーバー:z", 0xffffff);
	DrawString(0, 60, L"ポーズ:P", 0xffffff);

	//ステージを表示
	int mW, mH;//ステージのサイズ
	stage_->GetMapSize(mW, mH);
	int chipId = 0;//チップIDの取得
	for (int chipY = 0; chipY < mH; chipY++)
	{
		for (int chipX = 0; chipX < mW; chipX++)
		{
			chipId = stage_->GetChipId(0, chipX, chipY);
			if (chipId != 0)
			{
				my::MyDrawRectRotaGraph(chipX * 32 + 16, chipY * 32 -10,//表示するサイズをかける
										(chipId % kMapChipNum) * kMapSize, (chipId / kMapChipNum) * kMapSize,
										kMapSize, kMapSize,
										kDrawScale, 0.0f, chipHandle_, true, false);
			}
		}
	}


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, fadeColor_, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	player_->Draw();
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

