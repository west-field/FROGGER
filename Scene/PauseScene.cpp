#include "PauseScene.h"
#include <DxLib.h>
#include "../game.h"
#include "../InputState.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "KeyConfigScene.h"
#include "SoundSettingScene.h"

PauseScene::PauseScene(SceneManager& manager,int soundH) : Scene(manager), soundH_(soundH)
{

}

PauseScene::~PauseScene()
{

}

void PauseScene::Update(const InputState& input)
{
	bool isPress = false;
	if (input.IsTriggered(InputType::down))
	{
		selectNum_ = (selectNum_ + 1) % pauseMax;
		isPress = true;
	}
	else if (input.IsTriggered(InputType::up))
	{
		selectNum_ = (selectNum_ + (pauseMax - 1)) % pauseMax;
		isPress = true;
	}

	if (isPress)
	{
		for (int i = 0; i < pauseMax; i++)
		{
			if (i == selectNum_)
			{
				pauseMenu_[i].x = pw_start_x + 10;
				pauseMenu_[i].color = 0xaaffaa;
			}
			else
			{
				pauseMenu_[i].x = pw_start_x + 20;
				pauseMenu_[i].color = 0xffffff;
			}
		}
	}

	if (input.IsTriggered(InputType::next))
	{
		switch (selectNum_)
		{
		case pauseKeyconfig:
			manager_.PushScene(new KeyConfigScene(manager_, input));
			return;
		case pauseSound:
			manager_.PushScene(new SoundSettingScene(manager_,soundH_));
			return;
		case pauseBack:
			manager_.PopScene();
			return;
		default:
			break;
		}
	}
	if (input.IsTriggered(InputType::prev))
	{
		selectNum_ = pauseBack;
		manager_.PopScene();
		return;
	}
}

void PauseScene::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_MULA, 196);
	//ポーズウィンドウセロファン
	DrawBox(pw_start_x, pw_start_y, pw_start_x + pw_width, pw_start_y + pw_height, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//ポーズ中メッセージ
	DrawString(pw_start_x + 10, pw_start_y + 10, L"ポーズ", 0xffff88);
	for (auto& menu : pauseMenu_)
	{
		DrawString(menu.x, menu.y, menu.name, menu.color);
	}
	//ポーズウィンドウ枠線
	DrawBox(pw_start_x, pw_start_y, pw_start_x + pw_width, pw_start_y + pw_height, 0xffffff, false);
}
