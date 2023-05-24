#pragma once
#include "Secne.h"


/// <summary>
/// �Q�[���I�[�o�[�V�[��
/// </summary>
class GameoverScene : public Scene
{
public:
    GameoverScene(SceneManager& manager);
    virtual ~GameoverScene();

    void Update(const InputState& input);
    void Draw();
private:
    unsigned int fadeColor_ = 0xff0000;//�t�F�[�h�̐F�i��

    void FadeInUpdat(const InputState& input);
    void FadeOutUpdat(const InputState& input);
    void NormalUpdat(const InputState& input);

    void (GameoverScene::*updateFunc_ )(const InputState&) ;
};

