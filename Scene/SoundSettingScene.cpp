#include "SoundSettingScene.h"
#include <Dxlib.h>
#include "../InputState.h"
#include "../Util/Sound.h"
#include "SceneManager.h"

SoundSettingScene::SoundSettingScene(SceneManager& manager,int soundH) :Scene(manager), soundH_(soundH), updateFunc_(&SoundSettingScene::NormalUpdate)
{
}

SoundSettingScene::~SoundSettingScene()
{
}

void SoundSettingScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void SoundSettingScene::Draw()
{
	//サウンドセッティングウィンドウ
	DrawBox(pw_start_x, pw_start_y, pw_start_x + pw_width, pw_start_y + pw_height, 0x884444, true);
	//サウンドセッティング中メッセージ
	DrawString(pw_start_x + 10, pw_start_y + 10, L"SoundSetting...", 0xffffaa);
	//BGMの設定
	auto& soundMgr = SoundManager::GetInstance();
	DrawFormatString(soundChange_[soundTypeBGM].x, soundChange_[soundTypeBGM].y, soundChange_[soundTypeBGM].color,
		soundChange_[soundTypeBGM].name.c_str(), soundMgr.GetBGMVolume());
	//SEの設定
	DrawFormatString(soundChange_[soundTypeSE].x, soundChange_[soundTypeSE].y, soundChange_[soundTypeSE].color,
		soundChange_[soundTypeSE].name.c_str(), soundMgr.GetSEVolume());

	DrawFormatString(soundChange_[soundTypeBack].x, soundChange_[soundTypeBack].y, soundChange_[soundTypeBack].color,
		soundChange_[soundTypeBack].name.c_str());
	//サウンドセッティングウィンドウ枠線
	DrawBox(pw_start_x, pw_start_y, pw_start_x + pw_width, pw_start_y + pw_height, 0xffffff, false);
}

void SoundSettingScene::NormalUpdate(const InputState& input)
{
	bool isPress = false;
	if (input.IsTriggered(InputType::down))
	{
		selectNum_ = (selectNum_ + 1) % soundTypeMax;
		isPress = true;
	}
	else if (input.IsTriggered(InputType::up))
	{
		selectNum_ = (selectNum_ + (soundTypeMax - 1)) % soundTypeMax;
		isPress = true;
	}

	if (isPress)
	{
		SoundManager::GetInstance().Play(SoundId::Cursor);
		for (int i = 0; i < soundTypeMax; i++)
		{
			if (i == selectNum_)
			{
				soundChange_[i].x = pw_start_x + 10;
				soundChange_[i].color = 0xaaffaa;
			}
			else
			{
				soundChange_[i].x = pw_start_x + 20;
				soundChange_[i].color = 0xffffff;
			}
		}
	}
	auto& soundMgr = SoundManager::GetInstance();

	if (input.IsTriggered(InputType::next))
	{
		SoundManager::GetInstance().Play(SoundId::Determinant);
		switch (selectNum_)
		{
		case soundTypeBGM:
			soundChange_[soundTypeBGM].color = 0xffa000;
			updateFunc_ = &SoundSettingScene::BGMVolumeChange;
			return;
		case soundTypeSE:
			soundChange_[soundTypeSE].color = 0xffa000;
			updateFunc_ = &SoundSettingScene::SEVolumeChange;
			return;
		case soundTypeBack:
			soundMgr.SaveSoundConfig();
			manager_.PopScene();
			return;
		default:
			break;
		}
	}
	if (input.IsTriggered(InputType::prev))
	{
		soundMgr.SaveSoundConfig();
		SoundManager::GetInstance().Play(SoundId::Determinant);
		selectNum_ = soundTypeBack;
		manager_.PopScene();
		return;
	}
}

void SoundSettingScene::BGMVolumeChange(const InputState& input)
{
	auto& soundMgr = SoundManager::GetInstance();
	int soundVolume = 0;
	//BGM
	if (input.IsPressed(InputType::up))
	{
		if (input.IsTriggered(InputType::up))
		{
			puressTime_ = 0;
			waitInterval_ = 60;
		}
		if (puressTime_ % waitInterval_ == 0)
		{
			soundVolume = soundMgr.GetBGMVolume() + 1;
			if (soundVolume >= 255)
			{
				soundVolume = 255;
			}
			soundMgr.SetBGMVolume(soundVolume, soundH_);
		}
		if (puressTime_ % 10 == 0)
		{
			if (waitInterval_-- <= 3)
			{
				waitInterval_ = 3;
			}
		}
		puressTime_++;
	}
	if (input.IsPressed(InputType::down))
	{
		if (input.IsTriggered(InputType::down))
		{
			puressTime_ = 0;
			waitInterval_ = 60;
		}
		if (puressTime_ % waitInterval_ == 0)
		{
			soundVolume = soundMgr.GetBGMVolume() - 1;
			if (soundVolume <= 0)
			{
				soundVolume = 0;
			}
			soundMgr.SetBGMVolume(soundVolume, soundH_);
		}
		if (puressTime_ % 10 == 0)
		{
			if (waitInterval_-- <= 3)
			{
				waitInterval_ = 3;
			}
		}
		puressTime_++;
	}
	if (input.IsTriggered(InputType::next) || input.IsTriggered(InputType::prev))
	{
		SoundManager::GetInstance().Play(SoundId::Determinant);
		soundChange_[soundTypeBGM].color = 0xaaffaa;
		updateFunc_ = &SoundSettingScene::NormalUpdate;
		return;
	}
}

void SoundSettingScene::SEVolumeChange(const InputState& input)
{
	auto& soundMgr = SoundManager::GetInstance();
	int soundVolume = 0;

	//SE
	if (input.IsPressed(InputType::up))
	{
		if (input.IsTriggered(InputType::up))
		{
			puressTime_ = 0;
			waitInterval_ = 60;
		}
		if (puressTime_ % waitInterval_ == 0)
		{
			soundVolume = soundMgr.GetSEVolume() + 1;
			if (soundVolume >= 255)
			{
				soundVolume = 255;
			}
			SoundManager::GetInstance().Play(SoundId::Cursor);
			soundMgr.SetSEVolume(soundVolume);
		}
		if (puressTime_ % 10 == 0)
		{
			if (waitInterval_-- <= 3)
			{
				waitInterval_ = 3;
			}
		}
		puressTime_++;
	}
	if (input.IsPressed(InputType::down))
	{
		if (input.IsTriggered(InputType::down))
		{
			puressTime_ = 0;
			waitInterval_ = 60;
		}
		if (puressTime_ % waitInterval_ == 0)
		{
			soundVolume = soundMgr.GetSEVolume() - 1;
			if (soundVolume <= 0)
			{
				soundVolume = 0;
			}
			SoundManager::GetInstance().Play(SoundId::Cursor);
			soundMgr.SetSEVolume(soundVolume);
		}
		if (puressTime_ % 10 == 0)
		{
			if (waitInterval_-- <= 3)
			{
				waitInterval_ = 3;
			}
		}
		puressTime_++;
	}
	if (input.IsTriggered(InputType::next) || input.IsTriggered(InputType::prev))
	{
		SoundManager::GetInstance().Play(SoundId::Determinant);
		soundChange_[soundTypeSE].color = 0xaaffaa;
		updateFunc_ = &SoundSettingScene::NormalUpdate;
		return;
	}
}

