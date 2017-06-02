#include<stdio.h>
#include "GameLayout.h"
#include "Block.h"
#define TIMESTEP 1.0/60.0
#define PLAYERTHRESHOLD 800
class Player
{
public:
	GameLayout gameLayout;
	Block playerBlock;

private:
	float initial_velocity_horizontal;
	float velocity_horizontal;
	float initial_velocity_vertical;
	float velocity_vertical;
	float acceleration_horizontal;
	float acceleration_vertical;
	float displacement_x;
	float displacement_y;
	bool jump;
	bool start_scrolling;
	float scrolling_speed;
	bool can_scrolling_speed_updated = true;

public:

	Player(GameLayout &gameLayout) {
		this->gameLayout = gameLayout;
		playerBlock.setAttributes(200, 100, 250, 150);

		initial_velocity_horizontal = 0;
		velocity_horizontal = 0;
		initial_velocity_vertical = 0;
		velocity_vertical = 0;
		acceleration_horizontal = 0;
		acceleration_vertical = 0;
		displacement_x = 0;
		displacement_y = 0;
		jump = false;
		start_scrolling = false;
		scrolling_speed = 1;
		can_scrolling_speed_updated = true;
	}

	bool checkThreshold()
	{
		if (playerBlock.ym > PLAYERTHRESHOLD)
		{
			start_scrolling = true;
			return true;
		}
		return false;
	}

	void compute_physics()
	{
		compute_velocity();
		compute_displacement();
	}

	bool isOut()
	{
		if (playerBlock.y2 < 0)
			return true;
		return false;
	}
	void move_object()
	{
		move_vertical();
		move_horizontal();
	}
	void reset()
	{
		gameLayout.reset();
		playerBlock.setAttributes(200, 100, 250, 150);
		initial_velocity_horizontal = 0;
		velocity_horizontal = 0;
		initial_velocity_vertical = 0;
		velocity_vertical = 0;
		acceleration_horizontal = 0;
		acceleration_vertical = 0;
		displacement_x = 0;
		displacement_y = 0;
		jump = false;
		scrolling_speed = 1;
		start_scrolling = false;
		can_scrolling_speed_updated = true;
	}

	void resetHorizontalAccelerationifJump()
	{
		if (acceleration_vertical == 120000)
		{
			jump = true;
			acceleration_horizontal = 0;
		}
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
		{
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
	void verticalScrolling()
	{
		if (start_scrolling)
		{
			decrementAllObjects(scrolling_speed);
		}
		if (checkThreshold())
			decrementAllObjects();
	}

	void updateScrollingSpeed()
	{
		if (gameLayout.get_block_poped() % 30 == 0 && can_scrolling_speed_updated)
		{
			scrolling_speed *= 1.5;
			can_scrolling_speed_updated = false;
		}
		else if (gameLayout.get_block_poped() % 30 != 0)
		{
			can_scrolling_speed_updated = true;
		}
	}
private:

	void compute_displacement()
	{
		displacement_x = (initial_velocity_horizontal *TIMESTEP) + 0.5 *acceleration_horizontal * TIMESTEP * TIMESTEP;
		displacement_y = (initial_velocity_vertical * TIMESTEP) + 0.5 * acceleration_vertical * TIMESTEP *TIMESTEP;
		initial_velocity_horizontal = velocity_horizontal;
		initial_velocity_vertical = velocity_vertical;
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
	void decrementAllObjects()
	{
		float decrementValue = playerBlock.ym - PLAYERTHRESHOLD;
		decrementPlayerBlock(decrementValue);
		gameLayout.decrementAllBlocks(decrementValue);
	}

	void decrementAllObjects(float decrementValue)
	{
		decrementPlayerBlock(decrementValue);
		gameLayout.decrementAllBlocks(decrementValue);
	}
	void decrementPlayerBlock(float value)
	{
		playerBlock.increment_y(value*-1);
	}

	void move_horizontal()
	{
		playerBlock.increment_x(displacement_x);

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

	void move_vertical()
	{
		playerBlock.increment_y(displacement_y);
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
			}
		}
	}
};