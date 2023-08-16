#include <cub.h>

/**
 * It will return the position of the
 * first encounter with a boundary in the x axis
 * and also the offset
*/
static t_closer_cast_result	cast_x_closer_ray(t_posd from, int angle)
{
	t_closer_cast_result	r;
	double					tang;

	// Check Horizontal Lines
	r.dof = 0;
	tang = tan(degree_to_radians(angle));
	tang = 1.0 / tang;
	// 180degrees
	if (sin(degree_to_radians(angle)) > 0.001)  // looking up
	{
		//>> 6 =  dividing by MAP_LENGTH
		r.ray.y = (((int) from.y >> 6) << 6) - 0.0001;
		r.ray.x = (from.y - r.ray.y) * tang + from.x;
		r.offset.y = -MAP_LENGTH;
		r.offset.x = -r.offset.y * tang;
	}
	else if (sin(degree_to_radians(angle)) < -0.001)  // looking down
	{
		r.ray.y = (((int) from.y >> 6) << 6) + MAP_LENGTH;
		r.ray.x = (from.y - r.ray.y) * tang + from.x;
		r.offset.y = MAP_LENGTH;
		r.offset.x = -r.offset.y * tang;
	}
	else  // looking straght left or right
	{
		r.ray.x = from.x;
		r.ray.y = from.y;
		r.dof = 8;
	}
	return (r);
}

/**
 * It will return the position of the
 * first encounter with a boundary in the y axis
 * and also the offset
*/
static t_closer_cast_result	cast_y_closer_ray(t_posd from, int angle)
{
	t_closer_cast_result	r;
	double					tang;

	r.dof = 0;
	tang = tan(degree_to_radians(angle));
	// 180degrees
	if (cos(degree_to_radians(angle)) > 0.001)  // looking left
	{
		//>> 6 =  dividing by MAP_LENGTH
		r.ray.x = (((int) from.x >> 6) << 6) + MAP_LENGTH;
		r.ray.y = (from.x - r.ray.x) * tang + from.y;
		r.offset.x = MAP_LENGTH;
		r.offset.y = -r.offset.x * tang;
	}
	else if (cos(degree_to_radians(angle)) < -0.001)  // looking right
	{
		r.ray.x = (((int) from.x >> 6) << 6) - 0.0001;
		r.ray.y = (from.x - r.ray.x) * tang + from.y;
		r.offset.x = -MAP_LENGTH;
		r.offset.y = -r.offset.x * tang;
	}
	else // looking up or down, no hit
	{
		r.ray.x = from.x;
		r.ray.y = from.y;
		r.dof = 8;
	}
	return (r);
}

/**
 * It will return the position of the
 * next encounter with a boundary in the x axis
 * It uses the passed offset for better perfomance.
 * Using an offset allow us to jump multiple pixels checks
*/
static t_cast_result	cast_x_ray(int angle, t_posd from, t_posd offset)
{
	t_cast_result	r;
	t_posi			map;
	int				mp;
	double			ang_radians;
	int				dof;

	dof = 0;
	r.distance = 100000;
	ang_radians = degree_to_radians(angle);
	while (dof < 8)
	{
		map.x = (int) (from.x) >> 6;
		map.y = (int) (from.y) >> 6;
		mp = map.y * MAP_WIDTH + map.x;

		if (mp > 0 && mp < MAP_WIDTH * MAP_HEIGHT && state()->world_map[mp] > 0)
		{
			r.distance = cos(ang_radians) * (from.x - state()->player_pos.x) -
				sin(ang_radians) * (from.y - state()->player_pos.y);
			dof = 8;
		}
		else
		{
			from.x += offset.x;
			from.y += offset.y;
			dof += 1;
		}
	}
	r.ray = from;
	return (r);
}

/**
 * It will return the position of the
 * next encounter with a boundary in the y axis
 * It uses the passed offset for better perfomance.
 * Using an offset allow us to jump multiple pixels checks
*/
static t_cast_result	cast_y_ray(int angle, t_posd from, t_posd offset)
{
	t_cast_result	r;
	t_posi			map;
	int				mp;
	double			ang_radians;
	int				dof;

	dof = 0;
	r.distance = 100000;
	ang_radians = degree_to_radians(angle);
	while (dof < 8)
	{
		map.x = (int) (from.x) >> 6;
		map.y = (int) (from.y) >> 6;
		mp = map.y * MAP_WIDTH + map.x;

		if (mp > 0 && mp < MAP_WIDTH * MAP_HEIGHT && state()->world_map[mp] > 0)
		{
			r.distance = cos(ang_radians) * (from.x - state()->player_pos.x) -
				sin(ang_radians) * (from.y - state()->player_pos.y);
			dof = 8;
		} // hit
		else
		{
			from.x += offset.x;
			from.y += offset.y;
			dof += 1;
		}
	}
	r.ray = from;
	return (r);
}

t_cast_result	cast_ray(t_posd from, int angle)
{
	t_closer_cast_result	closer_cast;
	t_cast_result			cast;
	double					ry;
	double					rx;
	double					vx;
	double					vy;
	int						distH;
	int						distV;

	// Check Vertical Lines;
	closer_cast = cast_y_closer_ray(from, angle);
	rx = closer_cast.ray.x;
	ry = closer_cast.ray.y;
	distV = 100000;
	if (closer_cast.dof != 8)
	{
		cast = cast_y_ray(angle, closer_cast.ray, closer_cast.offset);
		distV = cast.distance;
		rx = cast.ray.x;
		ry = cast.ray.y;
	}
	vx = rx;
	vy = ry;

	// Check Horizontal Lines
	closer_cast = cast_x_closer_ray(from, angle);
	rx = closer_cast.ray.x;
	ry = closer_cast.ray.y;
	distH = 100000;
	if (closer_cast.dof != 8)
	{
		cast = cast_x_ray(angle, closer_cast.ray, closer_cast.offset);
		distH = cast.distance;
		rx = cast.ray.x;
		ry = cast.ray.y;
	}

	// Get the smaller distance
	if (distV < distH)
	{
		rx = vx;
		ry = vy;
		distH = distV;
	}

	cast.distance = distH;
	cast.ray.x = rx;
	cast.ray.y = ry;
	return (cast);
}
