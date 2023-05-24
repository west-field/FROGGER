#include <DxLib.h>
#include "game.h"
#include "Util/Sound.h"
#include "InputState.h"
#include "Scene/SceneManager.h"
#include "Scene/TitleScene.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	// window���[�h�ݒ�
	ChangeWindowMode(Game::kWindowMode);

	// window���[�h��ύX���邽��
	SetChangeScreenModeGraphicsSystemResetFlag(false);

	// �E�C���h�E���ݒ�
	SetMainWindowText(Game::kTitleText);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)
	{
		return -1;
	}
	auto& soundManager = SoundManager::GetInstance();

	SetDrawScreen(DX_SCREEN_BACK);

	InputState input;
	SceneManager sceneManeger;
	sceneManeger.ChangeScene(new TitleScene(sceneManeger));

	bool isTriggerWindouMode = false;//ALT��ENTER�������Ă��邩
	bool isWindouwMode = Game::kWindowMode;//�E�B���h�E���[�h��ύX����

	while (ProcessMessage() != -1)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// ��ʂ̃N���A
		ClearDrawScreen();

		input.Update();
		sceneManeger.Update(input);
		sceneManeger.Draw();

		//��ALT��ENTER�������ƃE�B���h�E���[�h��ύX�ł���
		if (CheckHitKey(KEY_INPUT_LALT))
		{
			if (CheckHitKey(KEY_INPUT_RETURN))
			{
				if (!isTriggerWindouMode)
				{
					isWindouwMode = !isWindouwMode;
					ChangeWindowMode(isWindouwMode);
					SetDrawScreen(DX_SCREEN_BACK);//�`�����Ē�`
				}
				isTriggerWindouMode = true;
			}
			else
			{
				SetDrawScreen(DX_SCREEN_BACK);//�`�����Ē�`
				isTriggerWindouMode = false;
			}
		}

		//����ʂ�\��ʂ����ւ���
		ScreenFlip();

		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;
		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667) {}
	}
	DxLib_End();

	return 0;
}