#pragma once
#include "GameLayout.h"
#include "Block.h"
#define TIMESTEP 1.0/60.0
class Player
{
public:
	Block playerBlock;

	float initial_velocity_horizontal;
	float velocity_horizontal;
	float initial_velocity_vertical;
	float velocity_vertical;
	float acceleration_horizontal;
	float acceleration_vertical;
	float displacement_x;
	float displacement_y;
	bool canJump;
	bool jumpFinish;
	GameLayout gameLayout;
	
	Player(GameLayout &gameLayout) {
		
		this->gameLayout = gameLayout;
		playerBlock.setAttrib(200, 100, 250, 150);
	
		initial_velocity_horizontal = 0;
		velocity_horizontal = 0;
		initial_velocity_vertical = 0;
		velocity_vertical = 0;
		acceleration_horizontal = 0;
		acceleration_vertical = 0;
		displacement_x = 0;
		displacement_y = 0;
		canJump = true;
		jumpFinish = false;
	}
	void move_horizontal(float dx)
	{
		playerBlock.increment_x(dx);

		if (playerBlock.x1 > 1670)
		{
			playerBlock.setX(1670, 1720);
	
			initial_velocity_horizontal = 0;

		}
		if (playerBlock.x1 < 200)
		{
			playerBlock.setX(200, 250);

			initial_velocity_horizontal = 0;

		}
	}
	void move_vertical(float dy)
	{

		playerBlock.increment_y(dy);
		if (playerBlock.y2 > 1030)
		{
			playerBlock.y2 = 1030;
			initial_velocity_vertical = 0;

		}
	//	if(gameLayout.checkVerticalCollision(v))
		if (playerBlock.y1 < 100)
		{
			playerBlock.setY(100, 150);
			initial_velocity_vertical = 0;
			if (!canJump)
			{
				canJump = true;
				jumpFinish = 1;
			}
		}
	}
	void move_object()
	{

		move_vertical(displacement_y);
		move_horizontal(displacement_x);

	}

	void compute_velocity()
	{
		velocity_vertical = initial_velocity_vertical + acceleration_vertical*TIMESTEP;
		if ((velocity_horizontal = initial_velocity_horizontal + acceleration_horizontal*TIMESTEP)> 2000)
			velocity_horizontal = 2000;

	}

	void compute_displacement()
	{

		displacement_x = (initial_velocity_horizontal *TIMESTEP) + 0.5 *acceleration_horizontal * TIMESTEP * TIMESTEP;
		displacement_y = (initial_velocity_vertical * TIMESTEP) + 0.5 * acceleration_vertical * TIMESTEP *TIMESTEP;
		initial_velocity_horizontal = velocity_horizontal;
		initial_velocity_vertical = velocity_vertical;
	}


};