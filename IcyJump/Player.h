#pragma once
#include "GameLayout.h"
#include "Block.h"
#define TIMESTEP 1.0/60.0
#define PLAYERTHRESHOLD 800
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
	bool autoDecrement = false;

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

		if (gameLayout.checkHorizontalCollision(playerBlock))
		{
			float collisionValue = gameLayout.getCollisionValue();
			if (gameLayout.isCollisionAtLeft())
				playerBlock.setX(collisionValue, collisionValue + 50);
			else if (gameLayout.isCollisionAtRight())
				playerBlock.setX(collisionValue - 50, collisionValue);
			initial_velocity_horizontal = 0;
		}
	}
	void move_vertical(float dy)
	{

		playerBlock.increment_y(dy);

		if (gameLayout.checkVerticalCollision(playerBlock))
		{
			float collisionValue = gameLayout.getCollisionValue();
			if (gameLayout.isCollisionAtTop())
				playerBlock.setY(collisionValue - 50, collisionValue);
			else if (gameLayout.isCollisionAtBottom())
				playerBlock.setY(collisionValue, collisionValue + 50);


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
		if ((velocity_horizontal = initial_velocity_horizontal + acceleration_horizontal*TIMESTEP) > 2000)
			velocity_horizontal = 2000;

	}

	void compute_displacement()
	{

		displacement_x = (initial_velocity_horizontal *TIMESTEP) + 0.5 *acceleration_horizontal * TIMESTEP * TIMESTEP;
		displacement_y = (initial_velocity_vertical * TIMESTEP) + 0.5 * acceleration_vertical * TIMESTEP *TIMESTEP;
		initial_velocity_horizontal = velocity_horizontal;
		initial_velocity_vertical = velocity_vertical;
	}

	bool checkThreshold()
	{
		if (playerBlock.ym > PLAYERTHRESHOLD)
		{
			autoDecrement = true;
			return true;
		}
		return false;
	}

	bool getAutoDecrement()
	{
		if (autoDecrement)
			return true;
		return false;
	}
	float getDecrementValue()
	{
		return playerBlock.ym - PLAYERTHRESHOLD;
	}

	void decrementPlayerBlock(float value)
	{
		playerBlock.increment_y(value*-1);
	}
 
	void decrementAllObjects()
	{
		float decrementValue = getDecrementValue();
		decrementPlayerBlock(decrementValue);
		gameLayout.decrementAllBlocks(decrementValue);
	}

	void decrementAllObjects(float decrementValue)
	{

		decrementPlayerBlock(decrementValue);
		gameLayout.decrementAllBlocks(decrementValue);
	}

};