#pragma once
#include "Secne.h"

/// <summary>
/// ゲームクリアシーン
/// </summary>
class GameclearScene : public Scene
{
public:
    GameclearScene(SceneManager& manager);
    virtual ~GameclearScene();

    void Update(const InputState& input);
    void Draw();
private:
    unsigned int fadeColor_ = 0x000000;//フェードの色（黒

    void FadeInUpdat(const InputState& input);
    void FadeOutUpdat(const InputState& input);
    void NormalUpdat(const InputState& input);

    void (GameclearScene::* updateFunc_)(const InputState&);
};

