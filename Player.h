#pragma once
#include "Util/Geometry.h"
#include <memory>
#include <vector>

class InputState;
class Stage;

using MapData_t = std::vector<std::vector<unsigned char>>;

enum Motion
{
	DownIdle,
	WidthIdle,
	UpIdle,
	DownWalk,
	WidthWalk,
	UpWalk,
	DownAttack,
	WidthAttack,
	UpAttack,
	Dead
};

class Player
{
public:
	Player();
	~Player();

	void Init();
	void Update();
	void Draw();

private:
	std::shared_ptr<InputState> input_;
	std::shared_ptr<Stage> stage_;
	MapData_t map_;

	Position2 pos_;
	int handle = 0;
	int idxX = 0, idxY = 0;
	int frame;
	bool handleTurn = false;
};

