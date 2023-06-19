#pragma once
#include "Secne.h"
#include <memory>

class Stage;
class Player;

/// <summary>
/// �Q�[�����V�[��
/// </summary>
class GameplayingScene : public Scene
{
public:
    GameplayingScene(SceneManager& manager);
    virtual ~GameplayingScene();

    virtual void Update(const InputState& input);
    virtual void Draw();
private:
    //��ʂ̃t�F�[�h�C��
     void FadeInUpdat(const InputState& input);
    //�ʏ�X�V
     void NormalUpdat(const InputState& input);
    //��ʂ̃t�F�[�h�A�E�g
     void FadeOutUpdat(const InputState& input);
private:
    unsigned int fadeColor_ = 0x000000;//�t�F�[�h�̐F�i��
    
    void (GameplayingScene::* updateFunc_)(const InputState& input);

    int crea_ = 0;

    int chipHandle_;

    std::shared_ptr<Stage> stage_;
    std::shared_ptr<Player> player_;
};

