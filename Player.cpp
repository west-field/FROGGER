#include "Player.h"
#include "Game/Stage.h"
#include "InputState.h"
#include <DxLib.h>

namespace
{
	constexpr int handleSize = 48;
	constexpr int idxWidthMax = 6;
	constexpr int kMapSize = 16;
}

Player::Player()
{
	input_ = std::make_shared<InputState>();
	stage_ = std::make_shared<Stage>();
	map_ = stage_->GetMapData();

	pos_ = { 0, 0 };
	handle = LoadGraph(L"Data/player.png");
	frame = 30;
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update()
{	
	input_->Update();

	if (input_->IsTriggered(InputType::left))
	{
		pos_.x -= kMapSize * 2;
		idxY = Motion::WidthIdle;
		handleTurn = true;
	}
	else if (input_->IsTriggered(InputType::right))
	{
		pos_.x += kMapSize * 2;
		idxY = Motion::WidthIdle;
		handleTurn = false;
	}
	else if (input_->IsTriggered(InputType::up))
	{
		pos_.y -= kMapSize * 2;
		idxY = Motion::UpIdle;
		handleTurn = false;
	}
	else if (input_->IsTriggered(InputType::down))
	{
		pos_.y += kMapSize * 2;
		idxY = Motion::DownIdle;
		handleTurn = false;
	}
	
	frame--;
	if (frame < 0)
	{
		frame = 30;
		idxX++;
		if (idxWidthMax <= idxX) idxX = 0;
	}

	int range = 50 * kMapSize * 2;
	if (pos_.x <= 0 + kMapSize) pos_.x = 0 + kMapSize;
	if (range <= pos_.x) pos_.x = range - kMapSize;

	range = 27 * kMapSize * 2;
	if (pos_.y <= 0 + kMapSize) pos_.y = 0 + kMapSize;
	if (range <= pos_.y) pos_.y = range - kMapSize;
}

void Player::Draw()
{
	DrawRectRotaGraph(pos_.x, pos_.y,
		idxX * handleSize, idxY * handleSize,
		handleSize, handleSize,
		2.0, 0.0,
		handle, true, handleTurn 
	);
}
