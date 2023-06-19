#pragma once
#include "Secne.h"
#include <memory>

class Stage;
class Player;

/// <summary>
/// ゲーム中シーン
/// </summary>
class GameplayingScene : public Scene
{
public:
    GameplayingScene(SceneManager& manager);
    virtual ~GameplayingScene();

    virtual void Update(const InputState& input);
    virtual void Draw();
private:
    //画面のフェードイン
     void FadeInUpdat(const InputState& input);
    //通常更新
     void NormalUpdat(const InputState& input);
    //画面のフェードアウト
     void FadeOutUpdat(const InputState& input);
private:
    unsigned int fadeColor_ = 0x000000;//フェードの色（黒
    
    void (GameplayingScene::* updateFunc_)(const InputState& input);

    int crea_ = 0;

    int chipHandle_;

    std::shared_ptr<Stage> stage_;
    std::shared_ptr<Player> player_;
};

