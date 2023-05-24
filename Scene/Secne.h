#pragma once

//プロトタイプ宣言
class SceneManager;//シーンマネージャー
class InputState;//入力ステート

/// <summary>
/// シーン基底クラス//大基になっている
/// </summary>
class Scene
{
protected:
	SceneManager& manager_;//シーンマネージャーへの参照
	
	static constexpr int kFadeInterval = 60;
	int fadeTimer_ = kFadeInterval;//フェードタイマー
	int fadeValue_ = 255;//黒矩形とのブレンド具合
public:
	Scene(SceneManager& manager) :manager_(manager){}
	virtual ~Scene() {}
	//シーンを更新する
	virtual void Update(const InputState& input) = 0;
	//シーンを描画する
	virtual void Draw() = 0;
};

