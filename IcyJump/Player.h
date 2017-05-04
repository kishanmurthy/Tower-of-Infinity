#pragma once
#define TIMESTEP 1.0/60.0
class Player
{
public:
	float v[2] = { 0,0 };
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
	Player() {
		v[0] = v[1] = 0;
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
	void move_horizontal(float *v, float dx)
	{
		v[0] += dx;
		if (v[0] > 1870)
		{
			v[0] = 1870;
			initial_velocity_horizontal = 0;

		}
		if (v[0] < 0)
		{
			v[0] = 0;
			initial_velocity_horizontal = 0;

		}
	}
	void move_vertical(float *v, float dy)
	{
		v[1] += dy;
		if (v[1] > 1030)
		{
			v[1] = 1030;
			initial_velocity_vertical = 0;

		}
		if (v[1] < 0)
		{
			v[1] = 0;
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

		move_vertical(v, displacement_y);
		move_horizontal(v, displacement_x);

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