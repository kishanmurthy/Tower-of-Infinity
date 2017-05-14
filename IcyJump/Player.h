#pragma once
#include<stdio.h>
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
	bool jump;
	bool jumpFinish;
	GameLayout gameLayout;
	bool autoDecrement = false;
	float scrolling_speed;
	bool scrolling_speed_update = true;
	Player(GameLayout gameLayout) {
		
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
		jump = false;
		jumpFinish = false;
		scrolling_speed = 1;
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
			if (jump)
			{
				jump = false;
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
		velocity_horizontal = initial_velocity_horizontal + acceleration_horizontal*TIMESTEP;
		if (velocity_horizontal > 2000)
			velocity_horizontal = 2000;
		else if (velocity_horizontal < -2000)
			velocity_horizontal = -2000;
	}

	void compute_displacement()
	{
		displacement_x = (initial_velocity_horizontal *TIMESTEP) + 0.5 *acceleration_horizontal * TIMESTEP * TIMESTEP;
		displacement_y = (initial_velocity_vertical * TIMESTEP) + 0.5 * acceleration_vertical * TIMESTEP *TIMESTEP;
		initial_velocity_horizontal = velocity_horizontal;
		initial_velocity_vertical = velocity_vertical;
	}

	void setAcceleration(bool keys[])
	{
		if (keys[0])
		{
			if (!jump)
				acceleration_vertical = 120000;
			else
				acceleration_vertical = -6000; //Is set when the object is in jump state and up arrow pressed.
		}
		else
			acceleration_vertical = -6000; 
		
		if (keys[2])
			acceleration_horizontal = -8000;
		else if (keys[3])
			acceleration_horizontal = 8000;
			

		if (keys[1])
			{	//normal retardation
				if (initial_velocity_horizontal > 100 && !jump)
					acceleration_horizontal = -5000;
				else if (initial_velocity_horizontal < -100 && !jump)
					acceleration_horizontal = 5000;
				else if (!jump)
				{
					initial_velocity_horizontal = 0;
					acceleration_horizontal = 0;
				}
			}
	
		
		
	}

	void resetHorizontalAccelerationifJump()
	{
		if (acceleration_vertical == 120000)
		{
			jump = true;
			acceleration_horizontal = 0;
		}
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
	
	void verticalScrolling()
	{
		if (autoDecrement)
		{
			decrementAllObjects(scrolling_speed);
		}
	}

	void updateScrollingSpeed()
	{
		if (gameLayout.blockPoped % 20 == 0 && scrolling_speed_update)
		{
		
			scrolling_speed *= 1.5;
			scrolling_speed_update = false;
		}
		else if (gameLayout.blockPoped % 20 != 0)
		{
			scrolling_speed_update = true;
		}
	}

	bool isOut()
	{
		if (playerBlock.y2 < 0)
			return true;
		return false;
	}

};